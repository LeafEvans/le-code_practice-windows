/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "RNSVGBaseComponentInstance.h"
#include "SvgTSpan.h"

namespace rnoh {
namespace svg {

class RNSVGTSpanComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGTSpanShadowNode> {
public:
    explicit RNSVGTSpanComponentInstance(Context context);

protected:
    void UpdateElementProps() override;

private:
    std::shared_ptr<SvgTSpan> m_svgTSpan = std::make_shared<SvgTSpan>();
};

} // namespace svg
} // namespace rnoh