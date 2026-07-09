/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "RNSVGBaseComponentInstance.h"
#include "SvgPattern.h"

namespace rnoh {
namespace svg {

class RNSVGPatternComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGPatternShadowNode> {
public:
    explicit RNSVGPatternComponentInstance(Context context);

protected:
    void UpdateElementProps() override;

private:
    std::shared_ptr<SvgPattern> m_svgPattern = std::make_shared<SvgPattern>();
};

} // namespace svg
} // namespace rnoh