/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "RNSVGSymbolComponentInstance.h"

namespace rnoh {
namespace svg {

RNSVGSymbolComponentInstance::RNSVGSymbolComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(m_svgSymbol);
}

void RNSVGSymbolComponentInstance::UpdateElementProps() {
    // set attribute to svgSymbol.
    m_svgSymbol->UpdateCommonProps(m_props);
    m_svgSymbol->mMinX = m_props->minX;
    m_svgSymbol->mMinY = m_props->minY;
    m_svgSymbol->mVbWidth = m_props->vbWidth;
    m_svgSymbol->mVbHeight = m_props->vbHeight;
    m_svgSymbol->mMeetOrSlice = m_props->meetOrSlice;
    m_svgSymbol->mAlign = m_props->align;
}

} // namespace svg
} // namespace rnoh
