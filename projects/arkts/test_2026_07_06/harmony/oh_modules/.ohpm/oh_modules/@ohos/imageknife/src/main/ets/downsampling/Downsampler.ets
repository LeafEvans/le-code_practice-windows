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
import {
  AtMost,
  CenterInside,
  AtLeast,
  DownsampleStrategy,
  FitCenter,
  DefaultDownSampling,
} from './DownsampleStartegy';
export class Downsampler {
  calculateScaling(
    typeValue: string,
    sourceWidth: number, //原始宽高
    sourceHeight: number, //原始宽高
    requestWidth: number, //请求宽高
    requestHeight: number, //请求宽高
    downsampType: DownsampleStrategy,
  ): Size {

    if (sourceHeight <= 0 || sourceWidth <= 0) {
      throw new Error(`Invalid width and height, sourceHeight:${sourceHeight}+ sourceWidth:${sourceWidth}`)
    }
    let downsampler = this.getDownsampler(downsampType);
    let scaleFactor: number =
      downsampler.getScaleFactor(sourceWidth, sourceHeight, requestWidth, requestHeight, downsampType);//缩放比
    //基于上一步得出的采样大小，根据不同的图片类型，计算采样后的图片尺寸
    if (typeValue === 'png') {
      return {
        width: Math.floor(sourceWidth / scaleFactor),
        height: Math.floor(sourceHeight / scaleFactor)
      }
    } else if (typeValue === 'webp') {
      return {
        width: Math.round(sourceWidth / scaleFactor),
        height: Math.round(sourceHeight / scaleFactor)
      }
    } else {
      return {
        width: sourceWidth / scaleFactor,
        height: sourceHeight / scaleFactor

      }
    }
  }
  getDownsampler(downsampType: DownsampleStrategy) {
    switch (downsampType) {
      case DownsampleStrategy.FIT_CENTER_MEMORY:
      case DownsampleStrategy.FIT_CENTER_QUALITY:
        return new FitCenter();
      case DownsampleStrategy.AT_MOST:
        return new AtMost();
      case DownsampleStrategy.CENTER_INSIDE_MEMORY:
      case DownsampleStrategy.CENTER_INSIDE_QUALITY:
        return new CenterInside();
      case DownsampleStrategy.AT_LEAST:
        return new AtLeast();
      case DownsampleStrategy.DEFAULT:
        return new DefaultDownSampling();
      default:
        throw new Error('Unsupported downsampling strategy');
    }
  }
}