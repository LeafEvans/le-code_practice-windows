/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "SvgNode.h"
#include "SvgGraphic.h"

namespace rnoh {
namespace svg {

class SvgDefs : public SvgNode {
public:
    SvgDefs() : SvgNode() { InitDefsFlag(); }
    ~SvgDefs() override = default;

    void InitDefsFlag() {
        hrefFill_ = false;
        hrefRender_ = false;
        inheritStyle_ = false;
        drawTraversed_ = false;
    }

    drawing::Path AsPath() override {
        drawing::Path path;
        // Early return if there are no children
        if (children_.empty()) {
            return path;
        }
        for (const auto& child : children_) {
            if (!child) {
                DLOG(WARNING) << "[SvgDefs:AsPath] Encountered a null child node";
                continue;
            }
            auto childPath = child->AsPath();
            path.Union(childPath);
        }
        return path;
    }
};

} // namespace svg
} // namespace rnoh
