/**
 * Copyright (c) 2024 Huawei Technologies Co., Ltd.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RNInstanceCAPI.h"

#include <react/renderer/componentregistry/native/NativeComponentRegistryBinding.h>
#include <react/renderer/runtimescheduler/RuntimeSchedulerCallInvoker.h>
#include <react/runtime/nativeviewconfig/LegacyUIManagerConstantsProviderBinding.h>
#include <future>
#include <memory>
#include "Assert.h"
#include "NativeLogger.h"
#include "Performance/NativeTracing.h"
#include "RNInstance.h"
#include "RNOH/Assert.h"
#include "RNOH/Performance/RNOHMarker.h"
#include "RNOHError.h"
#include "TaskExecutor/TaskExecutor.h"

using namespace facebook;
namespace rnoh {

RNInstanceCAPI::~RNInstanceCAPI() noexcept {
  DLOG(INFO) << "~RNInstanceCAPI::start";
  if (m_unsubscribeUITickListener != nullptr) {
    m_unsubscribeUITickListener();
  }
  m_taskExecutor->runSyncTask(
      TaskThread::MAIN,
      [surfaces =
           std::make_shared<decltype(m_surfaceById)>(std::move(m_surfaceById)),
       scheduler = m_scheduler,
       mountingManager = std::move(m_mountingManager),
       componentInstanceRegistry = std::move(m_componentInstanceRegistry),
       componentInstanceFactory = std::move(m_componentInstanceFactory)] {
        DLOG(INFO) << "~RNInstanceCAPI::MAIN - stopping all surfaces";
        for (auto& [surfaceId, surface] : *surfaces) {
          auto arkUISurface = std::dynamic_pointer_cast<ArkUISurface>(surface);
          if (arkUISurface != nullptr) {
            arkUISurface->stopSynchronously();
            scheduler->unregisterSurface(arkUISurface->getSurfaceHandler());
          }
        }
        if (!surfaces->empty()) {
          LOG(WARNING)
              << "Not all React Native surfaces were destroyed before the Instance they are running in.";
        }
      });
  DLOG(INFO) << "~RNInstanceCAPI::stop";
}

size_t RNInstanceCAPI::getId() {
  return m_id;
}

void RNInstanceCAPI::synchronouslyUpdateViewOnUIThread(
    facebook::react::Tag tag,
    folly::dynamic props) {
  facebook::react::TraceSection s(
      "#RNOH::RNInstanceCAPI::synchronouslyUpdateViewOnUIThread");
  VLOG(2) << "RNInstanceCAPI::synchronouslyUpdateViewOnUIThread";
  RNOH_ASSERT(m_taskExecutor->getCurrentTaskThread() == TaskThread::MAIN);

  auto componentInstance = m_componentInstanceRegistry->findByTag(tag);
  if (componentInstance == nullptr) {
    return;
  }

  auto componentHandle = componentInstance->getComponentHandle();
  auto componentDescriptor =
      m_scheduler->findComponentDescriptorByHandle_DO_NOT_USE_THIS_IS_BROKEN(
          componentHandle);
  if (componentDescriptor == nullptr) {
    LOG(ERROR)
        << "RNInstanceCAPI::synchronouslyUpdateViewOnUIThread: could not find componentDescriptor for tag: "
        << tag;
    return;
  }

  RNOHMarker::logMarker(
      RNOHMarker::RNOHMarkerId::FABRIC_UPDATE_UI_MAIN_THREAD_START, tag);
  m_mountingManager->updateView(tag, std::move(props), *componentDescriptor);
  RNOHMarker::logMarker(
      RNOHMarker::RNOHMarkerId::FABRIC_UPDATE_UI_MAIN_THREAD_END, tag);
}

void RNInstanceCAPI::attachRootView(
    NodeContentHandle nodeContentHandle,
    facebook::react::Tag surfaceId) {
  DLOG(INFO) << "RNInstanceCAPI::registerNodeContentHandle";
  auto it = m_surfaceById.find(surfaceId);
  if (it == m_surfaceById.end()) {
    LOG(ERROR) << "Surface with id: " << surfaceId << " not found";
    return;
  }
  it->second->attachToNodeContent(std::move(nodeContentHandle));
}

void RNInstanceCAPI::detachRootView(facebook::react::Tag surfaceId) {
  DLOG(INFO) << "RNInstanceCAPI::registerNodeContentHandle";
  auto it = m_surfaceById.find(surfaceId);
  if (it == m_surfaceById.end()) {
    LOG(ERROR) << "Surface with id: " << surfaceId << " not found";
    return;
  }
  it->second->detachFromNodeContent();
}

void RNInstanceCAPI::createSurface(
    facebook::react::Tag surfaceId,
    std::string const& moduleName) {
  DLOG(INFO) << "RNInstanceCAPI::createSurface";
  m_surfaceById.emplace(
      surfaceId,
      std::make_shared<ArkUISurface>(
          m_taskExecutor,
          m_scheduler,
          m_componentInstanceRegistry,
          m_componentInstanceFactory,
          m_arkTSMessageHub,
          m_arkTSBridge,
          surfaceId,
          m_id,
          moduleName));
}

void RNInstanceCAPI::updateSurfaceConstraints(
    facebook::react::Tag surfaceId,
    float minWidth,
    float minHeight,
    float maxWidth,
    float maxHeight,
    float viewportOffsetX,
    float viewportOffsetY,
    float pixelRatio,
    bool isRTL) {
  DLOG(INFO) << "RNInstanceCAPI::updateSurfaceConstraints";
  facebook::react::TraceSection s(
      "#RNOH::RNInstanceCAPI::updateSurfaceConstraints");
  auto it = m_surfaceById.find(surfaceId);
  if (it == m_surfaceById.end()) {
    return;
  }
  it->second->updateConstraints(
      minWidth,
      minHeight,
      maxWidth,
      maxHeight,
      viewportOffsetX,
      viewportOffsetY,
      pixelRatio,
      isRTL);
}

facebook::react::Size RNInstanceCAPI::measureSurface(
    facebook::react::Tag surfaceId,
    float minWidth,
    float minHeight,
    float maxWidth,
    float maxHeight,
    float viewportOffsetX,
    float viewportOffsetY,
    float pixelRatio,
    bool isRTL) {
  DLOG(INFO) << "RNInstanceCAPI::measureSurface";
  facebook::react::TraceSection s(
      "#RNOH::RNInstanceCAPI::updateSurfaceConstraints");
  auto it = m_surfaceById.find(surfaceId);
  if (it == m_surfaceById.end()) {
    throw FatalRNOHError("Invalid surfaceId");
  }
  return it->second->measure(
      minWidth,
      minHeight,
      maxWidth,
      maxHeight,
      viewportOffsetX,
      viewportOffsetY,
      pixelRatio,
      isRTL);
}

void RNInstanceCAPI::startSurface(
    facebook::react::Tag surfaceId,
    float minWidth,
    float minHeight,
    float maxWidth,
    float maxHeight,
    float viewportOffsetX,
    float viewportOffsetY,
    float pixelRatio,
    bool isRTL,
    folly::dynamic&& initialProps) {
  DLOG(INFO) << "RNInstanceCAPI::startSurface";
  auto it = m_surfaceById.find(surfaceId);
  if (it == m_surfaceById.end()) {
    return;
  }
  it->second->start(
      minWidth,
      minHeight,
      maxWidth,
      maxHeight,
      viewportOffsetX,
      viewportOffsetY,
      pixelRatio,
      isRTL,
      std::move(initialProps),
      m_animationDriver);
}

void RNInstanceCAPI::setSurfaceProps(
    facebook::react::Tag surfaceId,
    folly::dynamic&& props) {
  DLOG(INFO) << "RNInstanceCAPI::setSurfaceProps";
  facebook::react::TraceSection s("#RNOH::RNInstanceCAPI::setSurfaceProps");
  auto it = m_surfaceById.find(surfaceId);
  if (it == m_surfaceById.end()) {
    return;
  }
  it->second->setProps(std::move(props));
}

void RNInstanceCAPI::stopSurface(
    facebook::react::Tag surfaceId,
    std::function<void()> onStop) {
  DLOG(INFO) << "RNInstanceCAPI::stopSurface";
  auto it = m_surfaceById.find(surfaceId);
  if (it == m_surfaceById.end()) {
    return;
  }
  it->second->stop(std::move(onStop));
}

void RNInstanceCAPI::destroySurface(facebook::react::Tag surfaceId) {
  DLOG(INFO) << "RNInstanceCAPI::destroySurface";
  auto it = m_surfaceById.find(surfaceId);
  if (it == m_surfaceById.end()) {
    return;
  }
  auto surface = it->second;
  auto arkUISurface = std::dynamic_pointer_cast<ArkUISurface>(surface);
  if (arkUISurface != nullptr) {
    m_scheduler->unregisterSurface(arkUISurface->getSurfaceHandler());
  }

  m_surfaceById.erase(it);
}

void RNInstanceCAPI::setSurfaceDisplayMode(
    facebook::react::Tag surfaceId,
    facebook::react::DisplayMode displayMode) {
  DLOG(INFO) << "RNInstanceCAPI::setSurfaceDisplayMode";
  facebook::react::TraceSection s(
      "#RNOH::RNInstanceCAPI::setSurfaceDisplayMode");
  auto it = m_surfaceById.find(surfaceId);
  if (it == m_surfaceById.end()) {
    return;
  }
  it->second->setDisplayMode(displayMode);
}

void RNInstanceCAPI::onConfigurationChange(folly::dynamic const& payload) {
  RNInstanceInternal::onConfigurationChange(payload);
  if (payload.isNull()) {
    return;
  }
  if (!payload.count("screenPhysicalPixels")) {
    return;
  }
  const auto& screenPhysicalPixels = payload["screenPhysicalPixels"];
  const auto& scale = screenPhysicalPixels["scale"];
  const auto& fontScale = screenPhysicalPixels["fontScale"];
  if (!scale.isDouble() || !fontScale.isDouble()) {
    return;
  }
  for (const auto& [_, surface] : m_surfaceById) {
    surface->setDisplayMetrics(scale.asDouble(), fontScale.asDouble());
  }
}

ComponentInstance::Shared RNInstanceCAPI::findComponentInstanceByTag(
    facebook::react::Tag tag) {
  return m_componentInstanceRegistry->findByTag(tag);
}

std::optional<facebook::react::Tag>
RNInstanceCAPI::findComponentInstanceTagById(const std::string& id) {
  return m_componentInstanceRegistry->findTagById(id);
}

std::optional<std::string> RNInstanceCAPI::getNativeNodeIdByTag(
    facebook::react::Tag tag) const {
  auto componentInstance = m_componentInstanceRegistry->findByTag(tag);
  if (componentInstance == nullptr) {
    return std::nullopt;
  }
  return componentInstance->getLocalRootArkUINode().getId();
}

std::shared_ptr<TurboModuleProvider>
RNInstanceCAPI::createTurboModuleProvider() {
  DLOG(INFO) << "RNInstanceCAPI::createTurboModuleProvider";
  auto turboModuleProvider = std::make_shared<TurboModuleProvider>(
      std::make_shared<facebook::react::RuntimeSchedulerCallInvoker>(
          m_runtimeScheduler),
      std::move(m_turboModuleFactory),
      m_eventDispatcher,
      std::move(m_jsQueue),
      m_weakSelf);
  turboModuleProvider->installJSBindings(
      m_reactInstance->getUnbufferedRuntimeExecutor());
  return turboModuleProvider;
}

std::optional<Surface::Weak> RNInstanceCAPI::getSurfaceByRootTag(
    facebook::react::Tag rootTag) {
  auto it = m_surfaceById.find(rootTag);
  if (it == m_surfaceById.end()) {
    return std::nullopt;
  }
  return it->second;
};

void RNInstanceCAPI::installJSBindings(facebook::jsi::Runtime& rt) {
  // install `console.log` (etc.) implementation
  react::bindNativeLogger(rt, nativeLogger);
  // install tracing functions
  rnoh::setupTracing(rt);
  facebook::react::bindHasComponentProvider(
      rt, [this](std::string const& name) {
        return m_componentJSIBinderByName.contains(name);
      });

  facebook::react::LegacyUIManagerConstantsProviderBinding::install(
      rt,
      "getConstantsForViewManager",
      [this](auto& rt, auto const& name) -> jsi::Value {
        auto componentJSIBinder = m_componentJSIBinderByName.find(name);
        if (componentJSIBinder != m_componentJSIBinderByName.end()) {
          return componentJSIBinder->second->createBindings(rt);
        }
        LOG(ERROR) << "Couldn't find ComponentJSIBinder for: " << name;
        return nullptr;
      });

  facebook::react::LegacyUIManagerConstantsProviderBinding::install(
      rt, "getConstants", [](auto& rt) {
        return facebook::jsi::Value(facebook::jsi::Object(rt));
      });
}

} // namespace rnoh
