/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include <memory>
#include "SvgNode.h"

namespace rnoh {
namespace svg {

class SvgHost {
 public:
     SvgHost() = default;
     virtual ~SvgHost() = default;
     void SetSvgNode(const std::shared_ptr<SvgNode> &svgNode) { 
        std::lock_guard<std::mutex> lock(mtx);
        m_svgNode = svgNode;
    };
     const std::shared_ptr<SvgNode> &GetSvgNode() const { 
        std::lock_guard<std::mutex> lock(mtx);
        return m_svgNode;
    };

     void OnChildInsertCommon(const std::shared_ptr<SvgHost> &childSvgHost);

     void OnChildRemoveCommon(const std::shared_ptr<SvgHost> &childSvgHost);

 private:
  std::shared_ptr<SvgNode> m_svgNode{nullptr};
  mutable std::mutex mtx;
};

} // namespace svg
} // namespace rnoh