/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include "SVGPackage.h"

#include "RNOH/generated/components/RNSVGGroupJSIBinder.h"
#include "RNOH/generated/components/RNSVGSvgViewJSIBinder.h"
#include "RNOH/generated/components/RNSVGPathJSIBinder.h"
#include "RNOH/generated/components/RNSVGRectJSIBinder.h"
#include "RNOH/generated/components/RNSVGImageJSIBinder.h"
#include "RNOH/generated/components/RNSVGCircleJSIBinder.h"
#include "RNOH/generated/components/RNSVGEllipseJSIBinder.h"
#include "RNOH/generated/components/RNSVGLinearGradientJSIBinder.h"
#include "RNOH/generated/components/RNSVGDefsJSIBinder.h"
#include "RNOH/generated/components/RNSVGTextJSIBinder.h"
#include "RNOH/generated/components/RNSVGTSpanJSIBinder.h"
#include "RNOH/generated/components/RNSVGClipPathJSIBinder.h"
#include "RNOH/generated/components/RNSVGMaskJSIBinder.h"
#include "RNOH/generated/components/RNSVGMarkerJSIBinder.h"
#include "RNOH/generated/components/RNSVGUseJSIBinder.h"
#include "RNOH/generated/components/RNSVGForeignObjectJSIBinder.h"
#include "RNOH/generated/components/RNSVGLineJSIBinder.h"
#include "RNOH/generated/components/RNSVGPatternJSIBinder.h"
#include "RNOH/generated/components/RNSVGRadialGradientJSIBinder.h"
#include "RNOH/generated/components/RNSVGSymbolJSIBinder.h"
#include "RNOH/generated/components/RNSVGTextPathJSIBinder.h"
#include "turboModules/RNSVGSvgViewModule.h"
#include "turboModules/RNSVGRenderableModule.h"
#include "turboModules/RNSVGImageModule.h"
#include <react/renderer/components/react_native_svg/ComponentDescriptors.h>
#include "svgImage/RNSVGImageComponentDescriptor.h"

using namespace rnoh;
using namespace facebook;
using namespace svg;

std::vector<react::ComponentDescriptorProvider> SVGPackage::createComponentDescriptorProviders() {
    return {
        facebook::react::concreteComponentDescriptorProvider<facebook::react::RNSVGCircleComponentDescriptor>(),
        facebook::react::concreteComponentDescriptorProvider<facebook::react::RNSVGClipPathComponentDescriptor>(),
        facebook::react::concreteComponentDescriptorProvider<facebook::react::RNSVGDefsComponentDescriptor>(),
        facebook::react::concreteComponentDescriptorProvider<facebook::react::RNSVGEllipseComponentDescriptor>(),
        facebook::react::concreteComponentDescriptorProvider<facebook::react::RNSVGForeignObjectComponentDescriptor>(),
        facebook::react::concreteComponentDescriptorProvider<facebook::react::RNSVGGroupComponentDescriptor>(),
        facebook::react::concreteComponentDescriptorProvider<facebook::react::RNSVGSvgViewComponentDescriptor>(),
        facebook::react::concreteComponentDescriptorProvider<facebook::react::RNSVGImageComponentDescriptor>(),
        facebook::react::concreteComponentDescriptorProvider<facebook::react::RNSVGLineComponentDescriptor>(),
        facebook::react::concreteComponentDescriptorProvider<facebook::react::RNSVGLinearGradientComponentDescriptor>(),
        facebook::react::concreteComponentDescriptorProvider<facebook::react::RNSVGMarkerComponentDescriptor>(),
        facebook::react::concreteComponentDescriptorProvider<facebook::react::RNSVGMaskComponentDescriptor>(),
        facebook::react::concreteComponentDescriptorProvider<facebook::react::RNSVGPathComponentDescriptor>(),
        facebook::react::concreteComponentDescriptorProvider<facebook::react::RNSVGPatternComponentDescriptor>(),
        facebook::react::concreteComponentDescriptorProvider<facebook::react::RNSVGRadialGradientComponentDescriptor>(),
        facebook::react::concreteComponentDescriptorProvider<facebook::react::RNSVGRectComponentDescriptor>(),
        facebook::react::concreteComponentDescriptorProvider<facebook::react::RNSVGSymbolComponentDescriptor>(),
        facebook::react::concreteComponentDescriptorProvider<facebook::react::RNSVGTSpanComponentDescriptor>(),
        facebook::react::concreteComponentDescriptorProvider<facebook::react::RNSVGTextComponentDescriptor>(),
        facebook::react::concreteComponentDescriptorProvider<facebook::react::RNSVGTextPathComponentDescriptor>(),
        facebook::react::concreteComponentDescriptorProvider<facebook::react::RNSVGUseComponentDescriptor>(),
    };
}

