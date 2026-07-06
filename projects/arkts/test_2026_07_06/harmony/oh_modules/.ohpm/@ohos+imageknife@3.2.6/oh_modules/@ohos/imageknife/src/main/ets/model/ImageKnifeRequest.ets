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
import { ImageKnifeOption, ImageKnifeOptionV2 } from './ImageKnifeOption';
import common from '@ohos.app.ability.common';
import { ImageKnifeData, ImageKnifeRequestSource } from './ImageKnifeData';
import { taskpool } from '@kit.ArkTS';


export class ImageKnifeRequest {
  requestState: ImageKnifeRequestState = ImageKnifeRequestState.PROGRESS
  componentWidth: number = 0
  componentHeight: number = 0
  drawPlayHolderSuccess: boolean = false
  drawMainSuccess: boolean = false
  imageKnifeOption: ImageKnifeOption | ImageKnifeOptionV2
  context: common.UIAbilityContext
  ImageKnifeRequestCallback?: ImageKnifeRequestCallback
  componentVersion: number = 0
  headers: Map<string,Object> = new Map<string,Object>()
  imageKnifeData?: ImageKnifeData
  componentId?: number
  animator?: boolean
  taskRequest?: taskpool.Task
  constructor(option: ImageKnifeOption | ImageKnifeOptionV2,
              uIAbilityContext: common.UIAbilityContext,
              width: number,
              height: number,
              version: number,
              ImageKnifeRequestCallback: ImageKnifeRequestCallback,componentId?: number) {
    this.imageKnifeOption = option
    this.context = uIAbilityContext
    this.componentWidth = width
    this.componentHeight = height
    this.componentVersion = version
    this.ImageKnifeRequestCallback = ImageKnifeRequestCallback
    this.componentId = componentId
  }
  // RequestOption调用header对于的方法
  addHeader(key: string, value: Object) {
    this.headers.set(key, value);
  }

  // 全局调用header对应的方法，包含RequestOption的形式
  addHeaderMap(map: Map<string, Object>) {
    map.forEach((value, key) => {
      if (!this.headers.has(key)) {
        this.addHeader(key, value);
      }
    })
  }


  destroy() {
    this.ImageKnifeRequestCallback = undefined
  }
}

export enum ImageKnifeRequestState {
  PROGRESS,
  COMPLETE,
  ERROR,
  DESTROY
}


export interface ImageKnifeRequestCallback {
  showPixelMap: (version: number, pixelMap: PixelMap | string | Resource, requestSource: ImageKnifeRequestSource ,size?: Size,imageAnimator?: Array<ImageFrameInfo>) => void;
  mainLoadError?: (err: string) => void
}
