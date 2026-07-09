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

// from ArkUI "frameworks/base/geometry/dimension.cpp"
#include "Dimension.h"
#include "Size.h"
namespace rnoh {
namespace svg {

double Dimension::RelativeConvertToPx(double baseLen, double scale) const {
    switch (Unit()) {
    case DimensionUnit::PERCENT: {
        return Value() * baseLen;
    }
    case DimensionUnit::PX:
        return Value();
    case DimensionUnit::VP:
        return ConvertToPx(scale);
    default:
        return ConvertToPx(scale);
    }
}

double Dimension::ConvertToPx(const Size &viewPort, SvgLengthType type, double scale) const {
    switch (type) {
    case SvgLengthType::HORIZONTAL: {
        return RelativeConvertToPx(viewPort.Width(), scale);
    }
    case SvgLengthType::VERTICAL:
        return RelativeConvertToPx(viewPort.Height(), scale);
    case SvgLengthType::OTHER:
        return RelativeConvertToPx(sqrt(viewPort.Width() * viewPort.Height()), scale);
    default:
        return 0.0;
    }
}

double Dimension::FromRelative(bool isObjectBoundingBoxUnit, double relative, double scale) {
    if (Unit() == DimensionUnit::PERCENT) {
        return Value() * relative;
    }
    double baseLen = isObjectBoundingBoxUnit ? relative : scale;
    return Value() * baseLen;
}
} // namespace svg
} // namespace rnoh