ComponentNapiBinderByString SVGPackage::createComponentNapiBinderByName() { return {}; }

ComponentJSIBinderByString SVGPackage::createComponentJSIBinderByName() {
    return {
        {"RNSVGCircle", std::make_shared<RNSVGCircleJSIBinder>()},
        {"RNSVGClipPath", std::make_shared<RNSVGClipPathJSIBinder>()},
        {"RNSVGDefs", std::make_shared<RNSVGDefsJSIBinder>()},
        {"RNSVGEllipse", std::make_shared<RNSVGEllipseJSIBinder>()},
        {"RNSVGForeignObject", std::make_shared<RNSVGForeignObjectJSIBinder>()},
        {"RNSVGGroup", std::make_shared<RNSVGGroupJSIBinder>()},
        {"RNSVGSvgView", std::make_shared<RNSVGSvgViewJSIBinder>()},
        {"RNSVGImage", std::make_shared<RNSVGImageJSIBinder>()},
        {"RNSVGLine", std::make_shared<RNSVGLineJSIBinder>()},
        {"RNSVGLinearGradient", std::make_shared<RNSVGLinearGradientJSIBinder>()},
        {"RNSVGRadialGradient", std::make_shared<RNSVGRadialGradientJSIBinder>()},
        {"RNSVGMarker", std::make_shared<RNSVGMarkerJSIBinder>()},
        {"RNSVGMask", std::make_shared<RNSVGMaskJSIBinder>()},
        {"RNSVGPath", std::make_shared<RNSVGPathJSIBinder>()},
        {"RNSVGPattern", std::make_shared<RNSVGPatternJSIBinder>()},
        {"RNSVGRadialGradient", std::make_shared<RNSVGRadialGradientJSIBinder>()},
        {"RNSVGRect", std::make_shared<RNSVGRectJSIBinder>()},
        {"RNSVGSymbol", std::make_shared<RNSVGSymbolJSIBinder>()},
        {"RNSVGTSpan", std::make_shared<RNSVGTSpanJSIBinder>()},
        {"RNSVGText", std::make_shared<RNSVGTextJSIBinder>()},
        {"RNSVGTextPath", std::make_shared<RNSVGTextPathJSIBinder>()},
        {"RNSVGUse", std::make_shared<RNSVGUseJSIBinder>()},
    };
};

class SvgTurboModuleFactoryDelegate : public TurboModuleFactoryDelegate {
public:
    SharedTurboModule createTurboModule(Context ctx, const std::string &name) const override {
        if (name == "RNSVGSvgViewModule") {
            return std::make_shared<RNSVGSvgViewModule>(ctx, name);
        }
        if (name == "RNSVGRenderableModule") {
            return std::make_shared<RNSVGRenderableModule>(ctx, name);
        }
        if (name == "RNSVGImageModule") {
            return std::make_shared<RNSVGImageModule>(ctx, name);
        }
        return nullptr;
    };
};

std::unique_ptr<TurboModuleFactoryDelegate> SVGPackage::createTurboModuleFactoryDelegate() {
    return std::make_unique<SvgTurboModuleFactoryDelegate>();
}