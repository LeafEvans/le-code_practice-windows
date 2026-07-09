/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "RNSVGBaseComponentInstance.h"
#include "SvgEllipse.h"

namespace rnoh {
namespace svg {

class RNSVGEllipseComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGEllipseShadowNode> {
public:
    explicit RNSVGEllipseComponentInstance(Context context);

protected:
    void UpdateElementProps() override;

private:
    std::shared_ptr<SvgEllipse> m_svgEllipse = std::make_shared<SvgEllipse>();
};

} // namespace svg
} // namespace rnoh