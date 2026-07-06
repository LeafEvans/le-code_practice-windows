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
import { ImageKnifeRequest, ImageKnifeRequestState } from './model/ImageKnifeRequest';
import { CacheStrategy, ImageKnifeData, ImageKnifeRequestSource } from './model/ImageKnifeData';
import { MemoryLruCache } from './cache/MemoryLruCache';
import { IMemoryCache } from './cache/IMemoryCache'
import { FileCache } from './cache/FileCache';
import { ImageKnifeDispatcher } from './ImageKnifeDispatcher';
import { IEngineKey } from './key/IEngineKey';
import { HeaderOptions, ImageKnifeOption, ImageKnifeOptionV2 } from './model/ImageKnifeOption';
import { FileTypeUtil } from './utils/FileTypeUtil';
import { util } from '@kit.ArkTS';
import { image } from '@kit.ImageKit';
import { common } from '@kit.AbilityKit';
import { LogUtil } from './utils/LogUtil';
import { emitter } from '@kit.BasicServicesKit';


export class ImageKnife {
  private static instance: ImageKnife;
  // 内存缓存
  private memoryCache: IMemoryCache = new MemoryLruCache(256, 128 * 1024 * 1024);
  // 文件缓存
  private fileCache?: FileCache
  private dispatcher: ImageKnifeDispatcher = new ImageKnifeDispatcher()
  // 配置全局是否在子线程加载图片请求
  private _isRequestInSubThread: boolean = true;
  //定义全局网络请求header map
  headerMap: Map<string, Object> = new Map<string, Object>();
  customGetImage: ((context: Context, src: string | PixelMap | Resource,headers?: Record<string,Object>) => Promise<ArrayBuffer | undefined>) | undefined = undefined
  readTimeout?: number
  connectTimeout?: number
  public static getInstance(): ImageKnife {
    if (!ImageKnife.instance) {
      ImageKnife.instance = new ImageKnife();
    }
    return ImageKnife.instance;
  }

  private constructor() {
  }

  getConnectTimeout() {
    return this.connectTimeout
  }

  getReadTimeout() {
    return this.readTimeout
  }
  // 设置连接超时时长
  setConnectTimeout(timeout: number) {
    this.connectTimeout = timeout
  }
  // 设置读取超时时长
  setReadTimeout(timeout: number) {
    this.readTimeout = timeout
  }

  public set isRequestInSubThread(value: boolean) {
    this._isRequestInSubThread = value;
  }

  public get isRequestInSubThread(): boolean {
    return this._isRequestInSubThread;
  }

  /**
   * 初始化文件缓存个数，大小，以及路径
   * @param context 上下文
   * @param size 缓存数量
   * @param memory 内存大小
   * @param path 文件目录
   */
  async initFileCache(context: Context, size: number = 256, memory: number = 256 * 1024 * 1024,path?: string) {
    this.fileCache = new FileCache(context, size, memory)
    if ( path != undefined ) {
      await this.fileCache.initFileCache(path)
    } else {
      await this.fileCache.initFileCache()
    }
  }

  /**
   * 判断文件缓存是否已完成初始化
   * @returns 是否初始化
   */
  public isFileCacheInit(): boolean {
    return this.fileCache === undefined ? false : this.fileCache.isFileCacheInit()
  }
  /**
   * 重新加载
   */
  reload(request: ImageKnifeRequest) {
    if (request.requestState == ImageKnifeRequestState.ERROR) {
      request.requestState = ImageKnifeRequestState.PROGRESS
      ImageKnife.getInstance().execute(request)
    }
  }
  /**
   * 全局添加单个请求头header
   * @param key 请求头属性
   * @param value 请求头值
   */
  addHeader(key: string, value: Object) {
    this.headerMap.set(key, value)
  }

  /**
   * 全局设置请求头header
   * @param options 请求头数组
   */
  serHeaderOptions(options: Array<HeaderOptions>) {
    options.forEach((value) => {
      this.headerMap.set(value.key, value.value)
    })
  }

  /**
   * 删除单个请求头header
   * @param key 请求头属性
   */
  deleteHeader(key: string) {
    this.headerMap.delete(key)
  }

  /**
   * 设置自定义的内存缓存
   * @param newMemoryCache 自定义内存缓存
   */
  initMemoryCache(newMemoryCache: IMemoryCache): void {
    this.memoryCache = newMemoryCache
  }

