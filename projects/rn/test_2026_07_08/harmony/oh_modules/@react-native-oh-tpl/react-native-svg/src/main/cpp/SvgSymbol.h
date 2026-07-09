/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "SvgGraphic.h"
#include "properties/ViewBox.h"

namespace rnoh {
namespace svg {

class SvgSymbol : public SvgGraphic {
public:
    SvgSymbol() : SvgGraphic() { InitSymbolFlag(); }
    ~SvgSymbol() override = default;

    void InitSymbolFlag() {
        hrefFill_ = false;
        hrefRender_ = false;
        inheritStyle_ = false;
        drawTraversed_ = false;
    }
    float mMinX = 0.0f;
    float mMinY = 0.0f;
    float mVbWidth = 0.0f;
    float mVbHeight = 0.0f;
    std::string mAlign;
    int mMeetOrSlice = -1;
    void InitDefsFlag();
    void drawSymbol(OH_Drawing_Canvas *canvas, float width, float height);
};

} // namespace svg
} // namespace rnoh
