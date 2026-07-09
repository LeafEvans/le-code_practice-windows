/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "RNSVGMaskComponentInstance.h"

namespace rnoh {
namespace svg {

RNSVGMaskComponentInstance::RNSVGMaskComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(m_svgMask);
}

void RNSVGMaskComponentInstance::UpdateElementProps() {
    DLOG(INFO) << "[RNSVGMaskCI] onPropsChanged maskUnits: " << m_props->maskUnits;
    DLOG(INFO) << "[RNSVGMaskCI] onPropsChanged maskContentUnits: " << m_props->maskContentUnits;
    m_svgMask->UpdateCommonProps(m_props);
    // set attribute to svgMask.
    m_svgMask->setMaskUnits(m_props->maskUnits);
    m_svgMask->setMaskContentUnits(m_props->maskContentUnits);
    m_svgMask->setMaskX(m_props->x);
    m_svgMask->setMaskY(m_props->y);
    m_svgMask->setMaskHeight(m_props->height);
    m_svgMask->setMaskWidth(m_props->width);
}

} // namespace svg
} // namespace rnoh
