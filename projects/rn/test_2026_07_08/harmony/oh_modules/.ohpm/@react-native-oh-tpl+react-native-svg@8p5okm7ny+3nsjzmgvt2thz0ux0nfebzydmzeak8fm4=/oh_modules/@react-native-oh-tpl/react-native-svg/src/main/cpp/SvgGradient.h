/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "SvgGraphic.h"
#include <native_drawing/drawing_point.h>
#include "utils/SvgAttributesParser.h"

namespace rnoh {
namespace svg {

class SvgGradient : public SvgNode {
public:
    using Float = facebook::react::Float;
    explicit SvgGradient(GradientType gradientType);
    ~SvgGradient() override = default;
    
    void OnDraw(OH_Drawing_Canvas *canvas) override;

    void SetAttrX1(const std::string& x1);
    void SetAttrY1(const std::string& y1);
    void SetAttrX2(const std::string& x2);
    void SetAttrY2(const std::string& y2);

    void SetAttrFx(const std::string& fx);
    void SetAttrFy(const std::string& fy);
    void SetAttrCx(const std::string& cx);
    void SetAttrCy(const std::string& cy);
    void SetAttrRx(const std::string& rx);
    void SetAttrRy(const std::string& ry);

    void SetAttrGradient(std::vector<Float> gradient);
    void SetAttrGradientUnits(int gradientUnits);
    void SetAttrGradientTransforms(std::vector<Float> gradientTransforms);

    const Gradient& GetGradient() const;

private:
    SvgGradientAttribute gradientAttr_;
    double scale_ = 3.25;
    DimensionUnit defaultUnit_ = DimensionUnit::VP;
};

} // namespace svg
} // namespace rnoh
