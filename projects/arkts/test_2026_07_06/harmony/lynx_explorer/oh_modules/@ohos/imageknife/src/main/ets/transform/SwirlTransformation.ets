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
import { GPUImageSwirlFilter } from '@ohos/gpu_transform';
import { PixelMapTransformation } from './PixelMapTransformation';
import { image } from '@kit.ImageKit';

/**
 * 图片变换：扭曲效果
 */
@Sendable
export class SwirlTransformation extends PixelMapTransformation {
  // degree:值越大范围越大
  private mDegree: number = 0;
  // 取值范围 0.0 ~ 1.0
  private mAngle: number = 0.9;
  // 在图中的位置 取值范围 0.0 ~ 1.0
  private mXCenter: number = 0.5;
  // 在图中的位置 取值范围 0.0 ~ 1.0
  private mYCenter: number = 0.5;

  constructor(degree: number, angle?: number, centerPoint?: Array<number>) {
    super();
    this.mDegree = degree;
    if (angle) {
      this.mAngle = angle;
    }
    if (centerPoint && centerPoint.length === 2) {
      this.mXCenter = centerPoint[0];
      this.mYCenter = centerPoint[1];
    }
  }

  getName(): string {
    return this.constructor.name + ';degree:' + this.mDegree + ';angle:' + this.mAngle + ';XCenter:' + this.mXCenter
      + ';YCenter:' + this.mYCenter;
  }

  async transform(context: Context, toTransform: PixelMap, width: number, height: number): Promise<PixelMap> {
    let imageInfo: image.ImageInfo = await toTransform.getImageInfo();
    if (!imageInfo.size) {
      console.error('SwirlTransformation The image size does not exist.');
      return toTransform;
    }
    return await this.swirlGPU(toTransform, imageInfo.size.width, imageInfo.size.height);
  }

  private async swirlGPU(bitmap: image.PixelMap, targetWidth: number, targetHeight: number): Promise<PixelMap> {
    let bufferData = new ArrayBuffer(bitmap.getPixelBytesNumber());
    await bitmap.readPixelsToBuffer(bufferData);
    let filter = new GPUImageSwirlFilter();
    filter.setImageData(bufferData, targetWidth, targetHeight);
    filter.setRadius(this.mDegree);
    filter.setAngle(this.mAngle);
    filter.setCenter(this.mXCenter, this.mYCenter);
    let buf = await filter.getPixelMapBuf(0, 0, targetWidth, targetHeight);
    await bitmap.writeBufferToPixels(buf);
    return bitmap;
  }
}