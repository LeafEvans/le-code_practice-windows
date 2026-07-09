/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "RNSVGBaseComponentInstance.h"
#include "SvgSymbol.h"

namespace rnoh {
namespace svg {

class RNSVGSymbolComponentInstance : public RNSVGBaseComponentInstance<facebook::react::RNSVGSymbolShadowNode> {
public:
    explicit RNSVGSymbolComponentInstance(Context context);

protected:
    void UpdateElementProps() override;

private:
    std::shared_ptr<SvgSymbol> m_svgSymbol = std::make_shared<SvgSymbol>();
};

} // namespace svg
} // namespace rnoh