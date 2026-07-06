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
 * 图片变换：高亮效果
 */
@Sendable
export class BrightnessTransformation extends PixelMapTransformation {
  private bright: number // 高亮程度，取值范围在0-1之间，取值为0时图像保持不变。

  constructor(bright: number) {
    super()
    this.bright = bright
  }

  getName(): string {
    return this.constructor.name + ';bright:' + this.bright;
  }

  async transform(context: Context, toTransform: PixelMap, width: number, height: number): Promise<PixelMap> {
    let headFilter = effectKit.createEffect(toTransform);
    if (headFilter != null) {
      return await headFilter.brightness(this.bright).getEffectPixelMap()
    }
    return toTransform
  }
}

