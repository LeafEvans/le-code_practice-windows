/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "RNSVGGroupComponentInstance.h"

namespace rnoh {
namespace svg {

RNSVGGroupComponentInstance::RNSVGGroupComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(m_svgGroup);
}

void RNSVGGroupComponentInstance::UpdateElementProps() {
    m_svgGroup->UpdateCommonProps(m_props);
    m_svgGroup->UpdateFontProps(m_props);
}

} // namespace svg
} // namespace rnoh