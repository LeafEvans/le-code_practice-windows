/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "RNSVGClipPathComponentInstance.h"

namespace rnoh {
namespace svg {

RNSVGClipPathComponentInstance::RNSVGClipPathComponentInstance(Context context)
    : RNSVGBaseComponentInstance(std::move(context)) {
    SetSvgNode(m_svgClipPath);
}

void RNSVGClipPathComponentInstance::UpdateElementProps() { m_svgClipPath->UpdateCommonProps(m_props); }

} // namespace svg
} // namespace rnoh
