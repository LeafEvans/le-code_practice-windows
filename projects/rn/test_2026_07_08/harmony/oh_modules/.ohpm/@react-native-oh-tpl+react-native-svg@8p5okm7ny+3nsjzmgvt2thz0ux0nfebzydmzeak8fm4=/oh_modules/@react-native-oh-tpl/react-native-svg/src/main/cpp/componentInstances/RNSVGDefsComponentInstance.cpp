/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "RNSVGDefsComponentInstance.h"
#include "SvgDefs.h"

namespace rnoh {
namespace svg {

RNSVGDefsComponentInstance::RNSVGDefsComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(m_svgDefs);
}

void RNSVGDefsComponentInstance::UpdateElementProps() { m_svgDefs->UpdateHrefRenderProps(m_props); }

} // namespace svg
} // namespace rnoh
