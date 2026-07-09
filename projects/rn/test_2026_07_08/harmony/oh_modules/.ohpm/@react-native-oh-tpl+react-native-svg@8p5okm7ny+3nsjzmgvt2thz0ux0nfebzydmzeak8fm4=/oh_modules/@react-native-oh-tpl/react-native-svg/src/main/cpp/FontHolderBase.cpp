/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "FontHolderBase.h"

namespace rnoh {
namespace svg {

void FontHolderBase::InheritFont(const std::shared_ptr<FontData> &parent, double scale) {
    if (fp_.Empty()) {
        // share parent font to save memory
        font_ = parent;
    } else {
        font_ = std::make_shared<FontData>(fp_, *parent, scale);
    }
}

} // namespace svg
} // namespace rnoh