/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "RNSVGMarkerComponentInstance.h"

namespace rnoh {
namespace svg {

RNSVGMarkerComponentInstance::RNSVGMarkerComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(m_svgMarker);
}

void RNSVGMarkerComponentInstance::UpdateElementProps() {
    m_svgMarker->UpdateCommonProps(m_props);
    m_svgMarker->setRefX(m_props->refX);
    m_svgMarker->setRefY(m_props->refY);
    m_svgMarker->setMarkerWidth(m_props->markerWidth);
    m_svgMarker->setMarkerHeight(m_props->markerHeight);
    m_svgMarker->setMarkerUnits(m_props->markerUnits);
    m_svgMarker->setOrient(m_props->orient);
    m_svgMarker->setMinX(m_props->minX);
    m_svgMarker->setMinY(m_props->minY);
    m_svgMarker->setVbWidth(m_props->vbWidth);
    m_svgMarker->setVbHeight(m_props->vbHeight);
    m_svgMarker->setAlign(m_props->align);
    m_svgMarker->setMeetOrSlice(m_props->meetOrSlice);
}

} // namespace svg
} // namespace rnoh
