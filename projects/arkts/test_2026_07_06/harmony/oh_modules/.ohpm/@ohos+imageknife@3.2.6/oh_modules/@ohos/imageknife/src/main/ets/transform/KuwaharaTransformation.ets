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
import { GPUImageKuwaharaFilter } from '@ohos/gpu_transform';
import { PixelMapTransformation } from './PixelMapTransformation';
import { image } from '@kit.ImageKit';

/**
 * 图片变换：桑原滤波效果
 */
@Sendable
export class KuwaharaTransformation extends PixelMapTransformation {
  private radius: number;

  constructor(radius: number) {
    super();
    this.radius = radius;
  }

  getName(): string {
    return this.constructor.name + ';radius:' + this.radius;
  }

  async transform(context: Context, toTransform: PixelMap, width: number, height: number): Promise<PixelMap> {
    let imageInfo: image.ImageInfo = await toTransform.getImageInfo();
    if (!imageInfo.size) {
      console.error('KuwaharaTransformation The image size does not exist.');
      return toTransform;
    }
    return await this.kuwaharaGpu(toTransform, imageInfo.size.width, imageInfo.size.height);
  }

  private async kuwaharaGpu(bitmap: PixelMap, targetWidth: number, targetHeight: number): Promise<PixelMap> {
    let bufferData = new ArrayBuffer(bitmap.getPixelBytesNumber());
    await bitmap.readPixelsToBuffer(bufferData);
    let filter = new GPUImageKuwaharaFilter();
    filter.setImageData(bufferData, targetWidth, targetHeight);
    filter.setRadius(this.radius);
    let buf = await filter.getPixelMapBuf(0, 0, targetWidth, targetHeight);
    await bitmap.writeBufferToPixels(buf);
    return bitmap;
  }
}