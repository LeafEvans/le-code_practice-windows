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
import taskpool from '@ohos.taskpool';
import common from '@ohos.app.ability.common'
import { CacheStrategy, ImageKnifeData,EventImage } from './ImageKnifeData';
import { PixelMapTransformation } from '../transform/PixelMapTransformation';
import { drawing } from '@kit.ArkGraphics2D';
import { ImageKnifeRequest } from './ImageKnifeRequest';
import { DownsampleStrategy } from '../downsampling/DownsampleStartegy';

export interface HeaderOptions {
  key: string;
  value: Object;
}

@Observed
export class AnimatorOption {
  @Track
  state?: AnimationStatus = AnimationStatus.Running
  @Track
  iterations?: number = -1
  @Track
  reverse?: boolean = false
  @Track
  onStart?:()=>void
  @Track
  onFinish?:()=>void
  @Track
  onPause?:()=>void
  @Track
  onCancel?:()=>void
  @Track
  onRepeat?:()=>void
}

@ObservedV2
export class AnimatorOptionV2 {
  @Trace
  state?: AnimationStatus = AnimationStatus.Running
  @Trace
  iterations?: number = -1
  @Trace
  reverse?: boolean = false
  @Trace
  onStart?: () => void
  @Trace
  onFinish?: () => void
  @Trace
  onPause?: () => void
  @Trace
  onCancel?: () => void
  @Trace
  onRepeat?: () => void

  setState(state: AnimationStatus) {
    this.state = state
    return this
  }

  setIterations(iterations: number) {
    this.iterations = iterations
    return this
  }

  setReverse(reverse: boolean) {
    this.reverse = reverse
    return this
  }

  start(onStart: () => void) {
    this.onStart = onStart
    return this
  }

  finish(onFinish: () => void) {
    this.onFinish = onFinish
    return this
  }

  pause(onPause: () => void) {
    this.onPause = onPause
    return this
  }

  cancel(onCancel: () => void) {
    this.onCancel = onCancel
    return this
  }

  repeat(onRepeat: () => void) {
    this.onRepeat = onRepeat
    return this
  }
}

export interface HttpRequestOption {
  caPath?: string  // 自定义证书路径
  connectTimeout?: number // 连接超时
  readTimeout?: number // 读取超时
}
@Observed
export class ImageKnifeOption {
  // 主图资源
  loadSrc: string | PixelMap | Resource = 'ImageKnife';
  // 占位图
  placeholderSrc?: string | PixelMap | Resource;
  // 失败占位图
  errorholderSrc?: string | PixelMap | Resource;
  headerOption?: Array<HeaderOptions>;
  // 自定义缓存关键字
  signature?: string;
  // 主图填充效果
  objectFit?: ImageFit
  // 占位图填充效果
  placeholderObjectFit?: ImageFit
  // 错误图填充效果
  errorholderObjectFit?: ImageFit
  customGetImage?: (context: Context, src: string | PixelMap | Resource,headers?: Record<string,Object>) => Promise<ArrayBuffer | undefined>
  border?: BorderOptions
  // 缓存策略
  writeCacheStrategy?: CacheStrategy
  // 仅使用缓存加载数据
  onlyRetrieveFromCache?: boolean = false;
  priority?: taskpool.Priority = taskpool.Priority.LOW
  context?: common.UIAbilityContext;
  progressListener?: (progress: number) => void;
  transformation?: PixelMapTransformation
  onLoadListener?: OnLoadCallBack | undefined;
  onComplete?:(event:EventImage | undefined) => void
  drawingColorFilter?: ColorFilter | drawing.ColorFilter
  downsampleOf?: DownsampleStrategy // 降采样
  // 自定义证书路径
  httpOption?: HttpRequestOption
  constructor() {

  }
}

@ObservedV2
export class ImageKnifeOptionV2 {
  // 主图资源
  @Trace
  loadSrc: string | PixelMap | Resource = 'ImageKnife';
  // 占位图
  placeholderSrc?: string | PixelMap | Resource;
  // 失败占位图
  errorholderSrc?: string | PixelMap | Resource;
  headerOption?: Array<HeaderOptions>;
  // 自定义缓存关键字
  @Trace
  signature?: string;
  // 主图填充效果
  objectFit?: ImageFit
  // 占位图填充效果
  placeholderObjectFit?: ImageFit
  // 错误图填充效果
  errorholderObjectFit?: ImageFit
  customGetImage?: (context: Context, src: string | PixelMap | Resource,headers?: Record<string,Object>) => Promise<ArrayBuffer | undefined>
  border?: BorderOptions
  // 缓存策略
  writeCacheStrategy?: CacheStrategy
  // 仅使用缓存加载数据
  onlyRetrieveFromCache?: boolean = false;
  priority?: taskpool.Priority = taskpool.Priority.LOW
  context?: common.UIAbilityContext;
  progressListener?: (progress: number) => void;
  @Trace
  transformation?: PixelMapTransformation
  onLoadListener?: OnLoadCallBack | undefined;
  onComplete?:(event:EventImage | undefined) => void
  drawingColorFilter?: ColorFilter | drawing.ColorFilter
  @Trace
  downsampleOf?: DownsampleStrategy // 降采样
  // 自定义证书路径
  httpOption?: HttpRequestOption
  constructor(option: ImageKnifeOption) {
    this.loadSrc = option.loadSrc
    this.placeholderSrc = option.placeholderSrc
    this.errorholderSrc = option.errorholderSrc
    this.headerOption = option.headerOption
    this.signature = option.signature
    this.objectFit = option.objectFit
    this.placeholderObjectFit = option.placeholderObjectFit
    this.errorholderObjectFit = option.errorholderObjectFit
    this.customGetImage = option.customGetImage
    this.border = option.border
    this.writeCacheStrategy = option.writeCacheStrategy
    this.onlyRetrieveFromCache = option.onlyRetrieveFromCache
    this.priority = option.priority
    this.context = option.context
    this.progressListener = option.progressListener
    this.transformation = option.transformation
    this.onLoadListener = option.onLoadListener
    this.onComplete = option.onComplete
    this.drawingColorFilter = option.drawingColorFilter
    this.downsampleOf = option.downsampleOf
    this.httpOption = option.httpOption
  }
}

/**
 * 请求回调
 */
export interface OnLoadCallBack {
  // 请求开始
  onLoadStart?: (request?: ImageKnifeRequest) => void;

  // 请求成功
  onLoadSuccess?: (data: string | PixelMap | undefined, imageKnifeData: ImageKnifeData, request?: ImageKnifeRequest) => void;

  // 请求结束
  onLoadFailed?: (err: string, request?: ImageKnifeRequest) => void;
  // 请求取消
  onLoadCancel?: (reason: string, request?: ImageKnifeRequest) => void;
}