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
import { SparkMD5 } from '../3rd_party/sparkmd5/spark-md5';
import { ImageKnifeOption } from '../model/ImageKnifeOption';
import { IEngineKey } from './IEngineKey';
import { PixelMapTransformation } from '../transform/PixelMapTransformation';
import { ImageKnifeRequestSource } from '../model/ImageKnifeData';
import { DownsampleStrategy } from '../downsampling/DownsampleStartegy';

@Sendable
export class DefaultEngineKey implements IEngineKey {
  // 生成内存缓存key
  generateMemoryKey(loadSrc: string | PixelMap | Resource, requestSource: ImageKnifeRequestSource,
    imageKnifeOption: ImageKnifeOption,isAnimator?: boolean, width?: number, height?: number): string {
    let key = (isAnimator == true ? 'Animator=' : 'loadSrc==') + (typeof loadSrc == 'string' ? loadSrc : JSON.stringify(loadSrc)) + ';'
    if (requestSource === ImageKnifeRequestSource.SRC) {
      if (imageKnifeOption.signature !== undefined && imageKnifeOption.signature !== '') {
        key += 'signature=' + imageKnifeOption.signature + ';'
      }
      if (imageKnifeOption.transformation) {
        key += 'transformation=' + this.getTransformation(imageKnifeOption.transformation) + ';'
      }
      if ((imageKnifeOption.downsampleOf !== DownsampleStrategy.NONE && imageKnifeOption.downsampleOf !== undefined)) {
        key += 'downsampleOf' + imageKnifeOption.downsampleOf + 'width=' + width + 'height=' + height
      }
    }
    return key
  }

  // 生成文件缓存key
  generateFileKey(loadSrc: string | PixelMap | Resource, signature?: string,isAnimator?: boolean): string {
    let src = (isAnimator == true ? 'Animator=' : 'loadSrc==') + (typeof loadSrc == 'string' ? loadSrc : JSON.stringify(loadSrc)) + ';'
    if (signature !== undefined && signature !== '') {
      src += 'signature=' + signature + ';'
    }
    return SparkMD5.hashBinary(src)
  }

  private getTransformation(transformation: PixelMapTransformation): string {
    return transformation.getName()
  }
}



