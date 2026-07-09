/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "RNSVGBaseComponentInstance.h"
#include "svgImage/RNSVGImageShadowNode.h"
#include "SvgImage.h"
#include "downloadUtils/ImageSourceResolver.h"
#include "downloadUtils/HttpTaskProcessor.h"

namespace rnoh {
namespace svg {

class RNSVGImageComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGImageShadowNode>,
                                    public ImageSourceResolver::ImageSourceUpdateListener {
public:
    explicit RNSVGImageComponentInstance(Context context);

protected:
    void UpdateElementProps() override;

    void onPropsChanged(SharedConcreteProps const &props) override;

    // used for find local cache of uri, if not find return uri
    std::string FindLocalCacheByUri(std::string const &uri);

    // ImageSourceUpdateListener download success callback
    void onImageSourceCacheUpdate(std::string imageUri) override;

    // ImageSourceUpdateListener download fail callback
    void onImageSourceCacheDownloadFileFail() override;

private:
    std::shared_ptr<SvgImage> m_svgImage = std::make_shared<SvgImage>();
    facebook::react::ImageSource m_src;
};

} // namespace svg
} // namespace rnoh