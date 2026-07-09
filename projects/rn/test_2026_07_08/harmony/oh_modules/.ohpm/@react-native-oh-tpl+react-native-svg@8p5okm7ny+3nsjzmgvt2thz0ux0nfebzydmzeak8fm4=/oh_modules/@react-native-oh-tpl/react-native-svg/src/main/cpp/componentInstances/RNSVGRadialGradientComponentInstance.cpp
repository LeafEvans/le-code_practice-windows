/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "RNSVGRadialGradientComponentInstance.h"

namespace rnoh {
namespace svg {

RNSVGRadialGradientComponentInstance::RNSVGRadialGradientComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(m_svgRadialGradient);
}

void RNSVGRadialGradientComponentInstance::UpdateElementProps() {
    m_svgRadialGradient->UpdateHrefRenderProps(m_props);
    m_svgRadialGradient->SetAttrGradientUnits(m_props->gradientUnits); // first set attr gradientUnits
    m_svgRadialGradient->SetAttrFx(m_props->fx);
    m_svgRadialGradient->SetAttrFy(m_props->fy);
    m_svgRadialGradient->SetAttrCx(m_props->cx);
    m_svgRadialGradient->SetAttrCy(m_props->cy);
    m_svgRadialGradient->SetAttrRx(m_props->rx);
    m_svgRadialGradient->SetAttrRy(m_props->ry);
    m_svgRadialGradient->SetAttrGradient(m_props->gradient);
    m_svgRadialGradient->SetAttrGradientTransforms(m_props->gradientTransform);
}

} // namespace svg
} // namespace rnoh
