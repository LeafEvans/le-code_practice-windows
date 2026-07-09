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

// from ArkUI "frameworks/core/components/declaration/svg/svg_base_declaration.h"
#pragma once

#include "Attribute.h"
#include "properties/SvgPaintState.h"
#include <string>
#include <vector>

namespace rnoh {
namespace svg {

const char VALUE_NONE[] = "none";

struct SvgBaseAttribute : Attribute {
    double selfOpacity = 1.0; // opacity declared in tag attribute
    double opacity = 1.0; // multiplied with parent opacity. The actual opacity to be drawn
    float smoothEdge = 0.0f;
    FillState fillState;
    StrokeState strokeState;
//     SvgTextStyle textStyle;
    std::vector<double> transform; // transform matrix
    std::string transformOrigin;
    std::string filterId;
    std::string maskId;
    std::string id;
    std::string markerStart;
    std::string markerMid;
    std::string markerEnd;
    std::string clipPath;
    ClipState clipState;

    void InheritFromUse(const SvgBaseAttribute& parent)
    {
        opacity = selfOpacity * parent.opacity;
        fillState.Inherit(parent.fillState);
        strokeState.Inherit(parent.strokeState);
        clipState.Inherit(parent.clipState);
    }

    void Inherit(const SvgBaseAttribute& parent)
    {
        opacity = selfOpacity * parent.opacity;
        fillState.Inherit(parent.fillState);
        strokeState.Inherit(parent.strokeState);
        clipState.Inherit(parent.clipState);
    }
};

} // namespace svg
} // namespace rnoh
