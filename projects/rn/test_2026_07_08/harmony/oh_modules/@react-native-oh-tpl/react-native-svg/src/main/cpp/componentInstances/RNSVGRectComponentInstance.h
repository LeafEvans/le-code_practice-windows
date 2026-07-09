/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "RNSVGBaseComponentInstance.h"
#include "SvgRect.h"

namespace rnoh {
namespace svg {

class RNSVGRectComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGRectShadowNode> {
public:
    explicit RNSVGRectComponentInstance(Context context);

protected:
    void UpdateElementProps() override;

private:
    std::shared_ptr<SvgRect> m_svgRect = std::make_shared<SvgRect>();
};

} // namespace svg
} // namespace rnoh