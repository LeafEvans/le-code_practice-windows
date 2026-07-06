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
import { DownsampleStrategy } from './DownsampleStartegy';

export enum SampleSizeRounding {
  /**
   * Prefer to round the sample size up so that the image is downsampled to smaller than the
   * requested size to use less memory.
   */
  //（内存优先）
  MEMORY,
  /**
   * Prefer to round the sample size down so that the image is downsampled to larger than the
   * requested size to maintain quality at the expense of extra memory usage.
   */
  //（质量优先）
  QUALITY
}
//找出给定整数 i 中最高位的1（即最左边的1）所代表的值
export function highestOneBit(i: number): number {
  i |= (i >> 1);
  i |= (i >> 2);
  i |= (i >> 4);
  i |= (i >> 8);
  i |= (i >> 16);
  return i - (i >>> 1);
}


export function getScale(sourceWidth: number, sourceHeight: number, requestedWidth: number, requestedHeight: number,
  downsampType: DownsampleStrategy
): number {
  if (downsampType === DownsampleStrategy.FIT_CENTER_MEMORY) {
    const widthPercentage = requestedWidth / sourceWidth
    const heightPercentage = requestedHeight / sourceHeight
    return Math.min(widthPercentage, heightPercentage)
  } else {
    const maxIntegerFactor = Math.max(sourceHeight / requestedHeight, sourceWidth / requestedWidth);
    return maxIntegerFactor === 0 ? 1 : 1 / highestOneBit(maxIntegerFactor);

  }
}
//四舍五入
export function  round(value: number): number {
  return Math.floor(value + 0.5);
}