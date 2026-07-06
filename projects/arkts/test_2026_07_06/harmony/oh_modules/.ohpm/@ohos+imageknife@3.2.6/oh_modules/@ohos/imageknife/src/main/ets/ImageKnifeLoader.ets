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
import {
  CacheStrategy,
  DecodeImageInfo,
  ErrorInfo,
  FlipRotate,
  ImageKnifeData,
  ImageKnifeRequestSource,
  ImageKnifeRequestWithSource, RequestJobRequest,
  TimeInfo } from './model/ImageKnifeData';
import List from '@ohos.util.List'
import { FileCache } from './cache/FileCache';
import { LogUtil } from './utils/LogUtil';
import { Constants, LoadPhase, LoadPixelMapCode } from './utils/Constants';
import http from '@ohos.net.http';
import { combineArrayBuffers } from './utils/ArrayBufferUtils';
import { BusinessError } from '@kit.BasicServicesKit';
import fs from '@ohos.file.fs';
import emitter from '@ohos.events.emitter';
import image from '@ohos.multimedia.image';
import { RequestJobResult } from './model/ImageKnifeData'
import util from '@ohos.util';
import { FileTypeUtil } from './utils/FileTypeUtil';
import { DownsampleStrategy } from './downsampling/DownsampleStartegy';
import { Downsampler } from './downsampling/Downsampler';
import { common } from '@kit.AbilityKit';
import { ImageLoaderFactory } from './loaderStrategy/ImageLoaderFactory';
import { taskpool } from '@kit.ArkTS';
import { hiTraceMeter } from '@kit.PerformanceAnalysisKit';

class RequestData {
  receiveSize: number = 2000
  totalSize: number = 2000
}

/**
 * ImageKnifeDispatcher 抽取出来的方法，因@Concurrent只能import方法，故抽取到另一个类
 */
export class ImageKnifeLoader {
  static execute(request: RequestJobRequest, requestList: List<ImageKnifeRequestWithSource> | undefined, fileKey: string){
    ImageKnifeLoader.getImageArrayBuffer(request,requestList,fileKey)
  }
  static getUnit8Array (resBuf: ArrayBuffer) {
    let unit8 = new Uint8Array(resBuf)
    let unitString = ''
    if (unit8.length >= 3) {
      unitString = unit8[0] + ',' + unit8[1] + ',' + unit8[2]
    } else if (unit8.length > 0 && unit8.length < 3) {
      unitString = unit8.length + ''
    }
    return unitString
  }
  static async parseImage(resBuf: ArrayBuffer, fileKey: string,
    request: RequestJobRequest, callBackData: ImageKnifeData,headerObj?: Record<string, Object>): Promise<RequestJobResult | undefined> {
    callBackData.bufSize = resBuf.byteLength;
    let typeValue = new FileTypeUtil().getFileType(resBuf);
    if(typeValue == null) {
      LogUtil.log('requestJob.end: getFileType is null: ' + request.componentId + ',srcType:' + request.requestSource + ',' + request.componentVersion)
      ImageKnifeLoader.makeEmptyResult(request,
        'request is not a valid image source:' + request.src + ' ,componentId' + request.componentId + ',srcType:' +
        request.requestSource + ',' +
        request.componentVersion + ',buffer:' + resBuf.byteLength + ',unit8:' + ImageKnifeLoader.getUnit8Array(resBuf) +
          ',header:' + JSON.stringify(headerObj),
        ImageKnifeLoader.assembleError(callBackData, LoadPhase.PHASE_GET_FORMAT,
          LoadPixelMapCode.IMAGE_PARSE_FORMAT_FAILED_CODE))
      return
    }
    callBackData.type = typeValue;
    if(request.isAnimator) {
      return ImageKnifeLoader.parseForAnimatorComponent(resBuf ,typeValue ,fileKey, request, callBackData)
    }

    if (typeValue === 'gif' || typeValue === 'webp') {
      return ImageKnifeLoader.parseAnimatorImage(resBuf ,typeValue ,fileKey , request, callBackData)
    } else if(typeValue == 'svg') {
      return ImageKnifeLoader.parseSvgImage(resBuf ,typeValue ,fileKey , request, callBackData)
    }

    return ImageKnifeLoader.parseNormalImage(resBuf, typeValue, fileKey, request, callBackData)
  }

