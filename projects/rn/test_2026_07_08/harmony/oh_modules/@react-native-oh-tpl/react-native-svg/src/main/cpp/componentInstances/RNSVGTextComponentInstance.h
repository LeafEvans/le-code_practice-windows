/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "RNSVGBaseComponentInstance.h"
#include "SvgText.h"

namespace rnoh {
namespace svg {

class RNSVGTextComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGTextShadowNode> {
public:
    explicit RNSVGTextComponentInstance(Context context);

protected:
    void UpdateElementProps() override;

private:
    std::shared_ptr<SvgText> m_svgText = std::make_shared<SvgText>();
};

} // namespace svg
} // namespace rnoh