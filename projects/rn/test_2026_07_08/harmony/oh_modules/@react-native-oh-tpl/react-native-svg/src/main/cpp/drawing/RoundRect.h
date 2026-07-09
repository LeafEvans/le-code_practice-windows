/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include <memory>
#include <native_drawing/drawing_round_rect.h>
#include "Rect.h"

namespace rnoh {
namespace drawing {
class RoundRect final {
    using UniqueNativeRoundRect = std::unique_ptr<OH_Drawing_RoundRect, decltype(&OH_Drawing_RoundRectDestroy)>;

    using CornerPos = OH_Drawing_CornerPos;
    using CornerRadii = OH_Drawing_Corner_Radii;

public:
    RoundRect(Rect rect, float rx, float ry);
    RoundRect(RoundRect const &) = delete;
    RoundRect &operator=(RoundRect const &) = delete;
    RoundRect(RoundRect &&) = default;
    RoundRect &operator=(RoundRect &&) = default;
    ~RoundRect() noexcept = default;

    void SetCorner(CornerPos pos, CornerRadii radii);
    CornerRadii GetCorner(CornerPos pos);

    OH_Drawing_RoundRect *get() const { return roundRect_.get(); }

private:
    Rect rect_;
    UniqueNativeRoundRect roundRect_;
};
} // namespace drawing
} // namespace rnoh