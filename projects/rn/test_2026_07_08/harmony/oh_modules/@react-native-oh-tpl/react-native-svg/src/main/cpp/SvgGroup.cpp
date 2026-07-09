/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "SvgGroup.h"

namespace rnoh {
namespace svg {

void SvgGroup::InitGroupFlag() {
    hrefFill_ = true;
    hrefRender_ = true;
    passStyle_ = true;
    inheritStyle_ = true;
    drawTraversed_ = true;
}

void SvgGroup::OnInitStyle() {
    if (!font_) {
        InitFont(GetScale());
    }
    for (auto &child : children_) {
        if (auto childG = std::dynamic_pointer_cast<FontHolderBase>(child)) {
            childG->InheritFont(font_, child->GetScale());
        }
    }
}

} // namespace svg
} // namespace rnoh