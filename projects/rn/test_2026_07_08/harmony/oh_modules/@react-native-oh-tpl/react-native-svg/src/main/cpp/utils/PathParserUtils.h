/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 *
 * This file incorporates from the react-native-svg project, licensed under
 * the MIT License. Specifically:
 * - [software-mansion/react-native-svg] (https://github.com/software-mansion/react-native-svg)
 */

#pragma once

#include "SvgMarkerPositionUtils.h"
#include "drawing/Path.h"
#include <vector>
#include <string>

namespace rnoh {
namespace svg {
class PathParserUtils {

public:
    float mScale;
    std::vector<PathElement> elements;

    drawing::Path parse(std::string d);

private:
    int i;
    int l;
    std::string s;
    drawing::Path mPath;
    float mPenX, mPenY, mPenDownX, mPenDownY, mPivotX, mPivotY;
    bool mPenDown;

    void parse_list_separator();

    void skip_digits();

    void close();

    void setPenDown();

    void moveTo(float x, float y);

    void move(float x, float y);

    void lineTo(float x, float y);

    void line(float x, float y);

    void cubicTo(float c1x, float c1y, float c2x, float c2y, float ex, float ey);

    void curveTo(float c1x, float c1y, float c2x, float c2y, float ex, float ey);

    void curve(float c1x, float c1y, float c2x, float c2y, float ex, float ey);

    void smoothCurveTo(float c1x, float c1y, float ex, float ey);

    void smoothCurve(float c1x, float c1y, float ex, float ey);

    void quadraticBezierCurveTo(float c1x, float c1y, float c2x, float c2y);

    void quadraticBezierCurve(float c1x, float c1y, float c2x, float c2y);

    void smoothQuadraticBezierCurveTo(float c1x, float c1y);

    void smoothQuadraticBezierCurve(float c1x, float c1y);

    void arcToBezier(float cx, float cy, float rx, float ry, float sa, float ea, bool clockwise, float rad);

    void arcTo(float rx, float ry, float rotation, bool outer, bool clockwise, float x, float y);

    void arc(float rx, float ry, float rotation, bool outer, bool clockwise, float x, float y);

    double roundVal(double val);

    void skip_spaces();

    bool is_cmd(char c);

    bool is_number_start(char c);

    bool is_absolute(char c);

    bool parse_flag();

    float parse_number();

    float parse_list_number();
};
} // namespace svg
} // namespace rnoh
