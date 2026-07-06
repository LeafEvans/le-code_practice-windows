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
import { collections } from '@kit.ArkTS';

/**
 * 多个图片变换
 */
@Sendable
export class MultiTransTransformation extends PixelMapTransformation {
  private transformations: collections.Array<PixelMapTransformation>

  constructor(transformations: collections.Array<PixelMapTransformation>) {
    super()
    this.transformations = transformations
  }

  async transform(context: Context, toTransform: PixelMap, width: number, height: number): Promise<PixelMap> {
    let res = toTransform
    for (let i = 0; i < this.transformations.length; i++) {
      res = await this.transformations[i].transform(context, res, width, height)
    }
    return res
  }

  getName(): string {
    let res: string = ''
    this.transformations.forEach((transformation) => {
      res += transformation.getName() + '&'
    })
    return res
  }
}