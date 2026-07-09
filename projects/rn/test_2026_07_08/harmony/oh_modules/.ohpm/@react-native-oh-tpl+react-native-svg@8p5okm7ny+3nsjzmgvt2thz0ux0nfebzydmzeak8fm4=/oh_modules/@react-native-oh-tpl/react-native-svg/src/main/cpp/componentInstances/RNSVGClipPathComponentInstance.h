/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "RNSVGBaseComponentInstance.h"
#include "SvgClipPath.h"

namespace rnoh {
namespace svg {

class RNSVGClipPathComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGClipPathShadowNode> {
public:
    explicit RNSVGClipPathComponentInstance(Context context);

protected:
    void UpdateElementProps() override;

private:
    std::shared_ptr<SvgClipPath> m_svgClipPath = std::make_shared<SvgClipPath>();
};

} // namespace svg
} // namespace rnoh