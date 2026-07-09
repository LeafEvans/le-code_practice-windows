/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "RNSVGUseComponentInstance.h"

namespace rnoh {
namespace svg {

RNSVGUseComponentInstance::RNSVGUseComponentInstance(Context context) : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(m_svgUse);
}

void RNSVGUseComponentInstance::UpdateElementProps() {
    m_svgUse->UpdateCommonProps(m_props);
    m_svgUse->x = std::stof(m_props->x);
    m_svgUse->y = std::stof(m_props->y);
    m_svgUse->width = std::stof(m_props->width);
    m_svgUse->height = std::stof(m_props->height);
    m_svgUse->href = m_props->href;
}

} // namespace svg
} // namespace rnoh
