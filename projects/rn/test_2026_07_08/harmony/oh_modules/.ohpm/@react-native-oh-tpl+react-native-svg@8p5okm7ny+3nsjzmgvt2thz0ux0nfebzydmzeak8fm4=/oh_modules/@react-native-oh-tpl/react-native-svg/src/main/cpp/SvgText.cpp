/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include <memory>
#include "SvgText.h"
#include "drawing/TextStyle.h"
#include "drawing/TypographyStyle.h"
#include "SvgTSpan.h"

namespace rnoh {
namespace svg {

void SvgText::GlyphTraversal(OH_Drawing_Canvas *canvas) {
    if (!glyphCtx_) {
        InitGlyph(canvas, scale_);
    }
    for (auto const &child : children_) {
        if (auto span = std::dynamic_pointer_cast<TextBase>(child)) {
            span->SetGlyphContext(glyphCtx_);
            if (!span->hasAlignmentBaseline()) {
                span->setAlignmentBaseline(align_);
            }
            if (!span->hasBaselineShift()) {
                span->setBaselineShift(baselineShift_);
            }
        }
    }
}
void SvgText::OnDraw(OH_Drawing_Canvas *canvas) {
    GlyphTraversal(canvas);
    glyphCtx_->pushContext(true, shared_from_this(), x_, y_, dx_, dy_, rotate_);
}

} // namespace svg
} // namespace rnoh