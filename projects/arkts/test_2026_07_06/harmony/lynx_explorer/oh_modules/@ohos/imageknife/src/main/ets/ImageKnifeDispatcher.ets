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
import { ImageKnifeRequest, ImageKnifeRequestState } from './model/ImageKnifeRequest'
import { DefaultJobQueue } from './queue/DefaultJobQueue'
import { IJobQueue } from './queue/IJobQueue'
import List from '@ohos.util.List';
import LightWeightMap from '@ohos.util.LightWeightMap';
import { LogUtil } from './utils/LogUtil';
import { ImageKnife } from './ImageKnife';
import { ImageKnifeData, CacheStrategy, TimeInfo, ErrorInfo, ImageKnifeCheckRequest } from './model/ImageKnifeData';
import image from '@ohos.multimedia.image';
import emitter from '@ohos.events.emitter';
import { Constants, LoadPhase, LoadPixelMapCode } from './utils/Constants';
import taskpool from '@ohos.taskpool';
import { IEngineKey } from './key/IEngineKey';
import { DefaultEngineKey } from './key/DefaultEngineKey';
import {
  ImageKnifeRequestWithSource,
  ImageKnifeRequestSource,
  RequestJobResult,
  RequestJobRequest
} from './model/ImageKnifeData'
import { BusinessError } from '@kit.BasicServicesKit';
import { ImageKnifeLoader } from './ImageKnifeLoader'
import { DownsampleStrategy } from './downsampling/DownsampleStartegy';
import { hiTraceMeter } from '@kit.PerformanceAnalysisKit';


export class ImageKnifeDispatcher {
  // 最大并发
  private maxRequests: number = 8
  // 排队队列
  private jobQueue: IJobQueue = new DefaultJobQueue()
  // 执行中的请求
  executingJobMap: LightWeightMap<string, List<ImageKnifeRequestWithSource>> = new LightWeightMap();
  // 开发者可配置全局缓存
  private engineKey: IEngineKey = new DefaultEngineKey();

  showFromMemomry(request: ImageKnifeRequest, imageSrc: string | PixelMap | Resource, requestSource: ImageKnifeRequestSource,isAnimator?: boolean): boolean {
    LogUtil.log('showFromMemomry.start:' + request.componentId  + ',srcType:' + requestSource + ',version:' + request.componentVersion + ' isAnimator=' + isAnimator)
    let memoryCache: ImageKnifeData | undefined;
    let memoryCheckStartTime = Date.now();
    if (requestSource === ImageKnifeRequestSource.SRC) {
      if ((typeof (request.imageKnifeOption.loadSrc as image.PixelMap)?.isEditable) == 'boolean') {
        memoryCache = {
          source: request.imageKnifeOption.loadSrc as image.PixelMap,
          imageWidth: 0,
          imageHeight: 0,
        }
      } else {
        hiTraceMeter.startTrace('getMemoryCache',request.componentId)
        memoryCache = ImageKnife.getInstance()
          .loadFromMemoryCache(this.engineKey.generateMemoryKey(imageSrc, requestSource, request.imageKnifeOption,isAnimator, request.componentWidth, request.componentHeight));
        hiTraceMeter.finishTrace('getMemoryCache',request.componentId)
      }
    } else {
      if (typeof imageSrc !== 'string') {
        request.ImageKnifeRequestCallback?.showPixelMap(request.componentVersion, imageSrc, requestSource)
        return true
      } else {
        memoryCache = ImageKnife.getInstance()
          .loadFromMemoryCache(this.engineKey.generateMemoryKey(imageSrc, requestSource, request.imageKnifeOption,isAnimator, request.componentWidth, request.componentHeight));
      }
    }


    //记录ImageKnifeRequestSource.SRC 开始内存检查的时间点
    if (requestSource == ImageKnifeRequestSource.SRC && request.imageKnifeData) {
      let timeInfo = request.imageKnifeData?.timeInfo
      if (timeInfo) {
        timeInfo.memoryCheckStartTime = memoryCheckStartTime;
        timeInfo.memoryCheckEndTime = Date.now();
        //设置请求结束的时间点
        if (memoryCache !== undefined) {
          timeInfo.requestEndTime = Date.now();
        }
      }
    }

    if (memoryCache !== undefined) {
      // 画主图
      if (request.requestState === ImageKnifeRequestState.PROGRESS) {
        // 回调请求开始
        if (requestSource === ImageKnifeRequestSource.SRC && request.imageKnifeOption.onLoadListener?.onLoadStart !== undefined) {
          request.imageKnifeOption.onLoadListener.onLoadStart(request)
        }
        request.ImageKnifeRequestCallback?.showPixelMap(request.componentVersion, memoryCache.source, requestSource,
          { width: memoryCache.imageWidth, height: memoryCache.imageHeight }, memoryCache.imageAnimator)

        if (requestSource == ImageKnifeRequestSource.SRC) {
          request.requestState = ImageKnifeRequestState.COMPLETE
          request.drawMainSuccess = true
          // 回调请求开结束
          if (request.imageKnifeOption.onLoadListener?.onLoadSuccess !== undefined) {
            this.copyMemoryCacheInfo(memoryCache, request.imageKnifeData);
            request.imageKnifeOption.onLoadListener.onLoadSuccess(memoryCache.source, memoryCache, request)
          }
        } else if (requestSource == ImageKnifeRequestSource.ERROR_HOLDER) {
          request.requestState = ImageKnifeRequestState.ERROR
        }
      }
      LogUtil.log('showFromMemomry.end_hasmemory:' + request.componentId  + ',srcType:' + requestSource + ',version:' + request.componentVersion)
      return true
    }
    LogUtil.log('showFromMemomry.end_nomemory:' + request.componentId  + ',srcType:' + requestSource + ',version:' + request.componentVersion)
    return false
  }

