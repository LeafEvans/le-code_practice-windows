/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 *
 * This file incorporates from the OpenHarmony project, licensed under
 * the Apache License, Version 2.0. Specifically:
 * - [OpenHarmony/arkui_ace_engine] (https://gitee.com/openharmony/arkui_ace_engine)
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy
 * of the License at:
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

// from ArkUI "frameworks/core/components/declaration/common/attribute.h"
#pragma once

namespace rnoh {
namespace svg {

enum class AttributeTag {
    COMMON_ATTR = 0,
    COMMON_DISABLED_ATTR,
    COMMON_FOCUSABLE_ATTR,
    COMMON_TOUCHABLE_ATTR,
    COMMON_DATA_ATTR,
    COMMON_CLICK_EFFECT_ATTR,
    COMMON_RENDER_ATTR,
    COMMON_MULTIMODAL_ATTR,
    SPECIALIZED_ATTR,
    UNKNOWN,
    DEFAULT,
};

struct Attribute {
    bool IsValid() const { return tag != AttributeTag::UNKNOWN; }

    bool IsShared() const { return isShared; }

    bool isShared = true;
    AttributeTag tag = AttributeTag::DEFAULT;
};

} // namespace svg
} // namespace rnoh