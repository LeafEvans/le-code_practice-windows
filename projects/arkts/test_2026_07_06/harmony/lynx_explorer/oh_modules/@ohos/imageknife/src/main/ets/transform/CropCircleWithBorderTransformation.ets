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

export interface rgbColor {
  r_color: number,
  g_color: number,
  b_color: number,
}

/**
 * 图片变换：圆环裁剪效果
 */
@Sendable
export class CropCircleWithBorderTransformation extends PixelMapTransformation {
  private mBorderSize: number = 5;
  private mCenterX: number = 0;
  private mCenterY: number = 0;
  private mRadius: number = 0;
  private mRColor: number = 0;
  private mGColor: number = 0;
  private mBColor: number = 0;

  constructor(borderSize: number, value: rgbColor) {
    super();
    this.mRColor = value.g_color;
    this.mGColor = value.g_color;
    this.mBColor = value.b_color;
    this.mBorderSize = borderSize;
  }

  getConstructorParams() {
    return JSON.stringify([this.mBorderSize, {
      r_color: this.mRColor,
      g_color: this.mGColor,
      b_color: this.mBColor
    }]);
  }

  getName(): string {
    return this.constructor.name + ';mBorderSize:' + this.mBorderSize + ';mCenterX:' + this.mCenterX + ';mCenterY:'
      + this.mCenterY + ';mRadius:' + this.mRadius + ';mRColor:' + this.mRColor + ';mGColor:' + this.mGColor + ';mBColor:' + this.mBColor;
  }

  async transform(context: Context, toTransform: PixelMap, width: number, height: number): Promise<PixelMap> {
    return await this.transformPixelMap(toTransform);
  }

  private async transformPixelMap(pixelMap: PixelMap): Promise<PixelMap> {
    let imageInfo: image.ImageInfo = await pixelMap.getImageInfo();
    let size: Size = {
      width: imageInfo.size.width,
      height: imageInfo.size.height
    };
    if (!size) {
      console.error('CropCircleWithBorderTransformation The image size does not exist.');
      return pixelMap;
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


    let bufferData = new ArrayBuffer(pixelMap.getPixelBytesNumber());
    await pixelMap.readPixelsToBuffer(bufferData);

    let dataArray = new Uint8Array(bufferData);

    for (let h = 0; h <= height; h++) {
      for (let w = 0; w <= width; w++) {
        // 不在大圆之内的设置透明
        // 在大圆与小圆之间的  设置rgb值
        // 小圆之内的不变
        let isSmallCircle: boolean = this.isContainsSmallCircle(w, h);
        let isBigCircle: boolean = this.isContainsCircle(w, h);
        if (isSmallCircle) {
          continue;
        }

        let index = (h * width + w) * 4;
        if (!isBigCircle) {
          // 设置透明
          dataArray[index] = 0;
          dataArray[index+1] = 0;
          dataArray[index+2] = 0;
          dataArray[index+3] = 0;
        } else {
          // 设置broke
          dataArray[index] = this.mRColor;
          dataArray[index+1] = this.mGColor;
          dataArray[index+2] = this.mBColor;
        }
      }
    }
    await pixelMap.writeBufferToPixels(bufferData);
    return pixelMap;
  }

  isContainsCircle(x: number, y: number): boolean {
    let a: number = Math.pow((this.mCenterX - x), 2);
    let b: number = Math.pow((this.mCenterY - y), 2);
    let c: number = Math.sqrt((a + b));
    return c <= this.mRadius;
  }

  isContainsSmallCircle(x: number, y: number): boolean {
    let a: number = Math.pow((this.mCenterX - x), 2);
    let b: number = Math.pow((this.mCenterY - y), 2);
    let c: number = Math.sqrt((a + b));
    return c <= (this.mRadius - this.mBorderSize);
  }
}