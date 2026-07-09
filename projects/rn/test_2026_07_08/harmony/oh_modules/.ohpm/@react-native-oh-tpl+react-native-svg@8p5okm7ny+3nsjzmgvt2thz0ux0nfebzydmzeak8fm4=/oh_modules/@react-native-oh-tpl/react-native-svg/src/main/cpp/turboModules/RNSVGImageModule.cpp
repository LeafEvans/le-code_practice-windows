/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "RNSVGImageModule.h"
#include "utils/StringUtils.h"

using namespace facebook;

namespace rnoh {
namespace svg {
RNSVGImageModule::RNSVGImageModule(const ArkTSTurboModule::Context ctx, const std::string name)
    : ArkTSTurboModule(ctx, name) {
    methodMap_ = {
        ARK_ASYNC_METHOD_METADATA(getCacheDir, 0),
    };

    // 获取缓存路径前缀
    auto cache = this->callSync("getCacheDir", {});
    m_fileCacheDir = cache.asString() + "/";
    m_imageSourceResolver = std::make_shared<ImageSourceResolver>(m_fileCacheDir);

    fs::path directoryPath = m_fileCacheDir;
    // 将已有的缓存文件名放入remoteImageSourceMap
    if (fs::exists(directoryPath) && fs::is_directory(directoryPath)) {
        for (const auto &entry : fs::directory_iterator(directoryPath)) {
            if (fs::is_regular_file(entry.path())) {
                m_imageSourceResolver->remoteImageSourceMap_.put(entry.path().filename(), true);
            }
        }
    }
}

/**
 *
 * @param uri 图片uri
 * @param headers 请求头
 */
void RNSVGImageModule::downloadImage(const std::string &uri, const std::map<std::string, std::string> &headers) {
    HttpTaskProcessor *processor = new HttpTaskProcessor();
    processor->instance_ = m_imageSourceResolver;
    processor->filePath_ = m_fileCacheDir + StringUtils::generateHashedFileName(uri);

    if (headers.empty()) {
        processor->launchHttpRequest(uri.c_str());
    } else {
        processor->launchHttpRequestWithHeaders(uri.c_str(), headers);
    }
}

} // namespace svg
} // namespace rnoh