  private copyMemoryCacheInfo(memoryCache: ImageKnifeData | undefined, target: ImageKnifeData | undefined) {
    if (!memoryCache || !target) {
      return;
    }
    target.source = memoryCache.source;
    target.imageWidth = memoryCache.imageWidth;
    target.imageHeight = memoryCache.imageHeight;
    target.type = memoryCache.type;
    target.bufSize = memoryCache.bufSize
    target.imageAnimator = memoryCache.imageAnimator;
  }

  private assembleImageKnifeData(beforeCallData: ImageKnifeData | undefined, afterCallData: ImageKnifeData | undefined, req: ImageKnifeRequest) {
    if (!beforeCallData || !afterCallData || !req) {
      return;
    }
    //设置图片开始加载时间及其缓存检查时间点
    if (beforeCallData.timeInfo) {
      if (afterCallData.timeInfo) {
        afterCallData.timeInfo.requestStartTime = beforeCallData.timeInfo.requestStartTime;
        afterCallData.timeInfo.memoryCheckStartTime = beforeCallData.timeInfo.memoryCheckStartTime;
        afterCallData.timeInfo.memoryCheckEndTime = beforeCallData.timeInfo.memoryCheckEndTime;
      }
    }
    req.imageKnifeData = afterCallData;
  }

  private initCallData(request: ImageKnifeRequest) {
    if (!request) {
      return
    }
    //图片加载信息回调数据
    let callBackData: ImageKnifeData = {
      source: '',
      imageWidth: 0,
      imageHeight: 0,
    };

    //图片加载信息回调数据时间点
    let callBackTimeInfo: TimeInfo = {};
    callBackTimeInfo.requestStartTime = Date.now();
    callBackData.timeInfo = callBackTimeInfo;

    //跟隨請求保存回調信息點
    request.imageKnifeData = callBackData;
  }

  enqueue(request: ImageKnifeRequest,): void {
    //初始化加载回调信息
    this.initCallData(request);
    //1.内存有的话直接渲染
    if (this.showFromMemomry(request, request.imageKnifeOption.loadSrc, ImageKnifeRequestSource.SRC,request.animator)) {
      return
    }
    // 2.内存获取占位图
    if (request.imageKnifeOption.placeholderSrc !== undefined) {
      if (this.showFromMemomry(request, request.imageKnifeOption.placeholderSrc, ImageKnifeRequestSource.PLACE_HOLDER)) {
        request.drawPlayHolderSuccess = true
      }
    }
    this.executeJob(request)
  }

