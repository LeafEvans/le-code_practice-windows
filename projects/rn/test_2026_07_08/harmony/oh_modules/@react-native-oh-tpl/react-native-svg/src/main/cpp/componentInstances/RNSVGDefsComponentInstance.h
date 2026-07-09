/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "RNSVGBaseComponentInstance.h"
#include "SvgDefs.h"

namespace rnoh {
namespace svg {

class RNSVGDefsComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGDefsShadowNode> {

public:
    explicit RNSVGDefsComponentInstance(Context context);

protected:
    void UpdateElementProps() override;

private:
    std::shared_ptr<SvgDefs> m_svgDefs = std::make_shared<SvgDefs>();
};

} // namespace svg
} // namespace rnoh