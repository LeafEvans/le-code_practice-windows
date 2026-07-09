/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "RNSVGPathComponentInstance.h"

namespace rnoh {
namespace svg {

RNSVGPathComponentInstance::RNSVGPathComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(m_svgPath);
}

void RNSVGPathComponentInstance::UpdateElementProps() {
    DLOG(INFO) << "[RNSVGPathCI] d: " << m_props->d;
    DLOG(INFO) << "[RNSVGPathCI] pointScaleFactor: " << m_layoutMetrics.pointScaleFactor;
    m_svgPath->UpdateCommonProps(m_props);
    // Check if path data or scale factor has changed
    if (m_cacheD != m_props->d || m_cacheScale != m_layoutMetrics.pointScaleFactor) {
        m_svgPath->setD(m_props->d); // Update path data
        m_cacheD = m_props->d;       // Cache the new path data
        m_cacheScale = m_layoutMetrics.pointScaleFactor; // Cache the new scale factor
    } else {
        LOG(INFO) << "[RNSVGPathCI] No changes detected. Skipping update.";
    }
}

} // namespace svg
} // namespace rnoh
