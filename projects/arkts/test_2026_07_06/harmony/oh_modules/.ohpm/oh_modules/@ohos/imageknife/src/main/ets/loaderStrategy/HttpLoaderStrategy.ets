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
import { FileCache } from '../cache/FileCache';
import { IImageLoaderStrategy } from './IImageLoaderStrategy';
import {
  ImageKnifeData,
  ImageKnifeRequestSource,
  ImageKnifeRequestWithSource,
  RequestJobRequest,
  TimeInfo
} from '../model/ImageKnifeData';
import http from '@ohos.net.http';
import { ImageKnifeLoader } from '../ImageKnifeLoader';
import { combineArrayBuffers } from '../utils/ArrayBufferUtils';
import { BusinessError, emitter } from '@kit.BasicServicesKit';
import { Constants, LoadPhase, LoadPixelMapCode } from '../utils/Constants';
import { LogUtil } from '../utils/LogUtil';
import List from '@ohos.util.List';
import { taskpool } from '@kit.ArkTS';
import { hiTraceMeter } from '@kit.PerformanceAnalysisKit';

class RequestData {
  public receiveSize: number = 2000
  public totalSize: number = 2000
}

// HTTP加载策略
export class HttpLoaderStrategy implements IImageLoaderStrategy {
  async loadImage(
    request: RequestJobRequest,
    requestList: List<ImageKnifeRequestWithSource> | undefined,
    fileKey: string,
    callBackData: ImageKnifeData,
    callBackTimeInfo: TimeInfo
  ): Promise<void> {
    let resBuf: ArrayBuffer | undefined;
    let loadError: string = '';

    // 从文件缓存获取
    ImageKnifeLoader.assembleError(callBackData, LoadPhase.PHASE_NET);
    callBackTimeInfo.diskCheckStartTime = Date.now();
    hiTraceMeter.startTrace('getFileCache',request.componentId)
    resBuf = FileCache.getFileCacheByFile(request.context, fileKey, request.fileCacheFolder);
    hiTraceMeter.finishTrace('getFileCache',request.componentId)
    callBackTimeInfo.diskCheckEndTime = Date.now();

    if (resBuf !== undefined) {
      LogUtil.log(`success get image from filecache for key = ${fileKey} src = ${request.componentId},
        srcType:${request.requestSource}, ${request.componentVersion}`);
      ImageKnifeLoader.parseFile(resBuf, fileKey, request, callBackData);
    } else if (request.onlyRetrieveFromCache !== true) {
      LogUtil.log(`HttpDownloadClient.start: ${request.componentId}, srcType:${request.requestSource},
        ${request.componentVersion}`);
      callBackTimeInfo.netRequestStartTime = Date.now();
      if (taskpool.Task.isCanceled()) {
        return
      }
      const httpRequest = http.createHttp();
      emitter.once((request.src as string) + request.componentId,()=>{
        httpRequest.destroy()
      })
      let progress: number = 0;
      let arrayBuffers: ArrayBuffer[] = [];
      const headerObj = ImageKnifeLoader.getHeaderObj(request);

      httpRequest.on('dataReceive', (data: ArrayBuffer) => {
        arrayBuffers.push(data);
      });

      if (request.isWatchProgress) {
        httpRequest.on('dataReceiveProgress', (data: RequestData) => {
          if (data != undefined && typeof data.receiveSize === 'number' && typeof data.totalSize === 'number') {
            const percent = Math.round(((data.receiveSize * 1.0) / (data.totalSize * 1.0)) * 100);
            if (progress !== percent) {
              progress = percent;
              if (requestList === undefined) {
                // 子线程
                emitter.emit(Constants.PROGRESS_EMITTER + request.memoryKey, { data: { 'value': progress } });
              } else {
                // 主线程请求
                requestList.forEach((requestWithSource: ImageKnifeRequestWithSource) => {
                  if (requestWithSource.request.imageKnifeOption.progressListener !== undefined &&
                    requestWithSource.source === ImageKnifeRequestSource.SRC) {
                    requestWithSource.request.imageKnifeOption.progressListener(progress);
                  }
                });
              }
            }
          }
        });
      }
      hiTraceMeter.startTrace('loadHttp',request.componentId)
      let promise = httpRequest.requestInStream(request.src as string, {
        header: headerObj,
        method: http.RequestMethod.GET,
        expectDataType: http.HttpDataType.ARRAY_BUFFER,
        connectTimeout: request.connectTimeout ?? 60000,
        readTimeout: request.readTimeout ?? 30000,
        caPath: request.caPath
      });
      promise.then((data: number) => {
        emitter.off((request.src as string) + request.componentId)
        httpRequest.destroy()
        httpRequest.off('dataReceive')
        httpRequest.off('dataReceiveProgress')
        callBackData.httpCode = data;
        ImageKnifeLoader.assembleError(callBackData,LoadPhase.PHASE_NET, undefined);
        callBackTimeInfo.netRequestEndTime = Date.now();
        if (data == 200 || data == 206 || data == 204) {
          hiTraceMeter.finishTrace('loadHttp',request.componentId)
          resBuf = combineArrayBuffers(arrayBuffers);
          arrayBuffers = []
          ImageKnifeLoader.parseFile(resBuf, fileKey, request, callBackData,true,headerObj);
        } else {
          arrayBuffers = []
          loadError = 'HttpDownloadClient has error, http code =' + JSON.stringify(data);
          ImageKnifeLoader.makeEmptyResult(request,loadError, ImageKnifeLoader.assembleError(callBackData,
            LoadPhase.PHASE_NET, LoadPixelMapCode.IMAGE_HTTPS_LOAD_FAILED_CODE));
        }
      }).catch((err: BusinessError) => {
        emitter.off((request.src as string) + request.componentId)
        httpRequest.destroy()
        httpRequest.off('dataReceive')
        httpRequest.off('dataReceiveProgress')
        arrayBuffers = []
        callBackData.httpCode = err.code;
        loadError = 'HttpDownloadClient download ERROR : err = ' + JSON.stringify(err);
        callBackTimeInfo.netRequestEndTime = Date.now();
        ImageKnifeLoader.makeEmptyResult(request,loadError, ImageKnifeLoader.assembleError(callBackData,
          LoadPhase.PHASE_NET, LoadPixelMapCode.IMAGE_HTTPS_LOAD_FAILED_CODE));
      });
      LogUtil.log('HttpDownloadClient.end:' + request.componentId + ',srcType:' +
        request.requestSource + ',' + request.componentVersion);
      return;
    } else {
      callBackTimeInfo.netRequestEndTime = Date.now();
      loadError = `onlyRetrieveFromCache, do not fetch image src = ${request.src}`;
      ImageKnifeLoader.makeEmptyResult(request, loadError, callBackData);
      return;
    }
  }
}