  checkRepeatRequests(request: ImageKnifeRequest,imageSrc: string | PixelMap | Resource, requestSource: ImageKnifeRequestSource): ImageKnifeCheckRequest | undefined {
    let memoryKey: string = this.engineKey.generateMemoryKey(imageSrc, requestSource, request.imageKnifeOption,
      requestSource === ImageKnifeRequestSource.SRC ? request.animator : undefined, request.componentWidth,
      request.componentHeight)
    //3.判断是否要排队
    if (this.executingJobMap.length >= this.maxRequests && !this.executingJobMap.get(memoryKey) && requestSource === ImageKnifeRequestSource.SRC) {
      this.jobQueue.add(request)
      return
    }
    if (request.imageKnifeOption.onLoadListener?.onLoadStart !== undefined && requestSource === ImageKnifeRequestSource.SRC) {
      request.imageKnifeOption.onLoadListener?.onLoadStart(request)
    }
    let requestList: List<ImageKnifeRequestWithSource> | undefined = this.executingJobMap.get(memoryKey)
    if (requestList === undefined) {
      requestList = new List()
      requestList.add({ request: request, source: requestSource })
      this.executingJobMap.set(memoryKey, requestList)
      return {
        memoryKey,
        requestList
      }
    } else {
      requestList.add({ request: request, source: requestSource })
      return
    }
  }

  executeJob(request: ImageKnifeRequest): void {
    LogUtil.log('executeJob.start:' + request.componentId  + ',version:' + request.componentVersion)
    // 加载占位符
    if (request.imageKnifeOption.placeholderSrc !== undefined && request.drawPlayHolderSuccess == false) {
      let checkRequests =
        this.checkRepeatRequests(request, request.imageKnifeOption.placeholderSrc, ImageKnifeRequestSource.PLACE_HOLDER)
      if (checkRequests) {
        this.getAndShowImage(request, request.imageKnifeOption.placeholderSrc, ImageKnifeRequestSource.PLACE_HOLDER,
          checkRequests.memoryKey, checkRequests.requestList)
      }
    }
    let checkRequests =
      this.checkRepeatRequests(request, request.imageKnifeOption.loadSrc, ImageKnifeRequestSource.SRC)
    if (checkRequests) {
      // 加载主图
      this.getAndShowImage(request, request.imageKnifeOption.loadSrc, ImageKnifeRequestSource.SRC,
        checkRequests.memoryKey, checkRequests.requestList, request.animator)
    }
    LogUtil.log('executeJob.end:' + request.componentId  + ',version:' + request.componentVersion)
  }

