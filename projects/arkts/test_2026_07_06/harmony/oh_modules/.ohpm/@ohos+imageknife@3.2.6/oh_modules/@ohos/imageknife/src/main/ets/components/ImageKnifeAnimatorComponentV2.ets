/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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
import { AnimatorOptionV2, ImageKnifeOptionV2 } from '../model/ImageKnifeOption';
import { ImageKnifeRequest, ImageKnifeRequestState } from '../model/ImageKnifeRequest';
import common from '@ohos.app.ability.common';
import { ImageKnife } from '../ImageKnife';
import { LogUtil } from '../utils/LogUtil';
import { ImageKnifeRequestSource } from '../model/ImageKnifeData';
import { emitter } from '@kit.BasicServicesKit';

@ComponentV2
export struct ImageKnifeAnimatorComponentV2 {
  @Param @Require imageKnifeOption: ImageKnifeOptionV2;
  @Param animatorOption: AnimatorOptionV2 = new AnimatorOptionV2();
  @Local pixelMap: PixelMap | string | undefined = undefined
  @Local imageAnimator: Array<ImageFrameInfo> | undefined = undefined
  @Local adaptiveWidth: Length = '100%'
  @Local adaptiveHeight: Length | undefined = '100%'
  @Local objectFit: ImageFit = ImageFit.Contain
  private componentId: number = 0
  private request: ImageKnifeRequest | undefined
  private lastWidth: number = 0
  private lastHeight: number = 0
  private isImageFitAutoResize: boolean = false
  private currentWidth: number = 0
  private currentHeight: number = 0
  private componentVersion: number = 0
  private currentContext: common.UIAbilityContext | undefined = undefined
  @Monitor('imageKnifeOption','imageKnifeOption.loadSrc','imageKnifeOption.signature','imageKnifeOption.transformation','imageKnifeOption.downsampleOf')
  watchImageKnifeOption() {
    this.clearLastRequest()
    this.componentVersion++
    this.isImageFitAutoResize = false
    this.objectFit = this.imageKnifeOption.objectFit === undefined ? ImageFit.Contain : this.imageKnifeOption.objectFit
    LogUtil.log('watchImageKnifeOption execute request:width=' + this.currentWidth + ' height= ' + this.currentHeight +
      ' loadSrc = ' + this.imageKnifeOption.loadSrc +
      ' placeholderSrc = ' + this.imageKnifeOption.placeholderSrc +
      ' errorholderSrc = ' + this.imageKnifeOption.errorholderSrc +
      ' componentId = ' + this.componentId)
    ImageKnife.getInstance().execute(this.getRequest(
      this.currentWidth, this.currentHeight, this.componentId))
  }
  aboutToAppear(): void {
    this.objectFit = this.imageKnifeOption.objectFit === undefined ? ImageFit.Contain : this.imageKnifeOption.objectFit
    this.componentId = this.getUniqueId()
  }

  aboutToDisappear(): void {
    this.emitterDestroy()
    this.clearLastRequest()
  }

  aboutToRecycle() {
    this.emitterDestroy()
    this.clearLastRequest()
  }

