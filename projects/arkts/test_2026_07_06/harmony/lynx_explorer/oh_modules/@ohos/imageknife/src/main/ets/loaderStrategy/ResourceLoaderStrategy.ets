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
// 资源文件加载策略
import { IImageLoaderStrategy } from './IImageLoaderStrategy';
import {
  ImageKnifeData,
  ImageKnifeRequestSource,
  ImageKnifeRequestWithSource,
  RequestJobRequest,
  TimeInfo
} from '../model/ImageKnifeData';
import List from '@ohos.util.List';
import { application } from '@kit.AbilityKit';
import { ImageKnifeLoader } from '../ImageKnifeLoader';
import { taskpool } from '@kit.ArkTS';

export class ResourceLoaderStrategy implements IImageLoaderStrategy {
  async loadImage(
    request: RequestJobRequest,
    requestList: List<ImageKnifeRequestWithSource> | undefined,
    fileKey: string,
    callBackData: ImageKnifeData,
    callBackTimeInfo: TimeInfo
  ): Promise<void> {
    let resBuf: ArrayBuffer | undefined;
    let loadError: string = '';
    if (taskpool.Task.isCanceled()) {
      return
    }
    if (typeof request.src === 'number') {
      const moduleContext = await application.createModuleContext(request.context, request.moduleName);
      const manager = moduleContext.resourceManager;
      if ((resBuf == undefined && request.onlyRetrieveFromCache !== true &&
        request.requestSource === ImageKnifeRequestSource.SRC) ||
        (resBuf == undefined && request.requestSource !== ImageKnifeRequestSource.SRC)) {
        if (request.src === -1) {
          const resName = request.resName as string;
          resBuf =
            (await manager.getMediaByName(resName.substring(resName.lastIndexOf('.') + 1))).buffer as ArrayBuffer;
        } else {
          resBuf = request.resName ?
          manager.getRawFileContentSync(request.resName).buffer.slice(0) :
            (manager.getMediaContentSync(request.src)).buffer as ArrayBuffer;
        }
      }
    }
    if (resBuf === undefined || resBuf === null){
      callBackTimeInfo.requestEndTime = Date.now();
      loadError = 'Resource load error';
      ImageKnifeLoader.makeEmptyResult(request, loadError ,callBackData);
    } else {
      ImageKnifeLoader.parseFile(resBuf,fileKey,request, callBackData);
    }
    return;
  }
}