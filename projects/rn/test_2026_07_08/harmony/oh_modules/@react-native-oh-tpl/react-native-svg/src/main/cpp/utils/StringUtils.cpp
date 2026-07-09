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

#include "StringUtils.h"
#include "multimedia/image_framework/image/image_packer_native.h"
#include "multimedia/image_framework/image/image_source_native.h"
#include "multimedia/image_framework/image/pixelmap_native.h"

namespace rnoh {
namespace svg {
namespace StringUtils {
const char *base64_chars[2] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                               "abcdefghijklmnopqrstuvwxyz"
                               "0123456789"
                               "+/",

                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                               "abcdefghijklmnopqrstuvwxyz"
                               "0123456789"
                               "-_"};

std::string base64_encode(unsigned char const *bytes_to_encode, size_t in_len, bool url) {
    // 这里的in_len 是bytes_to_encode数组的长度，也就是要处理多少数量的单位数据(unsigned char)
    size_t len_encoded = (in_len + 2) / 3 * 4; // 这里经过了转化，len_encoded长度变为了像素总数

    unsigned char trailing_char = url ? '.' : '=';

    const char *base64_chars_ = base64_chars[url];

    std::string ret;
    ret.reserve(len_encoded);

    unsigned int pos = 0;

    while (pos < in_len) {
        ret.push_back(base64_chars_[(bytes_to_encode[pos + 0] & 0xfc) >> 2]);

        if (pos + 1 < in_len) {
            ret.push_back(
                base64_chars_[((bytes_to_encode[pos + 0] & 0x03) << 4) + ((bytes_to_encode[pos + 1] & 0xf0) >> 4)]);

            if (pos + 2 < in_len) {
                ret.push_back(
                    base64_chars_[((bytes_to_encode[pos + 1] & 0x0f) << 2) + ((bytes_to_encode[pos + 2] & 0xc0) >> 6)]);
                ret.push_back(base64_chars_[bytes_to_encode[pos + 2] & 0x3f]);
            } else {
                ret.push_back(base64_chars_[(bytes_to_encode[pos + 1] & 0x0f) << 2]);
                ret.push_back(trailing_char);
            }
        } else {

            ret.push_back(base64_chars_[(bytes_to_encode[pos + 0] & 0x03) << 4]);
            ret.push_back(trailing_char);
            ret.push_back(trailing_char);
        }
        pos += 3;
    }
    return ret;
}
std::string bitmapToBase64(OH_Drawing_Bitmap *bitmap) {
    auto width = OH_Drawing_BitmapGetWidth(bitmap);
    auto height = OH_Drawing_BitmapGetHeight(bitmap);
    auto bitmapAddr = OH_Drawing_BitmapGetPixels(bitmap);
    // 设置pixelmap编码格式
    OH_Pixelmap_InitializationOptions *createOption = nullptr;
    OH_PixelmapInitializationOptions_Create(&createOption);
    OH_PixelmapInitializationOptions_SetWidth(createOption, width);
    OH_PixelmapInitializationOptions_SetHeight(createOption, height);
    OH_PixelmapInitializationOptions_SetPixelFormat(createOption, PIXEL_FORMAT_BGRA_8888);
    OH_PixelmapInitializationOptions_SetAlphaType(createOption, PIXELMAP_ALPHA_TYPE_UNKNOWN);

    // 创建pixelmap实例
    OH_PixelmapNative *pixelMap = nullptr;
    Image_ErrorCode errCode = OH_PixelmapNative_CreatePixelmap(reinterpret_cast<uint8_t *>(bitmapAddr),
                                                               width * height * 4, createOption, &pixelMap);

    // 读取图像数据
    size_t destinationSize = width * height * 4;
    uint8_t *destination = (uint8_t *)malloc(destinationSize);
    errCode = OH_PixelmapNative_ReadPixels(pixelMap, destination, &destinationSize);

    // 设置pixelmap图像信息
    OH_Pixelmap_ImageInfo *imageInfo = nullptr;
    OH_PixelmapImageInfo_Create(&imageInfo);
    errCode = OH_PixelmapNative_GetImageInfo(pixelMap, imageInfo);

    OH_ImagePackerNative *packer = nullptr;
    errCode = OH_ImagePackerNative_Create(&packer);

    // 图片压缩options设置
    OH_PackingOptions *option = nullptr;
    OH_PackingOptions_Create(&option);
    char type[] = "image/png";
    Image_MimeType imageMimeType = {type, strlen(type)};
    OH_PackingOptions_SetMimeType(option, &imageMimeType);
    size_t bufferSize = width * height * 4;
    uint8_t *outData = (uint8_t *)malloc(bufferSize);
    errCode = OH_ImagePackerNative_PackToDataFromPixelmap(packer, option, pixelMap, outData, &bufferSize);

    std::string base64str = StringUtils::base64_encode(reinterpret_cast<unsigned char *>(outData), bufferSize);

    // 释放内存
    free(destination);
    free(outData);
    OH_PixelmapInitializationOptions_Release(createOption);
    OH_PixelmapNative_Release(pixelMap);
    OH_PixelmapImageInfo_Release(imageInfo);
    OH_ImagePackerNative_Release(packer);
    OH_PackingOptions_Release(option);

    return base64str;
}

} // namespace StringUtils
} // namespace svg
} // namespace rnoh