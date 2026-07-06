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
 * 图片变换：圆形裁剪效果
 */
@Sendable
export class CropCircleTransformation extends PixelMapTransformation {
  private mCenterX: number = 0;
  private mCenterY: number = 0;
  private mRadius: number = 0;

  constructor() {
    super();
  }

  getName(): string {
    return this.constructor.name + ';mCenterX:' + this.mCenterX + ';mCenterY:' + this.mCenterY + ';mRadius:' + this.mRadius;
  }

  async transform(context: Context, toTransform: PixelMap, width: number, height: number): Promise<PixelMap> {
    return await this.transformCircle(toTransform);
  }

  private async transformCircle(data: PixelMap): Promise<PixelMap> {
    let imageInfo: image.ImageInfo = await data.getImageInfo();
    let size: Size = {
      width: imageInfo.size.width,
      height: imageInfo.size.height
    };
    if (!size) {
      console.error('CropCircleTransformation The image size does not exist.');
      return data;
    }
    let height: number = size.height;
    let width: number = size.width;
    this.mRadius = 0;
    if (width > height) {
      this.mRadius = height / 2;
    } else {
      this.mRadius = width / 2;
    }
    this.mCenterX = width / 2;
    this.mCenterY = height / 2;

    let bufferData: ArrayBuffer = new ArrayBuffer(data.getPixelBytesNumber());
    await data.readPixelsToBuffer(bufferData);

    let dataArray = new Uint8Array(bufferData);

    for (let h = 0; h <= height; h++) {
      for (let w = 0; w <= width; w++) {
        if (this.isContainsCircle(w, h)) {
          continue;
        }
        // 针对的点
        let index = (h * width + w) * 4;
        dataArray[index] = 0;
        dataArray[index+1] = 0;
        dataArray[index+2] = 0;
        dataArray[index+3] = 0;
      }
    }
    await data.writeBufferToPixels(bufferData);
    return data;
  }

  isContainsCircle(x: number, y: number): boolean {
    let a = Math.pow((this.mCenterX - x), 2);
    let b = Math.pow((this.mCenterY - y), 2);
    let c = Math.sqrt((a + b));
    return c <= this.mRadius;
  }
}