  /**
   * 清除所有内存缓存
   */
  removeAllMemoryCache(): void {
    this.memoryCache.removeAll()
  }

  /**
   * 清除指定内存缓存
   * @param url 待清除的url路径或ImageKnifeOption
   */
  removeMemoryCache(url: string | ImageKnifeOption | ImageKnifeOptionV2) {
    let imageKnifeOption:ImageKnifeOption | ImageKnifeOptionV2 = new ImageKnifeOption();
    if (typeof url == 'string') {
      imageKnifeOption.loadSrc = url;
    } else {
      imageKnifeOption = url;
    }
    let key = this.getEngineKeyImpl().generateMemoryKey(imageKnifeOption.loadSrc, ImageKnifeRequestSource.SRC, imageKnifeOption);
    this.memoryCache.remove(key);
  }
  /**
   * 预加载
   * @param loadSrc 图片地址url
   * @returns 图片请求request
   */
  preload(loadSrc:string | ImageKnifeOption | ImageKnifeOptionV2):ImageKnifeRequest{
    let imageKnifeOption:ImageKnifeOption | ImageKnifeOptionV2 = new ImageKnifeOption()
    if (typeof loadSrc == 'string') {
      imageKnifeOption.loadSrc = loadSrc
    } else {
      imageKnifeOption = loadSrc;
    }
    let request = new ImageKnifeRequest(
      imageKnifeOption,
      imageKnifeOption.context !== undefined ? imageKnifeOption.context : getContext(this) as common.UIAbilityContext,
      0,
      0,
      0,
      {
        showPixelMap(version: number, pixelMap: PixelMap | string | Resource) {
        }
      }
    )
    this.execute(request)
    return request
  }
  /**
   * 取消图片请求
   * @param request 图片请求request
   */
  cancel(request:ImageKnifeRequest) {
    if (typeof request?.imageKnifeOption.loadSrc === 'string' && !request?.drawMainSuccess) {
      emitter.emit(request.imageKnifeOption.loadSrc + request.componentId)
    }
    request.requestState = ImageKnifeRequestState.DESTROY
  }
  /**
   * 预加载图片到文件缓存
   * @param loadSrc 图片地址url
   * @returns 返回文件缓存路径
   */
  preLoadCache(loadSrc: string | ImageKnifeOption | ImageKnifeOptionV2): Promise<string> {
    return new Promise((resolve, reject) => {
      let imageKnifeOption: ImageKnifeOption | ImageKnifeOptionV2 = new ImageKnifeOption()
      if (typeof loadSrc == 'string') {
        imageKnifeOption.loadSrc = loadSrc
      } else {
        imageKnifeOption = loadSrc;
      }
      LogUtil.log('ImageKnife_DataTime_preLoadCache-imageKnifeOption:'+loadSrc)
      let fileKey = this.getEngineKeyImpl().generateFileKey(imageKnifeOption.loadSrc, imageKnifeOption.signature)
      let cachePath = ImageKnife.getInstance().getFileCache().getFileToPath(fileKey)
      if (cachePath == null || cachePath == '' || cachePath == undefined) {
        let request = new ImageKnifeRequest(
          imageKnifeOption,
          imageKnifeOption.context !== undefined ? imageKnifeOption.context : getContext(this) as common.UIAbilityContext,
          0,
          0,
          0,
          {
            showPixelMap(version: number, pixelMap: PixelMap | string | Resource , requestSource: ImageKnifeRequestSource,size?:Size) {
              if (requestSource === ImageKnifeRequestSource.SRC) {
                resolve(ImageKnife.getInstance().getFileCache().getFileToPath(fileKey))
              }
            },
            mainLoadError:(err: string) =>{
              reject(err)
            }
          }
        )
        this.execute(request)
      } else {
        resolve(cachePath)
      }
    })
  }

  /**
   * 从内存或文件缓存中获取图片数据
   * @param url 图片地址url
   * @param cacheType 缓存策略
   * @returns 图片数据
   * @param signature key自定义信息
   */
  getCacheImage(loadSrc: string,
                cacheType: CacheStrategy = CacheStrategy.Default, signature?: string): Promise<ImageKnifeData | undefined> {
    let option: ImageKnifeOption = {
      loadSrc: loadSrc,
      signature:signature
    }
    let engineKeyImpl: IEngineKey = this.getEngineKeyImpl();

    return new Promise((resolve, reject) => {
      if (cacheType == CacheStrategy.Memory) {
        resolve(this.readMemoryCache(loadSrc, option, engineKeyImpl))
      } else if (cacheType == CacheStrategy.File) {
        this.readFileCache(loadSrc, engineKeyImpl, resolve)
      } else {
        let data = this.readMemoryCache(loadSrc, option, engineKeyImpl)
        data == undefined ? this.readFileCache(loadSrc, engineKeyImpl, resolve) : resolve(data)
      }
    })
  }

