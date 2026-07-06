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
export class Constants {
  public static PROGRESS_EMITTER: string = 'progressEmitter'
  public static CALLBACK_EMITTER: string = 'callBackEmitter'
}

/**
 * 图片加载的code
 */
export enum LoadPixelMapCode {
  // createImageSource error code
  IMAGE_SOURCE_ERROR_CODE = 100001,
  // createPixelMap error code
  IMAGE_DECODE_ERROR_CODE = 100002,
  //ImageKnifeAnimatorComponent组件仅支持动态图 code
  IMAGE_FORMAT_ERROR_CODE = 100003,
  //load failed code
  IMAGE_LOAD_FAILED_CODE = 100004,
  //自定义下载失败 code
  IMAGE_CUSTOM_LOAD_FAILED_CODE = 100005,
  // http请求失败 code
  IMAGE_HTTPS_LOAD_FAILED_CODE = 100006,
  //设置onlyRetrieveFromCache 导致的加载失败的code
  IMAGE_RETRIEVE_CACHE_CODE = 100007,
  //加载共享图片失败code
  IMAGE_LOAD_SHARE_FILE_FAILED_CODE = 100008,
  //加载本地文件图片失败code
  IMAGE_LOAD_LOCAL_FILE_FAILED_CODE = 100009,
  // 取消请求加载code
  IMAGE_LOAD_CANCEL_FAILED_CODE = 1000010,
  // 解析图片格式阶段
  IMAGE_PARSE_FORMAT_FAILED_CODE = 1000011
}

/**
 * 图片加载的各个阶段
 */
export enum LoadPhase {
  // 图片加载阶段
  PHASE_LOAD = 'load',
  // 网络请求下载阶段
  PHASE_NET = 'net',
  //获取图片格式阶段
  PHASE_GET_FORMAT = 'parse_format',
  //自定义下载阶段 customGetImage
  PHASE_CUSTOM_LOAD = 'customGetImage',
  // createPixelMap 阶段
  PHASE_CREATE_SOURCE = 'createImageSource',
  //createPixelMap 阶段
  PHASE_CREATE_PIXEL_MAP = 'createPixelMap',
  //请求队列排队阶段
  PHASE_THREAD_QUEUE = 'thread_queue',
  //图片解析阶段
  PHASE_PARSE_IAMGE = 'parseImage',
  //加载解析datashare:// 或者file:// 阶段
  PHASE_SHARE_FILE = 'datashare_or_file',
  //加载解析本地文件阶段
  PHASE_LOCAL_FILE = 'load_local_file',
  //图片加载解析完成，即将显示的阶段
  PHASE_WILL_SHOW = 'will_show',
}