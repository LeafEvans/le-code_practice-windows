/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "SvgGroup.h"
#include "TextBase.h"

namespace rnoh {
namespace svg {

class SvgText : public SvgGroup, public TextBase {
public:
    SvgText() = default;
    ~SvgText() override = default;

    void OnDraw(OH_Drawing_Canvas *canvas) override;

private:
    void GlyphTraversal(OH_Drawing_Canvas *canvas);
};

} // namespace svg
} // namespace rnoh