/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "RNSVGBaseComponentInstance.h"
#include "SvgTextPath.h"

namespace rnoh {
namespace svg {

class RNSVGTextPathComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGTextPathShadowNode> {
public:
    explicit RNSVGTextPathComponentInstance(Context context);

protected:
    void UpdateElementProps() override;

private:
    std::shared_ptr<SvgTextPath> m_svgTP = std::make_shared<SvgTextPath>();
};

} // namespace svg
} // namespace rnoh