  /**
   * 获取和显示图片
   */
  getAndShowImage(currentRequest: ImageKnifeRequest, imageSrc: string | PixelMap | Resource,
    requestSource: ImageKnifeRequestSource, memoryKey: string, requestList: List<ImageKnifeRequestWithSource>,
    isAnimator?: boolean): void {
    LogUtil.log('getAndShowImage.start:'  + currentRequest.componentId + ',srcType:' + requestSource + ',version:' + currentRequest.componentVersion)
    if (requestSource === ImageKnifeRequestSource.SRC && imageSrc === 'ImageKnife') {
      this.executingJobMap.remove(memoryKey)
      this.dispatchNextJob()
      LogUtil.error('loadSrc parameter is not passed:' + currentRequest.componentId + ',srcType:' + requestSource + ',version:' + currentRequest.componentVersion)
      return
    }
    LogUtil.info('image load getAndShowImage start:' + currentRequest.componentId + ',srcType:' + requestSource + ',version:' + currentRequest.componentVersion)
    let isWatchProgress : boolean = false
    if (currentRequest.imageKnifeOption.progressListener !== undefined && requestSource === ImageKnifeRequestSource.SRC) {
      isWatchProgress = true
    }

    let src: string | number = ''
    let moduleName: string = ''
    let resName: string = ''
    if((imageSrc as Resource)?.id != undefined) {
      moduleName = (imageSrc as Resource).moduleName
      src = (imageSrc as Resource).id
      resName = (imageSrc as Resource).params![0]
    } else if(typeof imageSrc == 'string') {
      src = imageSrc
    }
    let request: RequestJobRequest = {
      context: currentRequest.context,
      src: src,
      headers: currentRequest.imageKnifeOption.headerOption,
      allHeaders: currentRequest.headers,
      componentWidth:currentRequest.componentWidth,
      componentHeight:currentRequest.componentHeight,
      customGetImage: currentRequest.imageKnifeOption.customGetImage,
      onlyRetrieveFromCache: currentRequest.imageKnifeOption.onlyRetrieveFromCache,
      transformation: currentRequest.imageKnifeOption.transformation,
      writeCacheStrategy: ImageKnife.getInstance()
        .isFileCacheInit() ? currentRequest.imageKnifeOption.writeCacheStrategy : CacheStrategy.Memory, // 未初始化文件缓存时，不写文件缓存
      engineKey: this.engineKey,
      signature: currentRequest.imageKnifeOption.signature,
      requestSource: requestSource,
      isWatchProgress: isWatchProgress,
      memoryKey: memoryKey,
      fileCacheFolder: ImageKnife.getInstance().getFileCache()?.getCacheFolder(),
      isAnimator:isAnimator,
      moduleName: moduleName == '' ? undefined : moduleName,
      resName: resName == '' ? undefined : resName,
      caPath: currentRequest.imageKnifeOption.httpOption?.caPath,
      targetWidth: currentRequest.componentWidth,
      targetHeight: currentRequest.componentHeight,
      downsampType: currentRequest.imageKnifeOption.downsampleOf == undefined ? DownsampleStrategy.DEFAULT : currentRequest.imageKnifeOption.downsampleOf,
      isAutoImageFit: currentRequest.imageKnifeOption.objectFit == ImageFit.Auto,
      componentId: currentRequest.componentId,
      componentVersion: currentRequest.componentVersion,
      connectTimeout: currentRequest.imageKnifeOption.httpOption?.connectTimeout ?? ImageKnife.getInstance().getConnectTimeout(),
      readTimeout: currentRequest.imageKnifeOption.httpOption?.readTimeout ?? ImageKnife.getInstance().getReadTimeout()
    }

    if(request.customGetImage == undefined) {
      request.customGetImage = ImageKnife.getInstance().getCustomGetImage()
    }
    emitter.on(Constants.CALLBACK_EMITTER + memoryKey,(data)=>{
      emitter.off(Constants.CALLBACK_EMITTER + memoryKey)
      let res = data?.data?.value as RequestJobResult | undefined
      this.doTaskCallback(res, requestList!, currentRequest, memoryKey, imageSrc, requestSource,isAnimator);
      if (isWatchProgress){
        emitter.off(Constants.PROGRESS_EMITTER + memoryKey)
      }
      LogUtil.log('getAndShowImage.end:'+ currentRequest.componentId + ',srcType:' + requestSource + ',version:' + currentRequest.componentVersion)
    })
    if (ImageKnife.getInstance().isRequestInSubThread){
      // 启动线程下载和解码主图
      LogUtil.log('etAndShowImage_Task.start:' + currentRequest.componentId + ',srcType:' + requestSource + ',version:' + currentRequest.componentVersion)
      let task = new taskpool.Task(requestJob, request)
      LogUtil.log('getAndShowImage_Task.end:' + currentRequest.componentId + ',srcType:' + requestSource + ',version:' + currentRequest.componentVersion)
      if (isWatchProgress){
        emitter.on(Constants.PROGRESS_EMITTER + memoryKey, (data) => {
          this.progressCallBack(requestList! , data?.data?.value as number)
        });
      }

      LogUtil.log('getAndShowImage_execute.start(subthread):' + currentRequest.componentId + ',srcType:' + requestSource + ',version:' + currentRequest.componentVersion)
      taskpool.execute(task).then((res: Object) => {
      }).catch((err: BusinessError) => {
        emitter.off(Constants.CALLBACK_EMITTER + memoryKey)
        LogUtil.error('Fail to requestJob in sub thread err=' + err + ',id:' + currentRequest.componentId +
          ',version:' + currentRequest.componentVersion + ',url:' + imageSrc)
        if (isWatchProgress){
          emitter.off(Constants.PROGRESS_EMITTER + memoryKey)
        }

        this.doTaskCallback({
          pixelMap: undefined,
          bufferSize: 0,
          fileKey: '',
          loadFail: 'Fail to requestJob in sub thread err=' + err,
          imageKnifeData: {
            source: '',
            imageWidth: 0,
            imageHeight: 0,
            timeInfo: { requestEndTime: Date.now() },
            errorInfo: {
              phase: LoadPhase.PHASE_LOAD,
              code: LoadPixelMapCode.IMAGE_CUSTOM_LOAD_FAILED_CODE,
            }
          }
        }, requestList!, currentRequest, memoryKey, imageSrc, requestSource, isAnimator)
      })
      currentRequest.taskRequest = task
    } else { //主线程请求
      LogUtil.log('getAndShowImage_execute.start(mainthread):' + currentRequest.componentId + ',srcType:' + requestSource + ',version:' + currentRequest.componentVersion)
      requestJob(request, requestList).then(() => {
      }).catch((err: BusinessError) => {
        emitter.off(Constants.CALLBACK_EMITTER + memoryKey)
        LogUtil.error('Fail to requestJob in sub thread err=' + err + ',id:' + currentRequest.componentId +
          ',version:' + currentRequest.componentVersion + ',url:' + imageSrc)

        this.doTaskCallback({
          pixelMap: undefined,
          bufferSize: 0,
          fileKey: '',
          loadFail: 'Fail to requestJob in main thread err=' + err,
          imageKnifeData: {
            source: '',
            imageWidth: 0,
            imageHeight: 0,
            timeInfo: { requestEndTime: Date.now() },
            errorInfo: {
              phase: LoadPhase.PHASE_LOAD,
              code: LoadPixelMapCode.IMAGE_CUSTOM_LOAD_FAILED_CODE,
            }
          }
        }, requestList!, currentRequest, memoryKey, imageSrc, requestSource, isAnimator)
      })
    }
  }

