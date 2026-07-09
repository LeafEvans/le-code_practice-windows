/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "SvgPath.h"
#include "utils/PathParserUtils.h"
#include <native_drawing/drawing_matrix.h>
#include "utils/PathParserUtils.h"

namespace rnoh {
namespace svg {

void SvgPath::setD(const std::string &d) {
    d_ = d;
    PathParserUtils parser;
    parser.mScale = scale_;
    try {
        path_ = std::move(parser.parse(d.c_str()));
    } catch (const std::runtime_error &e) {
        LOG(ERROR) << "[svgPath] Svg path d invalid, error message: " << e.what();
        return;
    }
    elements_ = std::move(parser.elements);
    for (PathElement &elem : elements_) {
        for (Point &point : elem.points) {
            point.x *= scale_;
            point.y *= scale_;
        }
    }
}

drawing::Path SvgPath::AsPath() {
    if (path_.get()) {
        return path_;
    }
    return drawing::Path();
}

} // namespace svg
} // namespace rnoh