  /**
   * 预加载缓存（用于外部已获取pixelmap，需要加入imageknife缓存的场景）
   * @param url  图片地址url
   * @param pixelMap 图片
   * @param cacheType 缓存策略
   * @param signature key自定义信息
   */
  putCacheImage(url: string, pixelMap: PixelMap, cacheType: CacheStrategy = CacheStrategy.Default, signature?: string) {
    let memoryKey = this.getEngineKeyImpl()
      .generateMemoryKey(url, ImageKnifeRequestSource.SRC, { loadSrc: url, signature: signature });
    let fileKey = this.getEngineKeyImpl().generateFileKey(url, signature);
    let imageKnifeData: ImageKnifeData = { source: pixelMap, imageWidth: 0, imageHeight: 0 };
    switch (cacheType) {
      case CacheStrategy.Default:
        this.saveMemoryCache(memoryKey, imageKnifeData);
        this.saveFileCache(fileKey, this.pixelMapToArrayBuffer(pixelMap));
        break;
      case CacheStrategy.File:
        this.saveFileCache(fileKey, this.pixelMapToArrayBuffer(pixelMap));
        break
      case CacheStrategy.Memory:
        this.saveMemoryCache(memoryKey, imageKnifeData);
        break
    }
  }

  /**
   * 清除所有文件缓存
   * @returns
   */
  async removeAllFileCache(): Promise<void> {
    if (this.fileCache !== undefined) {
      await this.fileCache.removeAll()
    }
  }
  /*
   * 清除指定文件缓存
   * */
  removeFileCache(url: string | ImageKnifeOption | ImageKnifeOptionV2) {
    let imageKnifeOption:ImageKnifeOption | ImageKnifeOptionV2 = new ImageKnifeOption();
    if (typeof url == 'string') {
      imageKnifeOption.loadSrc = url;
    } else {
      imageKnifeOption = url;
    }
    let key = this.getEngineKeyImpl().generateFileKey(imageKnifeOption.loadSrc, imageKnifeOption.signature);
    if (this.fileCache !== undefined) {
      this.fileCache.remove(key);
    }
  }

  /**
   * 设置taskpool默认并发数量
   * @param concurrency 默认并发数量，默认为8
   */
  setMaxRequests(concurrency: number): void {
    this.dispatcher.setMaxRequests(concurrency)
  }

  getFileCacheByFile(context: Context, key: string): ArrayBuffer | undefined {
    if (this.fileCache !== undefined) {
      return FileCache.getFileCacheByFile(context, key)
    }
    return undefined
  }

  loadFromMemoryCache(key: string): ImageKnifeData | undefined {
    if (key !== '') {
      return this.memoryCache.get(key)
    }
    return undefined
  }

  saveMemoryCache(key: string, data: ImageKnifeData): void {
    if (key !== '') {
      this.memoryCache.put(key, data)
    }
  }

  loadFromFileCache(key: string): ArrayBuffer | undefined {
    return this.fileCache?.get(key)
  }

  saveFileCache(key: string, data: ArrayBuffer): void {
    this.fileCache?.put(key, data)
  }

  getFileCache(): FileCache {
    return this.fileCache as FileCache
  }

  /**
   * get cache upper limit
   * @param cacheType
   * @returns
   */
  getCacheLimitSize(cacheType?: CacheStrategy): number | undefined {
    if (cacheType == undefined || cacheType == CacheStrategy.Default) {
      cacheType = CacheStrategy.Memory;
    }
    if (cacheType == CacheStrategy.Memory) {
      return (this.memoryCache as MemoryLruCache).maxMemory;
    } else {
      if (this.isFileCacheInit()) {
        return this.fileCache?.maxMemory;
      } else {
        throw new Error('the disk cache not init');
      }
    }
  }

  /**
   * gets the number of images currently cached
   * @param cacheType
   * @returns
   */
  getCurrentCacheNum(cacheType: CacheStrategy): number | undefined {
    if (cacheType == undefined || cacheType == CacheStrategy.Default) {
      cacheType = CacheStrategy.Memory;
    }
    if (cacheType == CacheStrategy.Memory) {
      return (this.memoryCache as MemoryLruCache).size();
    } else {
      if (this.isFileCacheInit()) {
        return this.fileCache?.size();
      } else {
        throw new Error('the disk cache not init');
      }
    }
  }

