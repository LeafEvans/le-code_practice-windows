/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "SvgGraphic.h"
#include <native_drawing/drawing_point.h>
#include <native_drawing/drawing_canvas.h>
#include <native_drawing/drawing_path.h>
#include "SvgSymbol.h"

namespace rnoh {
namespace svg {

    class SvgUse : public SvgGraphic {
    public:
        SvgUse() = default;
        ~SvgUse() override = default;
        float x;
        float y;
        float width;
        float height;
        float opacity;
        std::string href;

        void OnDraw(OH_Drawing_Canvas *canvas) override;
    
        drawing::Path AsPath() override;
    private:
        class AttributeScope {
            public:
                explicit AttributeScope(const std::shared_ptr<SvgNode>& node);
                ~AttributeScope();

            private:
                SvgBaseAttribute attributes_;
                std::shared_ptr<SvgNode> node_;
            };
                // SvgAttributes useAttr_;
        };

} // namespace svg
} // namespace rnoh