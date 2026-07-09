/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "SvgGraphic.h"
#include "utils/SvgAttributesParser.h"

namespace rnoh {
namespace svg {

class SvgCircle : public SvgGraphic {
public:
    SvgCircle() = default;
    ~SvgCircle() override = default;

    void SetX(const std::string &x) { circleAttribute_.cx = SvgAttributesParser::ParseDimension(x, true); }
    void SetY(const std::string &y) { circleAttribute_.cy = SvgAttributesParser::ParseDimension(y, true); }
    void SetR(const std::string &r) { circleAttribute_.r = SvgAttributesParser::ParseDimension(r, true); }
    drawing::Path AsPath() override;
private:
    SvgCircleAttribute circleAttribute_;
};

} // namespace svg
} // namespace rnoh
