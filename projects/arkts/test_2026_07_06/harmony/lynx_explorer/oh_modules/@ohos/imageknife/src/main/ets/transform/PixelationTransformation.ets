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
import { GPUImagePixelationFilter } from '@ohos/gpu_transform';
import { PixelMapTransformation } from './PixelMapTransformation';
import { image } from '@kit.ImageKit';

/**
 * Applies a Pixelation effect to the image.
 * The pixel with a default of 10.0.
 */
@Sendable
export class PixelationTransformation extends PixelMapTransformation {
  private mPixel: number = 10.0;

  constructor(pixel?: number) {
    super();
    if (pixel) {
      this.mPixel = pixel;
    }
  }

  getName(): string {
    return this.constructor.name + ';pixel:' + this.mPixel;
  }


  async transform(context: Context, toTransform: PixelMap, width: number, height: number): Promise<PixelMap> {
    let imageInfo: image.ImageInfo = await toTransform.getImageInfo();
    if (!imageInfo.size) {
      console.error('PixelationTransformation The image size does not exist.');
      return toTransform;
    }
    return await this.pixelGPU(toTransform, imageInfo.size.width, imageInfo.size.height);
  }

  private async pixelGPU(bitmap: PixelMap, targetWidth: number, targetHeight: number): Promise<PixelMap> {
    let bufferData = new ArrayBuffer(bitmap.getPixelBytesNumber());
    await bitmap.readPixelsToBuffer(bufferData);
    let filter = new GPUImagePixelationFilter();
    filter.setImageData(bufferData, targetWidth, targetHeight);
    filter.setPixel(this.mPixel);
    let buf = await filter.getPixelMapBuf(0, 0, targetWidth, targetHeight);
    await bitmap.writeBufferToPixels(buf);
    return bitmap;
  }
}