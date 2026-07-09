/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "SvgCircle.h"

namespace rnoh {
namespace svg {

drawing::Path SvgCircle::AsPath() {
    drawing::Path path;
    double x = relativeOnWidth(circleAttribute_.cx);
    double y = relativeOnHeight(circleAttribute_.cy);
    double r = relativeOnOther(circleAttribute_.r);
    
    path.AddCircle(x, y, r, PATH_DIRECTION_CW);
    
    elements_ = {PathElement(ElementType::kCGPathElementMoveToPoint, {Point(x, y - r)}),
                       PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(x, y - r), Point(x + r, y)}),
                       PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(x + r, y), Point(x, y + r)}),
                       PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(x, y + r), Point(x - r, y)}),
                       PathElement(ElementType::kCGPathElementAddLineToPoint, {Point(x - r, y), Point(x, y - r)})};
    return path;
}

} // namespace svg
} // namespace rnoh