  static makeEmptyResult(request:RequestJobRequest,error: string, data?: ImageKnifeData){
    let res: RequestJobResult = {
      pixelMap: undefined,
      bufferSize: 0,
      fileKey: '',
      loadFail: error,
      imageKnifeData: data
    }
    emitter.emit(Constants.CALLBACK_EMITTER + request.memoryKey, { data: { 'value': res } })
  }

  static assembleError(data: ImageKnifeData | undefined, phase: string, code?: number): ImageKnifeData | undefined {
    let errorCallBackData = data?.errorInfo;
    if (!errorCallBackData) {
      return data;
    }
    errorCallBackData.phase = phase;
    errorCallBackData.code = code? code: 0;
    return data
  }

  static getTimeInfo(callBackData: ImageKnifeData): TimeInfo {
    let timeInfo: TimeInfo;
    if (callBackData.timeInfo) {
      timeInfo = callBackData.timeInfo;
    }else {
      timeInfo = {};
      callBackData.timeInfo = timeInfo;
    }
    return timeInfo;
  }
  static async  parseFile(resBuf: ArrayBuffer, fileKey: string,
    request: RequestJobRequest, callBackData: ImageKnifeData,saveFile?: boolean,headerObj?: Record<string, Object>) {
    let res = await ImageKnifeLoader.parseImage(resBuf,fileKey,request,callBackData,headerObj)
    // 保存文件缓存
    if (res && saveFile && request.writeCacheStrategy !== CacheStrategy.Memory) {
      LogUtil.log('requestJob_saveFileCacheOnlyFile.start:' + request.componentId + ',srcType:' + request.requestSource + ',' + request.componentVersion)
      hiTraceMeter.startTrace('saveFileCache',request.componentId)
      FileCache.saveFileCacheOnlyFile(request.context, fileKey, resBuf , request.fileCacheFolder)
      hiTraceMeter.finishTrace('saveFileCache',request.componentId)
      LogUtil.log('requestJob_saveFileCacheOnlyFile.end:' + request.componentId + ',srcType:' + request.requestSource + ',' + request.componentVersion)
    }
    if (res) {
      emitter.emit(Constants.CALLBACK_EMITTER + request.memoryKey, { data: { 'value': res } })
    }
  }
  static async parseNormalImage(resBuf: ArrayBuffer, typeValue: string, fileKey: string, request: RequestJobRequest, callBackData: ImageKnifeData): Promise<RequestJobResult | undefined> {
    LogUtil.log('image parse pixelmap start:' + request.componentId + ',srcType:' + request.requestSource + ',' + request.componentVersion)
    let resPixelmap: PixelMap | undefined = undefined
    hiTraceMeter.startTrace('parseImage',request.componentId)
    let timeInfo: TimeInfo = ImageKnifeLoader.getTimeInfo(callBackData);

    let decodingOptions: image.DecodingOptions = {
      editable: request.requestSource === ImageKnifeRequestSource.SRC && request.transformation !== undefined ? true : false,
    }
    let imageSource: image.ImageSource = image.createImageSource(resBuf)
    if (imageSource === undefined){
      ImageKnifeLoader.makeEmptyResult(request,'image.createImageSource failed', ImageKnifeLoader.assembleError(callBackData, LoadPhase.PHASE_CREATE_SOURCE, LoadPixelMapCode.IMAGE_SOURCE_ERROR_CODE))
      return
    }

    let imageInfoSync = imageSource.getImageInfoSync()
    if (imageInfoSync == undefined){
      imageSource.release()
      ImageKnifeLoader.makeEmptyResult(request, 'getImageInfoSync failed')
      return
    }
    let size = imageInfoSync.size
    callBackData.imageWidth = size.width;
    callBackData.imageHeight = size.height;

    if (request.isAutoImageFit && request.requestSource == ImageKnifeRequestSource.SRC){
      request.componentHeight = request.componentWidth * size.height / size.width
    }

    try {
      if ((request.downsampType !== DownsampleStrategy.NONE) &&
        request.requestSource == ImageKnifeRequestSource.SRC) {
        decodingOptions =
          ImageKnifeLoader.getDownsamplerDecodingOptions(typeValue, request, size, ImageKnifeRequestSource.SRC)
      }
    } catch (err) {
      imageSource.release()
      ImageKnifeLoader.makeEmptyResult(request, 'getDownsamplerDecodingOptions failed:' + err)
      return
    }
    timeInfo.decodeStartTime = Date.now();

    // 获取旋转信息
    let exif: string | undefined = undefined;
    await imageSource.getImageProperty(image.PropertyKey.ORIENTATION).then((res)=>{
      exif = res;
    }).catch((error: BusinessError)=>{
      LogUtil.info("The normal image don't have rotation information, " + error.message);
    })

    await imageSource.createPixelMap(decodingOptions)
      .then((pixelmap: PixelMap) => {
        timeInfo.decodeEndTime = Date.now();
        resPixelmap = pixelmap
        imageSource.release()
      }).catch((error: BusinessError) => {
        timeInfo.decodeEndTime = Date.now();
        imageSource.release()
        ImageKnifeLoader.makeEmptyResult(request, 'createPixelMap failed:' + JSON.stringify(error),
          ImageKnifeLoader.assembleError(callBackData, LoadPhase.PHASE_CREATE_PIXEL_MAP, LoadPixelMapCode.IMAGE_DECODE_ERROR_CODE))
        return
      })
    if (request.requestSource === ImageKnifeRequestSource.SRC && request.transformation !== undefined && resPixelmap !== undefined) {
      LogUtil.log('requestJob.transform.start:' + request.componentId + ',srcType:' + request.requestSource + ',' + request.componentVersion)
      resPixelmap = await request.transformation?.transform(request.context, resPixelmap,  request.componentWidth, request.componentHeight);
      LogUtil.log('requestJob.transform.end:' + request.componentId + ',srcType:' + request.requestSource + ',' + request.componentVersion)
    }
    try {
      resPixelmap?.setTransferDetached(true)
    } catch (e) {
      LogUtil.error('PixelMap setTransferDetached failed:' + JSON.stringify(e))
    }
    // 设置翻转和旋转角度
    if(exif && exif !== 'Top-left'){
      let result = ImageKnifeLoader.getOrientation(exif);
      if(result.horizontal || result.vertical) {
        resPixelmap?.flipSync(result.horizontal, result.vertical);
      }
      if(result.rotate > 0) {
        resPixelmap?.rotateSync(result.rotate);
      }
      LogUtil.log('The normal image set flip , horizontal=' + result.horizontal + ', vertical=' +result.vertical + ', rotate=' + result.rotate);
    }

    //获取各个pixelMap的大小
    if (resPixelmap !== undefined) {
      let decodeImages: DecodeImageInfo[] = [];
      let size = (resPixelmap as PixelMap).getImageInfoSync().size;
      let decodeImage: DecodeImageInfo = {
        contentWidth: size.width,
        contentHeight: size.height,
        contentSize: (resPixelmap as PixelMap).getPixelBytesNumber()
      }
      decodeImages.push(decodeImage);
      callBackData.decodeImages = decodeImages;
    }
    LogUtil.log('image parse pixelmap end:' + request.componentId + ',srcType:' + request.requestSource + ',' + request.componentVersion)
    hiTraceMeter.finishTrace('parseImage',request.componentId)

    return {
      pixelMap: resPixelmap,
      bufferSize: resBuf.byteLength,
      fileKey: fileKey,
      size:size,
      type:typeValue,
      imageKnifeData:callBackData
    }
  }
  static async parseSvgImage(resBuf: ArrayBuffer, typeValue: string, fileKey: string,
    request: RequestJobRequest, callBackData: ImageKnifeData): Promise<RequestJobResult | undefined> {
    let resPixelmap: PixelMap | undefined = undefined
    let timeInfo: TimeInfo = ImageKnifeLoader.getTimeInfo(callBackData);

    let imageSource: image.ImageSource = image.createImageSource(resBuf)
    if (imageSource === undefined){
      ImageKnifeLoader.makeEmptyResult(request,'image.createImageSource failed', ImageKnifeLoader.assembleError(callBackData, LoadPhase.PHASE_CREATE_SOURCE, LoadPixelMapCode.IMAGE_SOURCE_ERROR_CODE))
      return
    }

    let imageInfoSync = imageSource.getImageInfoSync()
    if (imageInfoSync == undefined){
      imageSource.release()
      ImageKnifeLoader.makeEmptyResult(request, 'getImageInfoSync failed')
      return
    }
    let size = imageInfoSync.size
    let scale = size.height / size.width
    let hValue = Math.round(request.componentHeight);
    let wValue = Math.round(request.componentWidth);
    let defaultSize: image.Size = {
      height: vp2px(wValue) * scale,
      width: vp2px(wValue)
    };
    let opts: image.DecodingOptions = {
      editable: true,
      desiredSize: defaultSize
    };
    callBackData.imageWidth = size.width;
    callBackData.imageHeight = size.height;
    try {
      if ((request.downsampType !== DownsampleStrategy.NONE) &&
        request.requestSource == ImageKnifeRequestSource.SRC) {
        opts = ImageKnifeLoader.getDownsamplerDecodingOptions(typeValue, request, size)
      }
    } catch (err) {
      imageSource.release()
      ImageKnifeLoader.makeEmptyResult(request,'getDownsamplerDecodingOptions failed:' + err)
      return
    }
    timeInfo.decodeStartTime = Date.now();

    // 获取旋转信息
    let exif: string | undefined = undefined;
    await imageSource.getImageProperty(image.PropertyKey.ORIENTATION).then((res)=>{
      exif = res;
    }).catch((error: BusinessError)=>{
      LogUtil.info("Svg image don't have rotation information, " + error.message);
    })

    await imageSource.createPixelMap(opts)
      .then((pixelmap: PixelMap) => {
        timeInfo.decodeEndTime = Date.now();
        resPixelmap = pixelmap
        imageSource.release()
        try {
          resPixelmap.setTransferDetached(true)
          // 设置翻转和旋转角度
          if(exif && exif !== 'Top-left'){
            let result = ImageKnifeLoader.getOrientation(exif);
            if(result.horizontal || result.vertical) {
              resPixelmap?.flipSync(result.horizontal, result.vertical);
            }
            if(result.rotate > 0) {
              resPixelmap?.rotateSync(result.rotate);
            }
            LogUtil.log('Svg image set flip , horizontal=' + result.horizontal + ', vertical=' +result.vertical + ', rotate=' + result.rotate);
          }
        } catch (e) {
          LogUtil.error('PixelMap setTransferDetached failed:' + JSON.stringify(e))
        }
      }).catch((error: BusinessError) => {
        timeInfo.decodeEndTime = Date.now();
        imageSource.release()
        ImageKnifeLoader.makeEmptyResult(request,'getImageInfoSync failed:' + JSON.stringify(error), ImageKnifeLoader.assembleError(callBackData, LoadPhase.PHASE_CREATE_PIXEL_MAP, LoadPixelMapCode.IMAGE_DECODE_ERROR_CODE))
        return
      })

    //获取各个pixelMap的大小
    if (resPixelmap && typeof resPixelmap !== 'string') {
      let decodeImages: DecodeImageInfo[] = [];
      let decodeImage: DecodeImageInfo = {
        contentWidth: defaultSize.width,
        contentHeight: defaultSize.height,
        contentSize: (resPixelmap as PixelMap).getPixelBytesNumber()
      }
      decodeImages.push(decodeImage);
    }

    return {
      pixelMap: resPixelmap,
      bufferSize: resBuf.byteLength,
      fileKey: fileKey,
      type:typeValue,
      imageKnifeData:callBackData
    }
  }
  static async parseAnimatorImage(resBuf: ArrayBuffer, typeValue: string,
    fileKey: string,request: RequestJobRequest, callBackData: ImageKnifeData): Promise<RequestJobResult | undefined>  {
    let timeInfo: TimeInfo = ImageKnifeLoader.getTimeInfo(callBackData);
    let imageSource: image.ImageSource = image.createImageSource(resBuf)
    if (imageSource === undefined){
      ImageKnifeLoader.makeEmptyResult(request,'image.createImageSource failed', ImageKnifeLoader.assembleError(callBackData,LoadPhase.PHASE_CREATE_SOURCE,LoadPixelMapCode.IMAGE_SOURCE_ERROR_CODE))
      return
    }

    let frameCount = await imageSource.getFrameCount()
    let imageInfoSync = imageSource.getImageInfoSync()
    imageSource.release()
    if (imageInfoSync == undefined){
      ImageKnifeLoader.makeEmptyResult(request, 'getImageInfoSync failed')
      return
    }
    let size = imageInfoSync.size
    callBackData.frameCount = frameCount;
    callBackData.imageWidth = size.width;
    callBackData.imageHeight = size.height;

    if(frameCount == undefined || frameCount == 1) {
    } else {
      timeInfo.decodeStartTime = Date.now()
      let base64str = 'data:image/' + typeValue + ';base64,' + new util.Base64Helper().encodeToStringSync(new Uint8Array(resBuf))
      timeInfo.decodeEndTime = Date.now()
      return {
        pixelMap: base64str,
        bufferSize: resBuf.byteLength,
        fileKey: fileKey,
        size:size,
        type:typeValue,
        imageKnifeData:callBackData
      }
    }
    return ImageKnifeLoader.parseNormalImage(resBuf, typeValue, fileKey, request, callBackData)
  }
  // 为AnimatorComponent解析动图
  static async parseForAnimatorComponent(resBuf: ArrayBuffer, typeValue: string, fileKey: string,request: RequestJobRequest, callBackData: ImageKnifeData): Promise<RequestJobResult | undefined> {
    let timeInfo: TimeInfo = ImageKnifeLoader.getTimeInfo(callBackData);

    if (typeValue === 'gif' || typeValue === 'webp') {
      let imageSource: image.ImageSource = image.createImageSource(resBuf);
      if (imageSource === undefined){
        ImageKnifeLoader.makeEmptyResult(request,'image.createImageSource failed', ImageKnifeLoader.assembleError(callBackData, LoadPhase.PHASE_CREATE_SOURCE, LoadPixelMapCode.IMAGE_SOURCE_ERROR_CODE))
        return
      }
      let decodingOptions: image.DecodingOptions = {
        editable: request.requestSource === ImageKnifeRequestSource.SRC && request.transformation !== undefined ? true : false,
      }

      let imageInfoSync = imageSource.getImageInfoSync()
      if (imageInfoSync == undefined){
        imageSource.release()
        ImageKnifeLoader.makeEmptyResult(request, 'getImageInfoSync failed')
        return
      }
      callBackData.imageWidth = imageInfoSync.size.width;
      callBackData.imageHeight = imageInfoSync.size.height;
      let pixelMapList: Array<PixelMap> = []
      let delayList: Array<number> = []
      timeInfo.decodeStartTime = Date.now();
      let decodeImages: Array<DecodeImageInfo> = [];
      await imageSource.createPixelMapList(decodingOptions).then(async (pixelList: Array<PixelMap>) => {
        timeInfo.decodeEndTime = Date.now();
        //sdk的api接口发生变更：从.getDelayTime() 变为.getDelayTimeList()
        await imageSource.getDelayTimeList().then(delayTimes => {
          if (pixelList.length > 0) {
            for (let i = 0; i < pixelList.length; i++) {
              pixelMapList.push(pixelList[i]);
              if (i < delayTimes.length) {
                delayList.push(delayTimes[i]);
              } else {
                delayList.push(delayTimes[delayTimes.length - 1])
              }
              //获取各个pixelMap的大小
              let size = pixelList[i].getImageInfoSync().size
              let decodeImage: DecodeImageInfo = {
                contentWidth: size.width,
                contentHeight: size.height,
                contentSize: pixelList[i].getPixelBytesNumber()
              }
              decodeImages.push(decodeImage);
            }
            imageSource.release();
          }
        })
      }).catch((error: BusinessError) => {
        imageSource.release()
        timeInfo.decodeEndTime = Date.now();
        ImageKnifeLoader.makeEmptyResult(request,'createPixelMapList failed:' + JSON.stringify(error),
          ImageKnifeLoader.assembleError(callBackData,LoadPhase.PHASE_CREATE_PIXEL_MAP,LoadPixelMapCode.IMAGE_DECODE_ERROR_CODE))
        return
      })
      callBackData.decodeImages = decodeImages;
      return {
        pixelMap: '',
        bufferSize: resBuf.byteLength,
        fileKey: fileKey,
        type: typeValue,
        imageKnifeData:callBackData,
        pixelMapList,
        delayList
      }
    } else {
      ImageKnifeLoader.makeEmptyResult(request,'ImageKnifeAnimatorComponent not support format', ImageKnifeLoader.assembleError(callBackData,LoadPhase.PHASE_PARSE_IAMGE,LoadPixelMapCode.IMAGE_FORMAT_ERROR_CODE))
      return
    }
  }
  static getHeaderObj(request:RequestJobRequest){
    let  headerObj: Record<string, Object> | undefined = {}
    if (request.headers != undefined && headerObj !== undefined) {
      request.headers.forEach((value) => {
        headerObj![value.key] = value.value
      })
    } else if (request.allHeaders.size > 0 && headerObj !== undefined) {
      request.allHeaders.forEach((value, key) => {
        headerObj![key] = value
      })
    } else {
      headerObj = undefined
    }
    return headerObj
  }

