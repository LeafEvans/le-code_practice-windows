/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "RNSVGPatternComponentInstance.h"

namespace rnoh {
namespace svg {

RNSVGPatternComponentInstance::RNSVGPatternComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(m_svgPattern);
}

void RNSVGPatternComponentInstance::UpdateElementProps() {
    // set attribute to svgPattern
    m_svgPattern->UpdateCommonProps(m_props);
    m_svgPattern->setPatternX(StringUtils::FromString(m_props->x));
    m_svgPattern->setPatternY(StringUtils::FromString(m_props->y));
    m_svgPattern->setWidth(StringUtils::FromString(m_props->width));
    m_svgPattern->setHeight(StringUtils::FromString(m_props->height));
    m_svgPattern->setPatternUnits(m_props->patternUnits);
    m_svgPattern->setPatternContentUnits(m_props->patternContentUnits);
    m_svgPattern->setViewBox(Rect(m_props->minX, m_props->minY, m_props->vbWidth, m_props->vbHeight));
    m_svgPattern->setmMinX(m_props->minX);
    m_svgPattern->setmMinY(m_props->minY);
    m_svgPattern->setmVbWidth(m_props->vbWidth);
    m_svgPattern->setmVbHeight(m_props->vbHeight);
    m_svgPattern->setmAlign(m_props->align);
    m_svgPattern->setmMeetOrSlice(m_props->meetOrSlice);
    m_svgPattern->setPatternTransforms(m_props->patternTransform);
}

} // namespace svg
} // namespace rnoh
