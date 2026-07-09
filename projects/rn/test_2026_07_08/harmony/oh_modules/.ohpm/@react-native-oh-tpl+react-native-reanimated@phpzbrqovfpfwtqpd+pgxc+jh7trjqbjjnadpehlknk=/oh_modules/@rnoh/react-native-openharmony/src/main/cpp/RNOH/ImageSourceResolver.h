/**
 * Copyright (c) 2024 Huawei Technologies Co., Ltd.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <ReactCommon/RuntimeExecutor.h>
#include <react/renderer/imagemanager/primitives.h>
#include <unordered_map>
#include <unordered_set>
#include "RNInstance.h"
#include "RNOH/ArkTSMessageHub.h"
#include "RNOH/Assert.h"
#include "RNOH/RNInstance.h"
#include "RNOH/TaskExecutor/TaskExecutor.h"
#include "RNOHCorePackage/TurboModules/ImageLoaderTurboModule.h"

constexpr char IMAGE_SOURCE_PENDING[] = "IMAGE_SOURCE_PENDING";

namespace rnoh {

static const std::unordered_set<std::string> VIDEO_FORMATS = {
    ".mp4", ".mov",  ".avi", ".mpeg", ".mpg",  ".mkv",  ".flv",
    ".wmv", ".m2ts", ".vob", ".ts",   ".webm", ".m3u8", ".mpd",
    ".3gp", ".3g2",  ".rm",  ".rmvb", ".f4v",  ".mxf"};

class ImageSourceResolver : public ArkTSMessageHub::Observer {
 public:
  using Shared = std::shared_ptr<ImageSourceResolver>;
  bool isVideoUri(const std::string& uri) {
    if (uri.empty()) {
      return false;
    }

    std::string path = uri;
    size_t paramIndex = uri.find('?');
    if (paramIndex != std::string::npos) {
      path = uri.substr(0, paramIndex);
    }

    size_t lastDot = path.find_last_of('.');
    if (lastDot == std::string::npos) {
      return false;
    }

    std::string suffix = path.substr(lastDot);
    std::transform(suffix.begin(), suffix.end(), suffix.begin(), ::tolower);

    return VIDEO_FORMATS.find(suffix) != VIDEO_FORMATS.end();
  }

  bool isRemoteUri(const std::string& uri) {
    if (uri.empty()) {
      return false;
    }
    // Check if URI starts with "http" (matches both "http://" and "https://")
    return uri.find("http", 0) == 0;
  }

  ImageSourceResolver(
      ArkTSMessageHub::Shared const& subject,
      RNInstance::Weak rnInstance,
      std::unordered_map<std::string, std::string> imageSourceByName)
      : ArkTSMessageHub::Observer(subject),
        m_rnInstance(rnInstance),
        imageSourceByName(imageSourceByName) {}

  class ImageSourceUpdateListener {
   public:
    std::string observedUri;

    ImageSourceUpdateListener(
        ImageSourceResolver::Shared const& imageSourceResolver)
        : m_imageSourceResolver(imageSourceResolver){};

    ~ImageSourceUpdateListener() {
      m_imageSourceResolver->removeListener(this);
    }

    virtual void onImageSourceCacheUpdate() = 0;

   private:
    ImageSourceResolver::Shared const& m_imageSourceResolver;
  };

  // Based on Android MultiSourceHelper class, see:
  // https://github.com/facebook/react-native/blob/v0.77.1/packages/react-native/ReactAndroid/src/main/java/com/facebook/react/views/imagehelper/MultiSourceHelper.kt#L81
  struct MultiSourceResolutionResult {
    /**
     * Get the best result overall (closest in size to the view's size).
     */
    facebook::react::ImageSource bestResult;
    /**
     * Get the best result URI (closest in size to the view's size) that is also
     * in cache. If this would be the same as the URI in `bestResult`, this will
     * return `std::nullopt` instead.
     */
    std::optional<std::string> bestResultUriInCache;
  };

  MultiSourceResolutionResult resolveImageSource(
      ImageSourceUpdateListener& listener,
      facebook::react::LayoutMetrics const& layoutMetrics,
      facebook::react::ImageSources const& newSourcesCandidates) {
    assertMainThread();
    auto imageCandidate = getBestSourceForSize(
        layoutMetrics.frame.size.width,
        layoutMetrics.frame.size.height,
        layoutMetrics.pointScaleFactor,
        newSourcesCandidates);

    if (imageCandidate.type != facebook::react::ImageSource::Type::Remote) {
      return {imageCandidate};
    }

    if (!isRemoteUri(imageCandidate.uri)) {
      return {imageCandidate};
    }

    // Subscribe to get information about prefetched URIs.
    if (isVideoUri(imageCandidate.uri)) {
      addListenerForURI(imageCandidate.uri, &listener);
    } else {
      if (uriListenersMap.find(imageCandidate.uri) == uriListenersMap.end()) {
        removeListener(&listener);
        addListenerForURI(imageCandidate.uri, &listener);
      }
    }

    if (auto it = remoteImageSourceMap.find(imageCandidate.uri);
        it == remoteImageSourceMap.end() ||
        it->second == IMAGE_SOURCE_PENDING) {
      auto resolvedFileUri = getPrefetchedImageFileUri(imageCandidate);
      if (!resolvedFileUri.empty()) {
        remoteImageSourceMap.emplace(imageCandidate.uri, resolvedFileUri);
      }
    }

    auto it = remoteImageSourceMap.find(imageCandidate.uri);
    if (it == remoteImageSourceMap.end() ||
        it->second == IMAGE_SOURCE_PENDING) {
      return {imageCandidate};
    }

    // cache hit
    return {imageCandidate, it->second};
  }

  // Based on Android MultiSourceHelper class, see:
  // https://github.com/facebook/react-native/blob/v0.72.5/packages/react-native/ReactAndroid/src/main/java/com/facebook/react/views/imagehelper/MultiSourceHelper.java#L61
  facebook::react::ImageSource getBestSourceForSize(
      double width,
      double height,
      double pointScaleFactor,
      facebook::react::ImageSources const& sources) {
    RNOH_ASSERT_MSG(
        sources.size() > 0, "ImageSources vector should not be empty");

    if (sources.size() == 1) {
      return sources[0];
    }

    auto bestSourceIndex = 0;
    auto targetImagePixels = width * height * pointScaleFactor;
    auto bestPixelsFit = std::numeric_limits<double>::max();

    for (auto i = 0; i < sources.size(); i++) {
      auto& source = sources[i];
      auto imagePixels = source.size.width * source.size.height;
      auto pixelsFit = std::abs(1.0 - imagePixels / targetImagePixels);

      if (pixelsFit < bestPixelsFit) {
        bestPixelsFit = pixelsFit;
        bestSourceIndex = i;
      }
    }

    return sources[bestSourceIndex];
  }

  void addListenerForURI(
      const std::string& uri,
      ImageSourceUpdateListener* listener) {
    assertMainThread();
    listener->observedUri = uri;
    auto it = uriListenersMap.find(uri);
    if (it == uriListenersMap.end()) {
      uriListenersMap.emplace(
          uri, std::initializer_list<ImageSourceUpdateListener*>{listener});
      return;
    }
    if (std::find(it->second.begin(), it->second.end(), listener) !=
        it->second.end()) {
      return;
    }
    it->second.push_back(listener);
  }

  void removeListenerForURI(
      const std::string& uri,
      ImageSourceUpdateListener* listener) {
    assertMainThread();
    auto it = uriListenersMap.find(uri);
    if (it == uriListenersMap.end()) {
      return;
    }
    auto& listeners = it->second;
    auto listenerPos = std::find(listeners.begin(), listeners.end(), listener);
    if (listenerPos != listeners.end()) {
      listeners.erase(listenerPos);
      if (listeners.empty()) {
        uriListenersMap.erase(uri);
      }
    }
  }

  void removeListener(ImageSourceUpdateListener* listener) {
    removeListenerForURI(listener->observedUri, listener);
  }

  std::optional<std::string> getImageSourceByName(const std::string& name) {
    if (imageSourceByName.contains(name)) {
      return {imageSourceByName[name]};
    }
    return std::nullopt;
  }

 protected:
  virtual void onMessageReceived(const ArkTSMessage& message) override {
    if (message.name == "UPDATE_IMAGE_SOURCE_MAP") {
      assertMainThread();
      auto remoteUri = message.payload["remoteUri"].asString();
      auto fileUri = message.payload["fileUri"].asString();
      auto it = uriListenersMap.find(remoteUri);
      if (it == uriListenersMap.end()) {
        return;
      }
      auto& listeners = it->second;
      remoteImageSourceMap.insert_or_assign(remoteUri, fileUri);
      for (auto listener : listeners) {
        listener->onImageSourceCacheUpdate();
        removeListenerForURI(remoteUri, listener);
      }
    }
  }

 private:
  std::unordered_map<std::string, std::vector<ImageSourceUpdateListener*>>
      uriListenersMap;
  std::unordered_map<std::string, std::string> remoteImageSourceMap;
  std::thread::id m_mainThreadId = std::this_thread::get_id();
  std::weak_ptr<RNInstance> m_rnInstance;
  std::unordered_map<std::string, std::string> imageSourceByName;

  void assertMainThread() {
    RNOH_ASSERT_MSG(
        m_mainThreadId == std::this_thread::get_id(),
        "ImageSourceResolver must only be accessed on the main thread");
  }

  std::string getPrefetchedImageFileUri(
      facebook::react::ImageSource imageCandidate) {
    auto rnInstance = m_rnInstance.lock();
    if (rnInstance == nullptr) {
      return {};
    }
    auto imageLoaderTurboModule =
        rnInstance->getTurboModule<ImageLoaderTurboModule>("ImageLoader");
    if (imageLoaderTurboModule != nullptr) {
      auto prefetchResult = imageLoaderTurboModule->callSync(
          "getPrefetchResult", {imageCandidate.uri});
      if (prefetchResult == "pending") {
        // The uri will be updated in onMessageReceived method.
        return IMAGE_SOURCE_PENDING;
      }
      if (prefetchResult != nullptr) {
        return prefetchResult.asString();
      }
    }
    return {};
  }
};

} // namespace rnoh
