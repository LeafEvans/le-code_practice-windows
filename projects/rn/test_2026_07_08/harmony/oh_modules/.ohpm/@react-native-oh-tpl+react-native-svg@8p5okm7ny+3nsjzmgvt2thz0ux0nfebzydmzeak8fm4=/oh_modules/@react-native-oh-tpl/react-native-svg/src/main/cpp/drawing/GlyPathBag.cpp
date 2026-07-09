/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "GlyPathBag.h"
#include "Path.h"

namespace rnoh::drawing {


int GlyPathBag::getIndex(char ch) {
    auto it = data.find(ch);
    return it == data.end() ? 0 : it->second;
}

drawing::Path GlyPathBag::getOrCreateAndCache(const char &ch, const std::string &current) { return drawing::Path(); }

} // namespace rnoh::drawing