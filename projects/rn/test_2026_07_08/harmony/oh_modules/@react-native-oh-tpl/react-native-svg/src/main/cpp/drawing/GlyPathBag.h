/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include <unordered_map>
#include <vector>
#include "drawing/Path.h"
#include "drawing/Pen.h"

namespace rnoh::drawing {

class GlyPathBag {
private:
    int getIndex(char ch);
    std::vector<drawing::Path> paths;
    std::unordered_map<char, int> data;
    drawing::Pen paint;

public:
    GlyPathBag(drawing::Pen const &paint) {
        // Make indexed-by-one, to allow zero to represent non-cached
        paths.push_back(drawing::Path());
    }
    drawing::Path getOrCreateAndCache(const char &ch, const std::string &current);
};

} // namespace rnoh::drawing
