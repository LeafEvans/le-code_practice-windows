/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "RNSVGSvgViewModule.h"

using namespace facebook;
using namespace react;

namespace rnoh {
namespace svg {

using Object = std::optional<jsi::Object>;

void RNSVGSvgViewModule::toDataURL(jsi::Runtime &rt, Int32_t tag, Object object, Callback &&callback) {
    // 获取图片的bitmap并将其转化为base64
    std::string base64;
    auto weakSvgNode = SvgViewManager::getInstance().getSvgViewByTag(*tag);
    if (weakSvgNode.lock()) {
        auto svgRootNode = weakSvgNode.lock();
        OH_Drawing_Bitmap *bitmap = OH_Drawing_BitmapCreate();
        OH_Drawing_BitmapFormat format = {COLOR_FORMAT_BGRA_8888, ALPHA_FORMAT_OPAQUE};
        auto size = svgRootNode->GetSize();
        OH_Drawing_BitmapBuild(bitmap, size.Width(), size.Height(), &format);
        OH_Drawing_Canvas *canvas = OH_Drawing_CanvasCreate();
        OH_Drawing_CanvasBind(canvas, bitmap);
        // 设置SvgNode节点相关信息
        if (svgRootNode->GetContext()) {
            svgRootNode->GetContext()->ClearIdMap();
        }
        svgRootNode->ContextTraversal();
        svgRootNode->InitStyle({});
        svgRootNode->Draw(canvas);
        base64 = StringUtils::bitmapToBase64(bitmap);
        // 销毁bitmap和canvas
        OH_Drawing_CanvasDestroy(canvas);
        // 销毁bitmap对象
        OH_Drawing_BitmapDestroy(bitmap);
    }
    jsInvoker_->invokeAsync([base64, endCallback = std::move(*callback)] { endCallback(base64); });
    return;
}

static jsi::Value __hostFunction_RNSVGSvgViewModule_toDataURL(jsi::Runtime &rt, react::TurboModule &turboModule,
                                                              const jsi::Value *args, size_t count) {
    auto tag = args[0].isNull() || args[0].isUndefined() ? std::nullopt : std::make_optional(args[0].asNumber());
    auto options = args[1].isNull() || args[1].isUndefined() ? std::nullopt : std::make_optional(args[1].asObject(rt));
    auto self = static_cast<RNSVGSvgViewModule *>(&turboModule);
    if (args[2].isObject()) {
        auto callback = std::make_shared<jsi::Function>(std::move(args[2].getObject(rt).getFunction(rt)));
        auto endCallback = [&rt, callback = std::move(callback)](std::string base64) {
            auto base64Value = jsi::String::createFromUtf8(rt, base64);
            callback->call(rt, {std::move(base64Value)});
        };
        static_cast<RNSVGSvgViewModule *>(&turboModule)->toDataURL(rt, tag, std::move(options), std::move(endCallback));
        return jsi::Value::undefined();
    }
    static_cast<RNSVGSvgViewModule *>(&turboModule)
        ->toDataURL(rt, tag, std::move(options), [self, &rt](std::string base64) {});
    return jsi::Value::undefined();
}

RNSVGSvgViewModule::RNSVGSvgViewModule(const ArkTSTurboModule::Context ctx, const std::string name)
    : ArkTSTurboModule(ctx, name) {
    { methodMap_["toDataURL"] = MethodMetadata{1, __hostFunction_RNSVGSvgViewModule_toDataURL}; };
}

} // namespace svg
} // namespace rnoh
