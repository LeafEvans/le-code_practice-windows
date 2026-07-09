/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include <native_drawing/drawing_text_typography.h>
#include "TypographyStyle.h"

namespace rnoh::drawing {

class Typography {
public:
    Typography(OH_Drawing_TypographyCreate *handler)
        : typ_(TypUPtr(OH_Drawing_CreateTypography(handler), OH_Drawing_DestroyTypography)) {}
    OH_Drawing_Typography *operator&() { return typ_.get(); }

private:
    using TypUPtr = std::unique_ptr<OH_Drawing_Typography, decltype(&OH_Drawing_DestroyTypography)>;
    TypUPtr typ_;
};

} // namespace rnoh::drawing