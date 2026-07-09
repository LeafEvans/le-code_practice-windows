/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "RNSVGRectComponentInstance.h"

namespace rnoh {
namespace svg {

RNSVGRectComponentInstance::RNSVGRectComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(m_svgRect);
}

void RNSVGRectComponentInstance::UpdateElementProps() {
        m_svgRect->UpdateCommonProps(m_props);
        m_svgRect->SetX(m_props->x);
        m_svgRect->SetY(m_props->y);
        m_svgRect->SetWidth(m_props->width);
        m_svgRect->SetHeight(m_props->height);
        if (m_props->rx.size() != 0) {
            m_svgRect->SetRX(m_props->rx);
        }
        if (m_props->ry.size() != 0) {
            m_svgRect->SetRY(m_props->ry);
        }
}

} // namespace svg
} // namespace rnoh
