/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "RNSVGBaseComponentInstance.h"
#include "SvgMarker.h"

namespace rnoh {
namespace svg {

class RNSVGMarkerComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGMarkerShadowNode> {
public:
    explicit RNSVGMarkerComponentInstance(Context context);

protected:
    void UpdateElementProps() override;

private:
    std::shared_ptr<SvgMarker> m_svgMarker = std::make_shared<SvgMarker>();
};

} // namespace svg
} // namespace rnoh