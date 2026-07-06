/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
import { PixelMapTransformation } from './PixelMapTransformation';
import { Size } from '@kit.ArkUI';
import { image } from '@kit.ImageKit';

/**
 * 图片变换：正方形裁剪效果
 */
@Sendable
export class CropSquareTransformation extends PixelMapTransformation {
  constructor() {
    super();
  }

  async transform(context: Context, toTransform: PixelMap, width: number, height: number): Promise<PixelMap> {
    let imageInfo: image.ImageInfo = await toTransform.getImageInfo();
    let size: Size = {
      width: imageInfo.size.width,
      height: imageInfo.size.height
    };
    if (!size) {
      console.error('CropSquareTransformation The image size does not exist.');
      return toTransform;
    }
    let pixelMapWidth: number = size.width;
    let pixelMapHeight: number = size.height;
    let targetSize: number = pixelMapWidth > pixelMapHeight ? pixelMapHeight : pixelMapWidth;
    let region: image.Region = {
      size: { width: targetSize, height: targetSize },
      x: pixelMapWidth / 2 - targetSize / 2,
      y: pixelMapHeight / 2 - targetSize / 2
    };
    await toTransform.crop(region);
    return toTransform;
  }
}