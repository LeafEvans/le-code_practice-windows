/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "RNSVGBaseComponentInstance.h"
#include "SvgMask.h"

namespace rnoh {
namespace svg {

class RNSVGMaskComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGMaskShadowNode> {
public:
    explicit RNSVGMaskComponentInstance(Context context);

protected:
    void UpdateElementProps() override;

private:
    std::shared_ptr<SvgMask> m_svgMask = std::make_shared<SvgMask>();
};

} // namespace svg
} // namespace rnoh