  /**
   * gets the current cache size
   * @param cacheType
   * @returns
   */
  getCurrentCacheSize(cacheType: CacheStrategy): number | undefined {
    if (cacheType == undefined || cacheType == CacheStrategy.Default) {
      cacheType = CacheStrategy.Memory;
    }
    if (cacheType == CacheStrategy.Memory) {
      return (this.memoryCache as MemoryLruCache).currentMemory;
    } else {
      if (this.isFileCacheInit()) {
        return this.fileCache?.currentMemory;
      } else {
        throw new Error('the disk cache not init');
      }
    }
  }

  private pixelMapToArrayBuffer(pixelMap: PixelMap): ArrayBuffer {
    let imageInfo = pixelMap.getImageInfoSync();
    let readBuffer: ArrayBuffer = new ArrayBuffer(imageInfo.size.height * imageInfo.size.width * 4);
    pixelMap.readPixelsToBufferSync(readBuffer);
    return readBuffer

  }

  private readMemoryCache(loadSrc: string, option: ImageKnifeOption, engineKey: IEngineKey): ImageKnifeData | undefined {
    let memoryKey = engineKey.generateMemoryKey(loadSrc, ImageKnifeRequestSource.SRC, option)
    return ImageKnife.getInstance()
      .loadFromMemoryCache(memoryKey)
  }

  private readFileCache(loadSrc: string, engineKey: IEngineKey, onComplete: (data: ImageKnifeData | undefined) => void) {
    let keys = engineKey.generateFileKey(loadSrc)
    let buffer = ImageKnife.getInstance().loadFromFileCache(keys)
    if (buffer != undefined) {
      let fileTypeUtil = new FileTypeUtil();
      let typeValue = fileTypeUtil.getFileType(buffer);
      if (typeValue === 'gif' || typeValue === 'webp') {
        let base64Help = new util.Base64Helper()

        let base64str = 'data:image/' + typeValue + ';base64,' + base64Help.encodeToStringSync(new Uint8Array(buffer))
        onComplete({
          source: base64str,
          imageWidth: 0,
          imageHeight: 0
        })
      }

      let imageSource: image.ImageSource = image.createImageSource(buffer);
      let decodingOptions: image.DecodingOptions = {
        editable: true,
      }

      imageSource.createPixelMap(decodingOptions)
        .then((pixelmap: PixelMap) => {
          onComplete({
            source: pixelmap,
            imageWidth: 0,
            imageHeight: 0
          })
          imageSource.release()
        })
    } else {
      onComplete(undefined)
    }
  }

  saveWithoutWriteFile(key: string, bufferSize: number): void {
    this.fileCache?.putWithoutWriteFile(key, bufferSize)
  }

  saveFileCacheOnlyFile(context: Context, key: string, value: ArrayBuffer): boolean {
    if (this.fileCache !== undefined) {
      return FileCache.saveFileCacheOnlyFile(context, key, value)
    }
    return false
  }

  async execute(request: ImageKnifeRequest): Promise<void> {
    LogUtil.log('ImageKnife_DataTime_execute.start:'+request.imageKnifeOption.loadSrc)
    if (this.headerMap.size > 0) {
      request.addHeaderMap(this.headerMap)
    }
    this.dispatcher.enqueue(request)
    LogUtil.log('ImageKnife_DataTime_execute.end:'+request.imageKnifeOption.loadSrc)
  }

  setEngineKeyImpl(impl: IEngineKey): void {
    this.dispatcher.setEngineKeyImpl(impl);
  }

  getEngineKeyImpl(): IEngineKey {
    return this.dispatcher.getEngineKeyImpl();
  }
  /**
   * 全局设置自定义下载
   * @param customGetImage 自定义请求函数
   */
  setCustomGetImage(customGetImage?: (context: Context, src: string | PixelMap | Resource,headers?: Record<string,Object>) => Promise<ArrayBuffer | undefined>) {
    this.customGetImage = customGetImage
  }
  getCustomGetImage(): undefined | ((context: Context, src: string | PixelMap | Resource,headers?: Record<string,Object>) => Promise<ArrayBuffer | undefined>){
    return this.customGetImage
  }
}