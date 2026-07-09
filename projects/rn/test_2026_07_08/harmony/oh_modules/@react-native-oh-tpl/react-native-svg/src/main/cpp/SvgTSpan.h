/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include <cmath>
#include "SvgGraphic.h"
#include "SvgText.h"
#include <native_drawing/drawing_text_typography.h>
#include "SvgTextPath.h"
#include "utils/GlyphContext.h"
#include "drawing/TypographyStyle.h"
#include "TextBase.h"
#include "FontHolderBase.h"

namespace rnoh {
namespace svg {

class SvgTSpan : public SvgGraphic, public TextBase, public FontHolderBase {
public:
    SvgTSpan() {
        hrefFill_ = true;
        hrefRender_ = true;
        passStyle_ = true;
        inheritStyle_ = true;
        drawTraversed_ = true;
    }
    ~SvgTSpan() override = default;

    void OnDraw(OH_Drawing_Canvas *canvas) override;

    void SetTextPathRef(std::shared_ptr<SvgTextPath> textPath) { textPath_ = textPath; }

    double getTextAnchorOffset(TextAnchor textAnchor, const double &textMeasure);

    std::string content_;

    Rect AsBounds() override;

    /**
     * @brief TSpan also supports the scenario with child nodes. Updates the font properties of the child node,
     *        inheriting from the parent node if the properties are empty.
     */
    void OnInitStyle() override {
        if (!font_) {
            InitFont(GetScale());
        }
        for (auto &child : children_) {
            if (auto childG = std::dynamic_pointer_cast<FontHolderBase>(child)) {
                childG->InheritFont(font_, child->GetScale());
            }
        }
    };

private:
    /**
     * @brief TSpan also supports the scenario with child nodes. Updates the text properties of the child node,
     *        inheriting from the parent node if the properties are empty.
     * @param child Represents the child node object.
     */
    void UpdateChildTextProps(std::shared_ptr<SvgTSpan> child) {
        UpdateIfEmpty(child->y_, y_);
        UpdateIfEmpty(child->x_, x_);
        UpdateIfEmpty(child->dy_, dy_);
        UpdateIfEmpty(child->dx_, dx_);
        UpdateIfEmpty(child->rotate_, rotate_);
    }

    void UpdateIfEmpty(std::vector<Dimension> &childProp, const std::vector<Dimension> &parentProp) {
        if (childProp.empty() && !parentProp.empty()) {
            childProp = parentProp;
        }
    }

    void DrawTextPath(OH_Drawing_Canvas *canvas);

    void DrawText(OH_Drawing_Canvas *canvas);

    drawing::TypographyStyle PrepareTypoStyle();

    /**
     * @return true if spacing needs to be adjusted.
     */
    bool AdjustSpacing(OH_Drawing_Canvas *canvas, double textMeasure, double &scaleSpacingAndGlyphs);

    double CalcBaselineShift(OH_Drawing_TypographyCreate *handler, OH_Drawing_TextStyle *style,
                             const OH_Drawing_Font_Metrics &fm);

    std::shared_ptr<SvgTextPath> textPath_;

    double boundsWidth_ = 0;
    double boundsHeight_ = 0;
    double boundsX_ = 0;
    double boundsY_ = 0;
};

} // namespace svg
} // namespace rnoh