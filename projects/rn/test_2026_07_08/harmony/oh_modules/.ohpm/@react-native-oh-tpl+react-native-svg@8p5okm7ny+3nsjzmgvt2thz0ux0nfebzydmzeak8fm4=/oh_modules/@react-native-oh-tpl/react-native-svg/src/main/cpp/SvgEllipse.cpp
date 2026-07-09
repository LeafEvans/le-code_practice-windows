/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "SvgEllipse.h"
#include "drawing/Rect.h"

namespace rnoh {
namespace svg {

drawing::Path SvgEllipse::AsPath() {
    drawing::Path path;
    double cx = relativeOnWidth(ellipseAttribute_.cx);
    double cy = relativeOnHeight(ellipseAttribute_.cy);
    double rx = relativeOnWidth(ellipseAttribute_.rx);
    double ry = relativeOnHeight(ellipseAttribute_.ry);

    drawing::Rect rect(cx - rx, cy - ry, cx + rx, cy + ry);
    path.AddOval(rect, PATH_DIRECTION_CW);

    elements_ = {PathElement(ElementType::kCGPathElementMoveToPoint, {Point(cx, cy - ry)}),
                 PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(cx, cy - ry), Point(cx + rx, cy)}),
                 PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(cx + rx, cy), Point(cx, cy + ry)}),
                 PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(cx, cy + ry), Point(cx - rx, cy)}),
                 PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(cx - rx, cy), Point(cx, cy - ry)})};
    return path;
};

} // namespace svg
} // namespace rnoh