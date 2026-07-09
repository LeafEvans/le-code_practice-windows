/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "SvgGraphic.h"

namespace rnoh {
namespace svg {

class SvgPath : public SvgGraphic {
private:
    std::string d_;
    drawing::Path path_{};

public:
    SvgPath() = default;
    ~SvgPath() override = default;

    void setD(const std::string &d);

    drawing::Path AsPath() override;
};

} // namespace svg
} // namespace rnoh