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
import { ImageKnifeLoader } from '../ImageKnifeLoader';
import { ImageKnifeData, ImageKnifeRequestWithSource, RequestJobRequest, TimeInfo } from '../model/ImageKnifeData';
import { LoadPhase, LoadPixelMapCode } from '../utils/Constants';
import { LogUtil } from '../utils/LogUtil';
import List from '@ohos.util.List';
import { taskpool } from '@kit.ArkTS';

// 自定义加载策略
export class CustomLoaderStrategy implements IImageLoaderStrategy {
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
    ImageKnifeLoader.assembleError(callBackData, LoadPhase.PHASE_CUSTOM_LOAD);
    callBackTimeInfo.diskCheckStartTime = Date.now();
    resBuf = FileCache.getFileCacheByFile(request.context, fileKey, request.fileCacheFolder);
    callBackTimeInfo.diskCheckEndTime = Date.now();

    if (resBuf !== undefined) {
      ImageKnifeLoader.parseFile(resBuf, fileKey, request, callBackData);
    } else if (!request.onlyRetrieveFromCache) {
      LogUtil.log('start customGetImage src=' + request.componentId + ',srcType:' + request.requestSource + ',' +
      request.componentVersion);
      if (taskpool.Task.isCanceled()) {
        return
      }
      const headerObj = ImageKnifeLoader.getHeaderObj(request);
      try {
        request.customGetImage!(request.context, request.src as string, headerObj)
          .then((buffer)=>{
            if(buffer !== undefined && buffer !== null) {
              ImageKnifeLoader.parseFile(buffer, fileKey, request, callBackData,true,headerObj);
            } else {
              loadError = 'customGetImage loadFail undefined';
              ImageKnifeLoader.makeEmptyResult(request,loadError, ImageKnifeLoader.assembleError(callBackData,
                LoadPhase.PHASE_CUSTOM_LOAD, LoadPixelMapCode.IMAGE_CUSTOM_LOAD_FAILED_CODE));
            }
          }).catch((err:string)=>{
          ImageKnifeLoader.makeEmptyResult(request,err, ImageKnifeLoader.assembleError(callBackData,
            LoadPhase.PHASE_CUSTOM_LOAD, LoadPixelMapCode.IMAGE_CUSTOM_LOAD_FAILED_CODE));
        })
      } catch (e) {
        loadError = 'customGetImage loadFail failed';
        ImageKnifeLoader.makeEmptyResult(request,loadError + e, ImageKnifeLoader.assembleError(callBackData,
          LoadPhase.PHASE_CUSTOM_LOAD, LoadPixelMapCode.IMAGE_CUSTOM_LOAD_FAILED_CODE));
      }
      LogUtil.log('end customGetImage src=' + request.componentId + ',srcType:' +
        request.requestSource + ',' + request.componentVersion);
      return;
    } else {
      loadError = `onlyRetrieveFromCache, do not fetch image src = ${request.src}`;
      ImageKnifeLoader.makeEmptyResult(request, loadError, callBackData);
    }
    return;
  }
}