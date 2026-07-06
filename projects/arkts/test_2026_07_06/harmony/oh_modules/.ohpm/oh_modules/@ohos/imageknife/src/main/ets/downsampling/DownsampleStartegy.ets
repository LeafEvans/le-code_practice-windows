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
import { BaseDownsampling } from './BaseDownsampling';
import { getScale, highestOneBit, round, SampleSizeRounding } from './DownsampleUtils';

export class FitCenter implements BaseDownsampling {
  getName() {
    return 'FitCenter'
  }

  getScaleFactor(sourceWidth: number, sourceHeight: number, requestedWidth: number, requestedHeight: number,
    downsampType: DownsampleStrategy
  ): number {
    //重新计算宽高比;
    let outSize: Size = {
      width: round(getScale(sourceWidth, sourceHeight, requestedWidth, requestedHeight, downsampType) * sourceWidth),
      height:round(getScale(sourceWidth, sourceHeight, requestedWidth, requestedHeight, downsampType) * sourceHeight)
    }
    let scaleFactor = downsampType === DownsampleStrategy.FIT_CENTER_QUALITY?
    Math.max(1, highestOneBit(Math.max(sourceWidth / outSize.width, sourceHeight / outSize.height))) :
    Math.max(1, highestOneBit(Math.min(sourceWidth / outSize.width, sourceHeight / outSize.height)))//将整型的缩放因子转换为2的次幂采样大小

    if (downsampType === DownsampleStrategy.FIT_CENTER_MEMORY
      && (scaleFactor < (1 / getScale(sourceWidth, sourceHeight, requestedWidth, requestedHeight, downsampType)))) {
      scaleFactor = scaleFactor << 1;
    }
    return scaleFactor
  }
}


/*宽高进行等比缩放宽高里面最小的比例先放进去
然后再更据原图的缩放比去适配另一边*/

export class AtLeast implements BaseDownsampling {
  getName() {
    return 'AtLeast'
  }

  getScaleFactor(sourceWidth: number, sourceHeight: number, requestedWidth: number, requestedHeight: number): number {
    const widthPercentage = requestedWidth / sourceWidth;
    const heightPercentage = requestedHeight / sourceHeight;
    //返回宽度和高度比例中最大的值
    let outSize: Size = {
      width: round(Math.max(widthPercentage, heightPercentage) * sourceWidth),
      height:round(Math.max(widthPercentage, heightPercentage) * sourceHeight)
    }
    let scaleFactor = Math.max(1, highestOneBit(Math.max(sourceWidth / outSize.width, sourceHeight / outSize.height)))

    return scaleFactor
  }
}

/*请求尺寸大于实际尺寸不进行放大,按照原图展示*/

export class AtMost implements BaseDownsampling {
  getName() {
    return 'AtMost'
  }


  getScaleFactor(sourceWidth: number, sourceHeight: number, requestedWidth: number, requestedHeight: number): number {
    const maxIntegerFactor = Math.ceil(Math.max(sourceHeight / requestedHeight, sourceWidth / requestedWidth));
    let lesserOrEqualSampleSize = Math.max(1, highestOneBit(maxIntegerFactor));
    let greaterOrEqualSampleSize = lesserOrEqualSampleSize
    if (lesserOrEqualSampleSize < maxIntegerFactor) {
      greaterOrEqualSampleSize = lesserOrEqualSampleSize <<= 1;
    }
    greaterOrEqualSampleSize = lesserOrEqualSampleSize << (lesserOrEqualSampleSize < maxIntegerFactor ? 1 : 0)

    let outSize: Size = {
      width: round((1 / greaterOrEqualSampleSize) * sourceWidth),
      height:round((1 / greaterOrEqualSampleSize) * sourceHeight)
    }
    let scaleFactor = Math.max(1, highestOneBit(Math.min(sourceWidth / outSize.width, sourceHeight / outSize.height)))
    if ((scaleFactor < greaterOrEqualSampleSize)) {
      scaleFactor = scaleFactor << 1;
    }
    return scaleFactor
  }
}