  /**
   * 回调下载进度
   * @param requestList 请求列表
   * @param data 进度
   */
  private progressCallBack(requestList:List<ImageKnifeRequestWithSource>, data: number) {
    for (let i = 0; i < requestList.length; i++) {
      let requestWithSource:ImageKnifeRequestWithSource = requestList[i]
      if (requestWithSource.request.imageKnifeOption.progressListener !== undefined && requestWithSource.source === ImageKnifeRequestSource.SRC) {
        requestWithSource.request.imageKnifeOption.progressListener(data)
      }
    }
  }

  private doTaskCallback(requestJobResult: RequestJobResult | undefined, requestList: List<ImageKnifeRequestWithSource> ,
    currentRequest: ImageKnifeRequest, memoryKey: string, imageSrc: string | PixelMap | Resource, requestSource: ImageKnifeRequestSource,isAnimator?: boolean):void {
    LogUtil.log('getAndShowImage_CallBack.start:' + currentRequest.componentId + ',srcType:' + requestSource + ',version:' + currentRequest.componentVersion)
    if (requestJobResult === undefined){
      return
    }

    //设置请求结束的时间
    if (requestJobResult.imageKnifeData && requestJobResult.imageKnifeData.timeInfo) {
      requestJobResult.imageKnifeData.timeInfo.requestEndTime = Date.now();
    }


    // 保存文件缓存
    if (requestJobResult.bufferSize > 0 && currentRequest.imageKnifeOption.writeCacheStrategy !== CacheStrategy.Memory) {
      LogUtil.log('getAndShowImage_saveWithoutWriteFile.start:' + currentRequest.componentId + ',srcType:' + requestSource + ',version:' + currentRequest.componentVersion)
      ImageKnife.getInstance().saveWithoutWriteFile(requestJobResult.fileKey, requestJobResult.bufferSize);
      LogUtil.log('getAndShowImage_saveWithoutWriteFile.end:' + currentRequest.componentId + ',srcType:' + requestSource + ',version:' + currentRequest.componentVersion)
    }

    let pixelmap = requestJobResult.pixelMap;
    // 请求取消
    if (currentRequest.requestState === ImageKnifeRequestState.DESTROY) {
      this.executingJobMap.remove(memoryKey);
      requestList.forEach((requestWithSource: ImageKnifeRequestWithSource) => {
        if ((currentRequest.componentId !== requestWithSource.request.componentId ||
          currentRequest.componentVersion !== requestWithSource.request.componentVersion) &&
          requestWithSource.request.requestState !== ImageKnifeRequestState.DESTROY) {
          // 加载占位符
          if (requestWithSource.source === ImageKnifeRequestSource.PLACE_HOLDER &&
            requestWithSource.request.imageKnifeOption.placeholderSrc !== undefined &&
            requestWithSource.request.drawPlayHolderSuccess == false) {
            let checkRequests =
              this.checkRepeatRequests(requestWithSource.request,
                requestWithSource.request.imageKnifeOption.placeholderSrc, ImageKnifeRequestSource.PLACE_HOLDER)
            if (checkRequests) {
              this.getAndShowImage(requestWithSource.request, requestWithSource.request.imageKnifeOption.placeholderSrc,
                ImageKnifeRequestSource.PLACE_HOLDER,
                checkRequests.memoryKey, checkRequests.requestList)
            }
          } else if (requestWithSource.source === ImageKnifeRequestSource.ERROR_HOLDER &&
            requestWithSource.request.imageKnifeOption.errorholderSrc !== undefined) {
            let checkRequests =
              this.checkRepeatRequests(requestWithSource.request,
                requestWithSource.request.imageKnifeOption.errorholderSrc, ImageKnifeRequestSource.ERROR_HOLDER)
            if (checkRequests) {
              this.getAndShowImage(requestWithSource.request, requestWithSource.request.imageKnifeOption.errorholderSrc,
                ImageKnifeRequestSource.ERROR_HOLDER,
                checkRequests.memoryKey, checkRequests.requestList)
            }
          } else if (requestWithSource.source === ImageKnifeRequestSource.SRC) {
            let checkRequests =
              this.checkRepeatRequests(requestWithSource.request, requestWithSource.request.imageKnifeOption.loadSrc, ImageKnifeRequestSource.SRC)
            if (checkRequests) {
              // 加载主图
              this.getAndShowImage(requestWithSource.request, requestWithSource.request.imageKnifeOption.loadSrc, ImageKnifeRequestSource.SRC,
                checkRequests.memoryKey, checkRequests.requestList, requestWithSource.request.animator)
            }
          }
        } else {
          if (pixelmap !== undefined && typeof pixelmap !== 'string') {
            (pixelmap as PixelMap).release()
          }
          if (requestWithSource.source == ImageKnifeRequestSource.SRC && requestWithSource.request.imageKnifeOption.onLoadListener?.onLoadCancel) {
            // 回调请求成功
            // 回调请求成功
            //设置失败回调的时间点
            let callBackData = requestWithSource.request.imageKnifeData;

            if (requestJobResult.imageKnifeData && requestJobResult.imageKnifeData.timeInfo) {
              requestJobResult.imageKnifeData.timeInfo.requestCancelTime = Date.now();
              if (requestJobResult.imageKnifeData.errorInfo) {
                requestJobResult.imageKnifeData.errorInfo.phase = LoadPhase.PHASE_WILL_SHOW;
                requestJobResult.imageKnifeData.errorInfo.code = LoadPixelMapCode.IMAGE_LOAD_CANCEL_FAILED_CODE;
              }
            }
            this.assembleImageKnifeData(callBackData,requestJobResult.imageKnifeData,requestWithSource.request)
            LogUtil.log('getAndShowImage cancel:' + requestWithSource.request.componentId  + ',srcType:' + requestSource + ',version:' + requestWithSource.request.componentVersion)
            requestWithSource.request.imageKnifeOption.onLoadListener.onLoadCancel(requestJobResult.loadFail ?? 'component has destroyed from load', requestWithSource.request)
          }
        }
      })
      this.dispatchNextJob()
      return
    }
    // 请求失败
    if (pixelmap === undefined) {
      this.executingJobMap.remove(memoryKey);
      requestList.forEach((requestWithSource: ImageKnifeRequestWithSource) => {
        requestWithSource.request.requestState = ImageKnifeRequestState.ERROR
        LogUtil.error('getAndShowImage_CallBack.pixelmap failed:' + requestWithSource.request.componentId + ',srcType:' +
          requestSource + ',version:' + requestWithSource.request.componentVersion + " error: " + requestJobResult.loadFail)
        // 回调请求失败
        if (requestWithSource.request.ImageKnifeRequestCallback?.mainLoadError && requestJobResult.loadFail) {
          requestWithSource.request.ImageKnifeRequestCallback?.mainLoadError(requestJobResult.loadFail)
        }
        if (requestWithSource.source === ImageKnifeRequestSource.SRC &&
          requestWithSource.request.imageKnifeOption.onLoadListener?.onLoadFailed !== undefined &&
        requestJobResult.loadFail) {
          this.assembleImageKnifeData(requestWithSource.request.imageKnifeData, requestJobResult.imageKnifeData,
            requestWithSource.request)
          requestWithSource.request.imageKnifeOption.onLoadListener.onLoadFailed(requestJobResult.loadFail,
            requestWithSource.request);
        }
        if (requestWithSource.source === ImageKnifeRequestSource.SRC &&
          requestWithSource.request.imageKnifeOption.errorholderSrc !== undefined) {
          requestWithSource.request.requestState = ImageKnifeRequestState.PROGRESS
          if (this.showFromMemomry(requestWithSource.request, requestWithSource.request.imageKnifeOption.errorholderSrc,
            ImageKnifeRequestSource.ERROR_HOLDER) === false) {
            let checkRequests =
              this.checkRepeatRequests(requestWithSource.request,
                requestWithSource.request.imageKnifeOption.errorholderSrc, ImageKnifeRequestSource.ERROR_HOLDER)
            if (checkRequests) {
              this.getAndShowImage(requestWithSource.request, requestWithSource.request.imageKnifeOption.errorholderSrc,
                ImageKnifeRequestSource.ERROR_HOLDER,
                checkRequests.memoryKey, checkRequests.requestList)
            }
          }
        }
      });
      this.dispatchNextJob();
      return;
    }

    let imageKnifeData: ImageKnifeData;
    if (!requestJobResult.imageKnifeData) {
      imageKnifeData = {
        source: pixelmap!,
        imageWidth: requestJobResult.size == undefined ? 0 : requestJobResult.size.width,
        imageHeight: requestJobResult.size == undefined ? 0 : requestJobResult.size.height,
        type: requestJobResult.type,
      };
    } else {
      imageKnifeData = requestJobResult.imageKnifeData;
      imageKnifeData.source = pixelmap!;
    }

    if(requestJobResult.pixelMapList != undefined) {
      let imageAnimator: Array<ImageFrameInfo> = []
      requestJobResult.pixelMapList.forEach((item,index)=>{
        imageAnimator.push({
          src:requestJobResult.pixelMapList![index],
          duration:requestJobResult.delayList![index]
        })
      })
      imageKnifeData.imageAnimator = imageAnimator
    }

    //构建缓存保存的ImageKnifeData
    let saveCacheImageData: ImageKnifeData = {
      source: pixelmap!,
      imageWidth: requestJobResult.size?.width ?? 0,
      imageHeight: requestJobResult.size?.height ?? 0,
      type: requestJobResult.type,
      bufSize: requestJobResult.bufferSize,
      imageAnimator: imageKnifeData.imageAnimator
    }

    // 保存内存缓存
    if (currentRequest.imageKnifeOption.writeCacheStrategy !== CacheStrategy.File) {
      LogUtil.log('getAndShowImage_saveMemoryCache.start:' + currentRequest.componentId + ',srcType:' + requestSource + ',version:' + currentRequest.componentVersion)
      hiTraceMeter.startTrace('saveMemoryCache',currentRequest.componentId)
      ImageKnife.getInstance()
        .saveMemoryCache(this.engineKey.generateMemoryKey(imageSrc, requestSource, currentRequest.imageKnifeOption,isAnimator, currentRequest.componentWidth, currentRequest.componentHeight),
          saveCacheImageData);
      hiTraceMeter.finishTrace('saveMemoryCache',currentRequest.componentId)
      LogUtil.log('getAndShowImage_saveMemoryCache.end:' + currentRequest.componentId + ',srcType:' + requestSource + ',version:' + currentRequest.componentVersion)
    }
    if (requestList !== undefined) {
      // key相同的request，一起绘制
      requestList.forEach((requestWithSource: ImageKnifeRequestWithSource) => {
        // 画主图
        if (requestWithSource.source === ImageKnifeRequestSource.SRC ||
          requestWithSource.source === ImageKnifeRequestSource.ERROR_HOLDER
          || (requestWithSource.source === ImageKnifeRequestSource.PLACE_HOLDER &&
            requestWithSource.request.requestState === ImageKnifeRequestState.PROGRESS)) {
          requestWithSource.request.ImageKnifeRequestCallback?.showPixelMap(requestWithSource.request.componentVersion,
            imageKnifeData.source, requestWithSource.source,
            { width: imageKnifeData.imageWidth, height: imageKnifeData.imageHeight },
            imageKnifeData.imageAnimator);
        }

        if (requestWithSource.source == ImageKnifeRequestSource.SRC) {
          requestWithSource.request.requestState = ImageKnifeRequestState.COMPLETE;
          requestWithSource.request.drawMainSuccess = true
          if (requestWithSource.request.imageKnifeOption.onLoadListener &&
          requestWithSource.request.imageKnifeOption.onLoadListener.onLoadSuccess) {
            // 回调请求成功
            this.assembleImageKnifeData(requestWithSource.request.imageKnifeData, imageKnifeData,
              requestWithSource.request);
            requestWithSource.request.imageKnifeOption.onLoadListener.onLoadSuccess(imageKnifeData.source,
              saveCacheImageData, requestWithSource.request);
          }
        } else if (requestWithSource.source == ImageKnifeRequestSource.ERROR_HOLDER) {
          requestWithSource.request.requestState = ImageKnifeRequestState.ERROR;
        } else {
          requestWithSource.request.drawPlayHolderSuccess = true
        }
      });
      this.executingJobMap.remove(memoryKey);
      this.dispatchNextJob();
    } else {
      LogUtil.log('error: no requestlist need to draw for key = ' + memoryKey);
    }
    LogUtil.log('getAndShowImage_CallBack.end:' + currentRequest.componentId + ',srcType:' + requestSource + ',version:' + currentRequest.componentVersion)
  }


