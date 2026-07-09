/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "RNSVGLinearGradientComponentInstance.h"

namespace rnoh {
namespace svg {

RNSVGLinearGradientComponentInstance::RNSVGLinearGradientComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(m_svgLinearGradient);
}

void RNSVGLinearGradientComponentInstance::UpdateElementProps() {
    m_svgLinearGradient->UpdateHrefRenderProps(m_props);
    m_svgLinearGradient->SetAttrGradientUnits(m_props->gradientUnits); // first set attr gradientUnits
    m_svgLinearGradient->SetAttrX1(m_props->x1);
    m_svgLinearGradient->SetAttrY1(m_props->y1);
    m_svgLinearGradient->SetAttrX2(m_props->x2);
    m_svgLinearGradient->SetAttrY2(m_props->y2);
    m_svgLinearGradient->SetAttrGradient(m_props->gradient);
    m_svgLinearGradient->SetAttrGradientTransforms(m_props->gradientTransform);
}

} // namespace svg
} // namespace rnoh
