/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include <string>

namespace rnoh {
namespace svg {

constexpr int LIGHTER_THRESHOLD_550 = 550;
constexpr int LIGHTER_THRESHOLD_750 = 750;
constexpr int BOLDER_THRESHOLD_350 = 350;
constexpr int BOLDER_THRESHOLD_550 = 550;
constexpr int BOLDER_THRESHOLD_900 = 900;
constexpr int DEFAULT_BOLDER_WEIGHT = 400;
constexpr int DEFAULT_LIGHTER_WEIGHT = 100;
constexpr int DEFAULT_MEDIUM_WEIGHT = 400;
constexpr int DEFAULT_BOLDER_WEIGHT_700 = 700;
constexpr int DEFAULT_BOLDER_WEIGHT_900 = 900;

enum class FontStyle { normal, italic, oblique };

enum class FontWeight {
    w100,
    w200,
    w300,
    normal,
    w500,
    w600,
    bold,
    w800,
    w900,
    bolder,
    lighter,
    unknown,
};

// match with <native_drawing/drawing_text_typography.h>
enum class TextAnchor { start = 4, middle = 2, end = 5 };

// match with <native_drawing/drawing_text_typography.h>
enum class TextDecoration { None = 0x0, Underline = 0x1, Overline = 0x2, LineThrough = 0x4 };

enum class FontVariantLigatures { normal, none };

FontStyle fontStyleFromStr(const std::string &str);
FontWeight fontWeightFromStr(const std::string &str);
TextAnchor textAnchorFromStr(const std::string &str);
TextDecoration textDecorationFromStr(const std::string &str);
FontVariantLigatures fontVariantFromStr(const std::string &str);

// intermediate data to store in Svg nodes
struct FontProps {
    std::string fontStyle;
    std::string fontVariant;
    std::string fontWeight;
    std::string fontStretch;
    std::string fontSize;
    std::string fontFamily;
    std::string textAnchor;
    std::string textDecoration;
    std::string letterSpacing;
    std::string wordSpacing;
    std::string kerning;
    std::string fontFeatureSettings;
    std::string fontVariantLigatures;
    std::string fontVariationSettings;

    inline bool Empty() const {
        return fontStyle.empty() && fontVariant.empty() && fontWeight.empty() && fontStretch.empty() &&
               fontSize.empty() && fontFamily.empty() && textAnchor.empty() && textDecoration.empty() &&
               letterSpacing.empty() && wordSpacing.empty() && kerning.empty() && fontFeatureSettings.empty() &&
               fontVariantLigatures.empty() && fontVariationSettings.empty();
    }
};

class FontData {
public:
    FontData() = default;
    FontData(const FontProps &props, const FontData &parent, double scale);

    static const double DEFAULT_FONT_SIZE;
    static const double DEFAULT_KERNING;
    static const double DEFAULT_WORD_SPACING;
    static const double DEFAULT_LETTER_SPACING;

    /* ------- Props -------- */
    double fontSize = DEFAULT_FONT_SIZE;
    std::string fontFamily;
    FontStyle fontStyle = FontStyle::normal;
    FontWeight fontWeight = FontWeight::normal;
    int absoluteFontWeight = 400;
    std::string fontFeatureSettings;
    std::string fontVariationSettings;
    FontVariantLigatures fontVariantLigatures = FontVariantLigatures::normal;
    TextAnchor textAnchor = TextAnchor::start;
    TextDecoration textDecoration = TextDecoration::None;

    double kerning = DEFAULT_KERNING;
    double wordSpacing = DEFAULT_WORD_SPACING;
    double letterSpacing = DEFAULT_LETTER_SPACING;

    bool manualKerning = false;
    /* -------------------- */

    double toAbsolute(const std::string &value, double scale, double fontSize, double relative);

    void setInheritedWeight(const FontData &parent);

    void handleNumericWeight(const FontData &parent, double number);

private:
    static const int normal = 400;

    static const FontWeight WEIGHTS[];

    static FontWeight nearestFontWeight(int abFontWeight) {
        return WEIGHTS[static_cast<int>(abFontWeight / 100.0f)];
    }

    static const int absoluteFontWeights[];

    static int from(FontWeight fontW, const FontData &parent) {
        if (fontW == FontWeight::bolder) {
            return WeightToBolder(parent.absoluteFontWeight);
        } else if (fontW == FontWeight::lighter) {
            return lighter(parent.absoluteFontWeight);
        } else {
            return absoluteFontWeights[static_cast<int>(fontW)];
        }
    }

    static int WeightToBolder(int inherited) {
        if (inherited < BOLDER_THRESHOLD_350) {
            return DEFAULT_BOLDER_WEIGHT;
        } else if (inherited < BOLDER_THRESHOLD_550) {
            return DEFAULT_BOLDER_WEIGHT_700;
        } else if (inherited < BOLDER_THRESHOLD_900) {
            return DEFAULT_BOLDER_WEIGHT_900;
        } else {
            return inherited;
        }
    }

    static int lighter(int inherited) {
        if (inherited < DEFAULT_LIGHTER_WEIGHT) {
            return inherited;
        } else if (inherited < LIGHTER_THRESHOLD_550) {
            return DEFAULT_LIGHTER_WEIGHT;
        } else if (inherited < LIGHTER_THRESHOLD_750) {
            return DEFAULT_MEDIUM_WEIGHT;
        } else {
            return DEFAULT_BOLDER_WEIGHT_700;
        }
    }
};

} // namespace svg
} // namespace rnoh