  // 获取图片资源
  static async getImageArrayBuffer(request: RequestJobRequest, requestList: List<ImageKnifeRequestWithSource> | undefined,fileKey:string) {
    let resBuf: ArrayBuffer | undefined
    let loadError: string = ''
    //定义图片各个阶段错误信息
    let error: ErrorInfo = { code: 0, phase: LoadPhase.PHASE_LOAD }
    //定义加载时间点
    let callBackTimeInfo: TimeInfo = {};
    //定义加载信息回调数据
    let callBackData: ImageKnifeData = {
      source: '',
      imageWidth: 0,
      imageHeight: 0,
      timeInfo: callBackTimeInfo,
      errorInfo: error
    };

    const loaderStrategy = ImageLoaderFactory.getLoaderStrategy(request);
    if (loaderStrategy) {
      await loaderStrategy.loadImage(request, requestList, fileKey, callBackData, callBackTimeInfo);
    } else {
      loadError = `Unsupported request type: ${request.src}`;
      callBackTimeInfo.requestEndTime = Date.now();
      ImageKnifeLoader.makeEmptyResult(request, loadError, callBackData);
    }
  }
  static isLocalLoadSrc(context: Object | undefined, loadSrc: string): boolean {
    if (context != undefined) {
      let fileDir: string = (context as common.UIAbilityContext).filesDir as string;
      let cacheDir: string = (context as common.UIAbilityContext).cacheDir as string
      if (loadSrc.startsWith(fileDir) || loadSrc.startsWith(cacheDir)) {
        return true;
      }
    }
    return false;
  }
  static getDownsamplerDecodingOptions(typeValue: string, request: RequestJobRequest, size: Size,
    SRC?: ImageKnifeRequestSource):image.DecodingOptions {
    let reqSize =
      new Downsampler().calculateScaling(typeValue, size.width, size.height,
        vp2px(request.targetWidth), vp2px(request.targetHeight), request.downsampType)
    if (typeValue == 'svg') {
      return {
        editable: true,
        desiredSize: {
          height: vp2px(reqSize.height),
          width: vp2px(reqSize.width)
        }

      }
    } else {
      return {
        editable: request.requestSource === SRC && request.transformation !== undefined ? true : false,
        desiredSize:{
          width: reqSize.width,
          height: reqSize.height
        }
      }
    }
  }

  static getOrientation(orientation: string | undefined){
    let horizontal: boolean = false;
    let vertical: boolean = false;
    let rotate: number= 0;
    switch (orientation){
      case 'Top-left': break
      case 'Top-right':
        horizontal = true;
        break;
      case 'Bottom-left':
        vertical = true;
        break
      case 'Bottom-right':
        rotate = 180;
        break;
      case 'Left-top':
        horizontal = true;
        rotate = 270;
        break
      case 'Right-top':
        rotate = 90;
        break;
      case 'Left-bottom':
        rotate = 270;
        break
      case 'Right-bottom':
        horizontal = true;
        rotate = 90;
        break;
    }

    let data: FlipRotate = { horizontal: horizontal, vertical: vertical, rotate:rotate };
    return data
  }
}