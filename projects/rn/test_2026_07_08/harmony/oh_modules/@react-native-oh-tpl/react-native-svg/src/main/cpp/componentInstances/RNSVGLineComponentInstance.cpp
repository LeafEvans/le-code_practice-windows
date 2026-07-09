/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "RNSVGLineComponentInstance.h"

namespace rnoh {
namespace svg {

RNSVGLineComponentInstance::RNSVGLineComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(m_svgLine);
}

void RNSVGLineComponentInstance::UpdateElementProps() {
    m_svgLine->UpdateCommonProps(m_props);
    m_svgLine->SetX1(m_props->x1);
    m_svgLine->SetY1(m_props->y1);
    m_svgLine->SetX2(m_props->x2);
    m_svgLine->SetY2(m_props->y2);
}

} // namespace svg
} // namespace rnoh
