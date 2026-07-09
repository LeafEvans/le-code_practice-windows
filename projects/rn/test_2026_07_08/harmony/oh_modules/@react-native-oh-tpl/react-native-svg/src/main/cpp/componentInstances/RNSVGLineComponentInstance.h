/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "RNSVGBaseComponentInstance.h"
#include "SvgLine.h"

namespace rnoh {
namespace svg {

class RNSVGLineComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGLineShadowNode> {
public:
    explicit RNSVGLineComponentInstance(Context context);

protected:
    void UpdateElementProps() override;

private:
    std::shared_ptr<SvgLine> m_svgLine = std::make_shared<SvgLine>();
};

} // namespace svg
} // namespace rnoh