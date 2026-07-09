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

#pragma once

#include "SvgNode.h"
#include <native_drawing/drawing_path.h>

namespace rnoh {
namespace svg {

class SvgQuote : public SvgNode {
public:
    SvgQuote() : SvgNode() { InitHrefFlag(); }
    ~SvgQuote() override = default;

    drawing::Path getClipPath(drawing::Path path) {
        DLOG(INFO) << "[SvgQuote] getClipPath";
        for (const auto &child : children_) {
            auto childPath = child->AsPath();
            path.AddPath(childPath);
        }
        return path;
    }

    drawing::Path getClipPath(drawing::Path path, drawing::Path::OpMode op) {
        DLOG(INFO) << "[SvgQuote] getClipPath with op, op = " << op;
        for (const auto &child : children_) {
            auto childPath = child->AsPath();
            path.Op(childPath, op);
        }
        return path;
    }

    drawing::Path AsPath() override {
        DLOG(INFO) << "[SvgQuote] AsPath";
        drawing::Path path;

        if (attributes_.clipState.IsEvenodd()) {
            return getClipPath(path);
        } else {
            return getClipPath(path, drawing::Path::OpMode::PATH_OP_MODE_UNION);
        }
    }

    void Draw(OH_Drawing_Canvas *canvas) override {
        // render composition on other svg tags
        DLOG(INFO) << "[SvgQuote] Draw";
        OnDrawTraversedBefore(canvas);
        OnDrawTraversed(canvas);
        OnDrawTraversedAfter(canvas);
    }

protected:
    virtual void OnDrawTraversedBefore(OH_Drawing_Canvas *canvas) {}
    virtual void OnDrawTraversedAfter(OH_Drawing_Canvas *canvas) {}

    // mask/pattern/filter/clipPath
    void InitHrefFlag() {
        hrefFill_ = true;
        hrefRender_ = false;
        passStyle_ = true;
        inheritStyle_ = false;
        drawTraversed_ = false;
    }
};

} // namespace svg
} // namespace rnoh
