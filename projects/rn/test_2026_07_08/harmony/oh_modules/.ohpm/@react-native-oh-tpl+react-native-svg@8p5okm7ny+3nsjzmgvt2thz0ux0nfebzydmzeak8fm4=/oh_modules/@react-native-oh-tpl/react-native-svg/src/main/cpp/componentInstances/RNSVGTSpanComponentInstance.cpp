/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "RNSVGTSpanComponentInstance.h"
#include "SvgTSpan.h"

namespace rnoh {
namespace svg {

RNSVGTSpanComponentInstance::RNSVGTSpanComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(m_svgTSpan);
}

void RNSVGTSpanComponentInstance::UpdateElementProps() {
    m_svgTSpan->UpdateCommonProps(m_props);
    m_svgTSpan->content_ = m_props->content;
    m_svgTSpan->UpdateFontProps(m_props);
    m_svgTSpan->UpdateTextProps(m_props);
}

} // namespace svg
} // namespace rnoh
