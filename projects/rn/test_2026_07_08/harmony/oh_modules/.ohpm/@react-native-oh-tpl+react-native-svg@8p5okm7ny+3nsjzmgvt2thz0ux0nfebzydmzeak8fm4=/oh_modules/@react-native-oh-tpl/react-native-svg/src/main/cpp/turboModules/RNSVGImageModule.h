/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include <ReactCommon/TurboModule.h>
#include "RNOH/ArkTSTurboModule.h"
#include "downloadUtils/ImageSourceResolver.h"
#include "downloadUtils/HttpTaskProcessor.h"

namespace rnoh {
namespace svg {

class JSI_EXPORT RNSVGImageModule : public ArkTSTurboModule {
public:
    RNSVGImageModule(const ArkTSTurboModule::Context ctx, const std::string name);

    ~RNSVGImageModule() { HttpTaskProcessor::destroyAllTask(); }

    void downloadImage(const std::string &uri, const std::map<std::string, std::string> &headers);

    std::shared_ptr<ImageSourceResolver> getImageSourceResolver() { return m_imageSourceResolver; }

private:
    std::string m_fileCacheDir;
    std::shared_ptr<ImageSourceResolver> m_imageSourceResolver = nullptr;
};
} // namespace svg
} // namespace rnoh
