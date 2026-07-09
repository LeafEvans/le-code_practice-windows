/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "RNSVGBaseComponentInstance.h"
#include "SvgGradient.h"

namespace rnoh {
namespace svg {

class RNSVGRadialGradientComponentInstance
    : public RNSVGBaseComponentInstance<facebook::react::RNSVGRadialGradientShadowNode> {
public:
    explicit RNSVGRadialGradientComponentInstance(Context context);

protected:
    void UpdateElementProps() override;

private:
    std::shared_ptr<SvgGradient> m_svgRadialGradient = std::make_shared<SvgGradient>(GradientType::RADIAL);
};

} // namespace svg
} // namespace rnoh