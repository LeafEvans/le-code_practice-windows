/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "RNSVGTextComponentInstance.h"

namespace rnoh {
namespace svg {

RNSVGTextComponentInstance::RNSVGTextComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(m_svgText);
}

void RNSVGTextComponentInstance::UpdateElementProps() {
    m_svgText->UpdateCommonProps(m_props);
    m_svgText->UpdateFontProps(m_props);
    m_svgText->UpdateTextProps(m_props);
}

} // namespace svg
} // namespace rnoh
