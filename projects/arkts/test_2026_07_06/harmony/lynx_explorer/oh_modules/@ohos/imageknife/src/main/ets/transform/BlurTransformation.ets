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
import effectKit from '@ohos.effectKit';

/**
 * 图片变换：模糊效果
 */
@Sendable
export class BlurTransformation extends PixelMapTransformation {
  private radius: number // 模糊半径，单位是像素。模糊效果与所设置的值成正比，值越大效果越明显。

  constructor(radius: number) {
    super()
    this.radius = radius
  }

  getName(): string {
    return this.constructor.name + ';radius:' + this.radius;
  }

  async transform(context: Context, toTransform: PixelMap, width: number, height: number): Promise<PixelMap> {
    let headFilter = effectKit.createEffect(toTransform);
    if (headFilter != null) {
      return await headFilter.blur(this.radius).getEffectPixelMap()
    }
    return toTransform
  }
}