/*宽高进行等比缩放宽高里面最大的比例先放进去
然后再更据原图的缩放比去适配另一边*/
export class CenterInside implements BaseDownsampling {
  getName() {
    return 'CenterInside'
  }
  getScaleFactor(sourceWidth: number, sourceHeight: number, requestedWidth: number, requestedHeight: number,
    downsampType: DownsampleStrategy
  ): number {
    let outSize: Size = {
      width: round(Math.min(1, getScale(sourceWidth, sourceHeight, requestedWidth, requestedHeight, downsampType)) * sourceWidth),
      height:round(Math.min(1, getScale(sourceWidth, sourceHeight, requestedWidth, requestedHeight, downsampType)) * sourceHeight)
    }
    //将整型的缩放因子转换为2的次幂采样大小
    let scaleFactor = this.getSampleSizeType(sourceWidth, sourceHeight, requestedWidth, requestedHeight,
      downsampType) == SampleSizeRounding.QUALITY ?
    Math.max(1, highestOneBit(Math.max(sourceWidth / outSize.width, sourceHeight / outSize.height))) :
    Math.max(1, highestOneBit(Math.min(sourceWidth / outSize.width, sourceHeight / outSize.height)))
    if (this.getSampleSizeType(sourceWidth, sourceHeight, requestedWidth, requestedHeight, downsampType)
      == SampleSizeRounding.MEMORY  && (scaleFactor < (1 / Math.min(1, getScale(sourceWidth, sourceHeight, requestedWidth, requestedHeight, downsampType))))) {
      scaleFactor = scaleFactor << 1;
    }
    return scaleFactor

  }

  getSampleSizeType(sourceWidth: number, sourceHeight: number, requestedWidth: number, requestedHeight: number,
    downsampType: DownsampleStrategy
  ): SampleSizeRounding {
    //如果缩放因子为 1，表示没有缩放，优先选择质量
    if (Math.min(1, getScale(sourceWidth, sourceHeight, requestedWidth, requestedHeight, downsampType)) === 1) {
      return SampleSizeRounding.QUALITY
    }
    //否则，使用 FIL_CENTER 的 SampleSizeRounding 值
    return downsampType === DownsampleStrategy.CENTER_INSIDE_MEMORY?SampleSizeRounding.MEMORY:SampleSizeRounding.QUALITY
  }
}
// 默认值，图片分辨率超过上限7680 * 4320，宽高等比降为7680 * 4320
export class DefaultDownSampling implements BaseDownsampling {
  getName(): string {
    return 'DefaultDownSampling'
  }
  getScaleFactor(sourceWidth: number, sourceHeight: number, requestWidth: number, requestHeight: number, downsampType?: DownsampleStrategy | undefined): number {
    let resolution_max_8k = 7680 * 4320
    let resolution_source = sourceWidth * sourceHeight

    if ( resolution_source <= resolution_max_8k ) {
      return 1
    } else {
      return resolution_source / resolution_max_8k
    }
  }
}

export enum DownsampleStrategy {
  //请求尺寸大于实际尺寸不进行放大
  AT_MOST,
  //两边自适应内存优先
  FIT_CENTER_MEMORY,
  //两边自适应质量优先
  FIT_CENTER_QUALITY,
  //按照宽高比的最大比进行适配内存优先
  CENTER_INSIDE_MEMORY,
  //按照宽高比的最大比进行适配质量优先
  CENTER_INSIDE_QUALITY,
  //宽高进行等比缩放宽高里面最小的比例先放进去，然后再根据原图的缩放比去适配
  AT_LEAST,
  //不进行降采样
  NONE,
  // 默认值，图片分辨率超过上限7680 * 4320，宽高等比降为7680 * 4320
  DEFAULT
}