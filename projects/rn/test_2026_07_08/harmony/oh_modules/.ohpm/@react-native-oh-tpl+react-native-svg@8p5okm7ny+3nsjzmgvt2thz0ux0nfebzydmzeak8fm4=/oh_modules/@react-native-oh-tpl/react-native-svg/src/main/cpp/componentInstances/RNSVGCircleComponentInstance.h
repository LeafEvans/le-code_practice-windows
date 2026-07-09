/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "RNSVGBaseComponentInstance.h"
#include "SvgCircle.h"

namespace rnoh {
namespace svg {

class RNSVGCircleComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGCircleShadowNode> {
public:
    explicit RNSVGCircleComponentInstance(Context context);

protected:
    void UpdateElementProps() override;

private:
    std::shared_ptr<SvgCircle> m_svgCircle = std::make_shared<SvgCircle>();
};

} // namespace svg
} // namespace rnoh