  dispatchNextJob() {
    LogUtil.log('dispatchNextJob.start')

    // 主图和错误图并发加载时，以及主图加载失败后立即加载错误图，可能会导致短时间内并发数超过maxRequests，故此处减少响应的并发
    if (this.executingJobMap.length >= this.maxRequests) {
      return
    }

    while (true) {
      let request = this.jobQueue.pop()
      if (request === undefined) {
        LogUtil.log('dispatchNextJob.end:no any job')
        break // 队列已无任务
      }
      else if (request.requestState === ImageKnifeRequestState.PROGRESS) {
        if (!request.drawPlayHolderSuccess && request.imageKnifeOption.placeholderSrc !== undefined) {
          if (this.showFromMemomry(request, request.imageKnifeOption.placeholderSrc, ImageKnifeRequestSource.PLACE_HOLDER)) {
            request.drawPlayHolderSuccess = true
          }
        }
        LogUtil.log('dispatchNextJob.start executeJob:' + request.componentId  + ',version:' + request.componentVersion)
        this.executeJob(request)
        LogUtil.log('dispatchNextJob.end executeJob:' + request.componentId  + ',version:' + request.componentVersion)
        break
      }else if (request.requestState == ImageKnifeRequestState.DESTROY && request.imageKnifeOption.onLoadListener?.onLoadCancel) {
        //构建回调错误信息
        let callBackData = request.imageKnifeData;
        if (callBackData) {
          let timeInfo: TimeInfo =  ImageKnifeLoader.getTimeInfo(callBackData)
          timeInfo.requestCancelTime = Date.now();
          timeInfo.requestEndTime = Date.now()
          let errorInfo: ErrorInfo = {
            phase: LoadPhase.PHASE_THREAD_QUEUE,
            code: LoadPixelMapCode.IMAGE_LOAD_CANCEL_FAILED_CODE,
          };
          callBackData.errorInfo = errorInfo;
        }
        LogUtil.log('dispatchNextJob cancel:' + request.componentId  + ',version:' + request.componentVersion)
        request.imageKnifeOption.onLoadListener.onLoadCancel('component has destroyed from queue', request)
      }
    }
  }

  setMaxRequests(concurrency: number): void {
    if (concurrency > 0) {
      this.maxRequests = concurrency
    }
  }

  setEngineKeyImpl(impl: IEngineKey): void {
    this.engineKey = impl;
  }

  getEngineKeyImpl(): IEngineKey {
    return this.engineKey;
  }
}

/**
 * 通过taskpool 二级缓存，下载/读取本地文件，编解码
 * @param context
 * @param src
 * @returns
 */
@Concurrent
async function requestJob(request: RequestJobRequest, requestList?: List<ImageKnifeRequestWithSource>) {
  LogUtil.log('requestJob.start:' + request.componentId + ',srcType:' + request.requestSource + ',' + request.componentVersion)
  let src = typeof request.src == 'number' ? request.resName != undefined ? request.resName : request.src + '' : request.src
  // 生成文件缓存key
  let fileKey = request.engineKey.generateFileKey(src, request.signature, request.isAnimator)

  //获取图片资源
  ImageKnifeLoader.execute(request,requestList,fileKey)

}



