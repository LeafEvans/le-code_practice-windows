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

class RNSVGLinearGradientComponentInstance
    : public RNSVGBaseComponentInstance<facebook::react::RNSVGLinearGradientShadowNode> {
public:
    explicit RNSVGLinearGradientComponentInstance(Context context);

protected:
    void UpdateElementProps() override;

private:
    std::shared_ptr<SvgGradient> m_svgLinearGradient = std::make_shared<SvgGradient>(GradientType::LINEAR);
};

} // namespace svg
} // namespace rnoh