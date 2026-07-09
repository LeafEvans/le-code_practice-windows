/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "RNSVGBaseComponentInstance.h"
#include "SvgPath.h"

namespace rnoh {
namespace svg {

class RNSVGPathComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGPathShadowNode> {
public:
    explicit RNSVGPathComponentInstance(Context context);

protected:
    void UpdateElementProps() override;

private:
    std::shared_ptr<SvgPath> m_svgPath = std::make_shared<SvgPath>();
    std::string m_cacheD;
    Float m_cacheScale;
};

} // namespace svg
} // namespace rnoh