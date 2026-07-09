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

class SvgEllipse : public SvgGraphic {
public:
    using Float = facebook::react::Float;
    SvgEllipse() = default;
    ~SvgEllipse() override = default;
    
    drawing::Path AsPath() override;
    void SetCX(const std::string &cx) { ellipseAttribute_.cx = SvgAttributesParser::ParseDimension(cx, true); }
    void SetCY(const std::string &cy) { ellipseAttribute_.cy = SvgAttributesParser::ParseDimension(cy, true); }
    void SetRX(const std::string &rx) { ellipseAttribute_.rx = SvgAttributesParser::ParseDimension(rx, true); }
    void SetRY(const std::string &ry) { ellipseAttribute_.ry = SvgAttributesParser::ParseDimension(ry, true); }

private:
    SvgEllipseAttribute ellipseAttribute_;
};

} // namespace svg
} // namespace rnoh