  emitterDestroy() {
    if (typeof this.request?.imageKnifeOption.loadSrc === 'string' && !this.request?.drawMainSuccess) {
      emitter.emit(this.request.imageKnifeOption.loadSrc + this.componentId)
    }
  }
  /**
   * 对已DESTROY的组件不再发起请求
   */
  private clearLastRequest(){
    if (this.request !== undefined) {
      this.request.requestState = ImageKnifeRequestState.DESTROY
      this.request = undefined
    }
  }
  build() {
    ImageAnimator()
      .images(this.imageAnimator)
      .width(this.adaptiveWidth)
      .height(this.adaptiveHeight)
      .border(this.imageKnifeOption.border)
      .clip(this.imageKnifeOption.border?.radius == undefined ? false : true)
      .state(this.animatorOption.state == undefined ? AnimationStatus.Running : this.animatorOption.state)
      .iterations(this.animatorOption.iterations == undefined ? -1 : this.animatorOption.iterations)
      .reverse(this.animatorOption.reverse == undefined ? false : this.animatorOption.reverse)
      .onSizeChange((oldValue:SizeOptions, newValue:SizeOptions) => {
        this.currentWidth = newValue.width as number
        this.currentHeight = newValue.height as number
        this.lastWidth = oldValue.width as number
        this.lastHeight = oldValue.height as number
        if (this.currentWidth > 0 && this.currentHeight > 0) {
          // 前提：宽高值均有效,值>0. 条件1：当前宽高与上一次宽高不同  条件2:当前是第一次绘制
          if (this.currentHeight !== this.lastHeight || this.currentWidth !== this.lastWidth) {
            LogUtil.log('onSizeChange execute request:width=' + this.currentWidth + ' height= ' + this.currentHeight +
              ' loadSrc = ' + this.imageKnifeOption.loadSrc +
              ' placeholderSrc = ' + this.imageKnifeOption.placeholderSrc +
              ' errorholderSrc = ' + this.imageKnifeOption.errorholderSrc +
              ' componentId = ' + this.componentId)

            if (this.imageKnifeOption.objectFit === ImageFit.Auto && this.isImageFitAutoResize) {
              this.isImageFitAutoResize = false
            } else {
              ImageKnife.getInstance().execute(this.getRequest(
                this.currentWidth, this.currentHeight, this.componentId))
            }
          }
        }
      })
      .onStart(this.animatorOption.onStart)
      .onFinish(this.animatorOption.onFinish)
      .onPause(this.animatorOption.onPause)
      .onCancel(this.animatorOption.onCancel)
      .onRepeat(this.animatorOption.onRepeat)
  }

  getCurrentContext(): common.UIAbilityContext {
    if (this.currentContext === undefined) {
      this.currentContext = getContext(this) as common.UIAbilityContext
    }
    return this.currentContext
  }

  getRequest(width: number, height: number,componentId: number): ImageKnifeRequest {
    this.request = new ImageKnifeRequest(
      this.imageKnifeOption,
      this.imageKnifeOption.context !== undefined ? this.imageKnifeOption.context : this.getCurrentContext(),
      width,
      height,
      this.componentVersion,
      {
        showPixelMap: (version: number, pixelMap: PixelMap | string | Resource, requestSource: ImageKnifeRequestSource,
          size?: Size,
          imageAnimator?: Array<ImageFrameInfo>) => {
          if (version !== this.componentVersion) {
            return //针对reuse场景，不显示历史图片
          }
          if (imageAnimator !== undefined) {
            this.imageAnimator = imageAnimator
          } else {
            this.imageAnimator = [
              {
                src: pixelMap
              }
            ]
          }

          if (this.imageKnifeOption.objectFit === ImageFit.Auto && this.isImageFitAutoResize === false &&
            requestSource === ImageKnifeRequestSource.SRC) {
            this.adaptiveHeight = undefined
            this.isImageFitAutoResize = true
          }

          if (requestSource === ImageKnifeRequestSource.SRC) {
            this.objectFit =
              this.imageKnifeOption.objectFit === undefined ? ImageFit.Contain : this.imageKnifeOption.objectFit
          } else if (requestSource == ImageKnifeRequestSource.PLACE_HOLDER) {
            this.objectFit =
              this.imageKnifeOption.placeholderObjectFit === undefined ?
                (this.imageKnifeOption.objectFit === undefined ? ImageFit.Contain : this.imageKnifeOption.objectFit) :
              this.imageKnifeOption.placeholderObjectFit
          } else {
            this.objectFit =
              this.imageKnifeOption.errorholderObjectFit === undefined ?
                (this.imageKnifeOption.objectFit === undefined ? ImageFit.Contain : this.imageKnifeOption.objectFit) :
              this.imageKnifeOption.errorholderObjectFit
          }
        }
      })
    this.request.animator = true
    return this.request
  }
}