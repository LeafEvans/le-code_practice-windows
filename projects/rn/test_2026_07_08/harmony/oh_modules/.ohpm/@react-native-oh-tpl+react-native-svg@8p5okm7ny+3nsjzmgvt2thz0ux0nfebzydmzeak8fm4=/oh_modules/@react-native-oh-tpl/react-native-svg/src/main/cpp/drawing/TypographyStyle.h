/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include <memory>
#include <optional>
#include <native_drawing/drawing_text_typography.h>

#include "TextStyle.h"
#include "properties/Font.h"

namespace rnoh::drawing {

class TypographyStyle final {

    using UniqueTypographyStyle =
        std::unique_ptr<OH_Drawing_TypographyStyle, decltype(&OH_Drawing_DestroyTypographyStyle)>;

public:
    TypographyStyle();
    ~TypographyStyle() noexcept;

    TypographyStyle(const TypographyStyle &) = delete;
    TypographyStyle &operator=(const TypographyStyle &) = delete;

    TypographyStyle(TypographyStyle &&other) = default;
    TypographyStyle &operator=(TypographyStyle &&other) = default;

    void SetTextStyle(TextStyle textStyle);

    void Update(const std::shared_ptr<svg::FontData> &style);

    UniqueTypographyStyle typographyStyle_;
    TextStyle::UniqueTextStyle textStyle_ = {nullptr, OH_Drawing_DestroyTextStyle};
};

} // namespace rnoh::drawing