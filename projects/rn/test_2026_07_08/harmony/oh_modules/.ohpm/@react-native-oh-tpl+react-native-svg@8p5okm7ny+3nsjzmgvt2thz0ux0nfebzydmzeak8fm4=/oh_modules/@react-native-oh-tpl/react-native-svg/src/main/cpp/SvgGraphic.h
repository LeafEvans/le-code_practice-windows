/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 *
 * This file incorporates from the OpenHarmony project, licensed under
 * the Apache License, Version 2.0. Specifically:
 * - [OpenHarmony/arkui_ace_engine] (https://gitee.com/openharmony/arkui_ace_engine)
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy
 * of the License at:
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

// from ArkUI "frameworks/core/components_ng/svg/parse/svg_graphic.h"
#pragma once

#include "SvgNode.h"
#include "utils/StringUtils.h"
#include "utils/SvgMarkerPositionUtils.h"
#include "drawing/Brush.h"
#include "drawing/Path.h"
#include "drawing/Pen.h"
#include <native_drawing/drawing_brush.h>
#include <native_drawing/drawing_path_effect.h>
#include <native_drawing/drawing_pen.h>


namespace rnoh {
namespace svg {

class SvgGraphic : virtual public SvgNode {
public:
     SvgGraphic() : SvgNode() {}
    ~SvgGraphic() noexcept override = default; 


    void OnDraw(OH_Drawing_Canvas *canvas) override;
protected:
    drawing::Path path_ {};
    drawing::Brush fillBrush_ {};
    drawing::Pen strokePen_ {};

    // Use Brush to draw fill
    void OnGraphicFill(OH_Drawing_Canvas *canvas);
    // Use Pen to draw stroke
    void OnGraphicStroke(OH_Drawing_Canvas *canvas);

    bool UpdateFillStyle(bool antiAlias = true);
    bool UpdateStrokeStyle(bool antiAlias = true);
    void UpdateGradient(std::optional<Gradient> &gradient);
    void SetFillGradientStyle(double opacity);
    void SetStrokeGradientStyle(double opacity);
    bool SetPatternStyle();
    void UpdateLineDash();

    std::vector<PathElement> elements_;

private:
    void DrawMarker(OH_Drawing_Canvas *canvas);
    // to be done? Color Filter;
};

} // namespace svg
} // namespace rnoh