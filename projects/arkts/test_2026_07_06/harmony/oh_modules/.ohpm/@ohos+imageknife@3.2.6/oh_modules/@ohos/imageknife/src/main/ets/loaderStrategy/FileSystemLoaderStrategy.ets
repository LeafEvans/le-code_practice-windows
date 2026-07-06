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
import { ImageKnifeData, RequestJobRequest, TimeInfo, ImageKnifeRequestWithSource } from '../model/ImageKnifeData';
import fs from '@ohos.file.fs';
import { IImageLoaderStrategy } from './IImageLoaderStrategy';
import List from '@ohos.util.List';
import { ImageKnifeLoader } from '../ImageKnifeLoader';
import { LoadPhase, LoadPixelMapCode } from '../utils/Constants';
import { BusinessError } from '@kit.BasicServicesKit';
import { taskpool } from '@kit.ArkTS';

export class FileSystemLoaderStrategy implements IImageLoaderStrategy {
  async loadImage(request: RequestJobRequest, requestList: List<ImageKnifeRequestWithSource> | undefined,
    fileKey: string, callBackData: ImageKnifeData, callBackTimeInfo: TimeInfo
  ): Promise<void> {
    let resBuf: ArrayBuffer | undefined;
    let loadError: string = '';

    if (typeof request.src === 'string' &&
      (request.src.startsWith('datashare://') || request.src.startsWith('file://'))) {
      if (taskpool.Task.isCanceled()) {
        return
      }
      ImageKnifeLoader.assembleError(callBackData, LoadPhase.PHASE_SHARE_FILE);
      await fs.open(request.src, fs.OpenMode.READ_ONLY).then(async (file) => {
        await fs.stat(file.fd).then(async (stat) => {
          let buf = new ArrayBuffer(stat.size);
          await fs.read(file.fd, buf).then((readLen) => {
            resBuf = buf;
            fs.closeSync(file.fd);
          }).catch((err: BusinessError) => {
            ImageKnifeLoader.assembleError(callBackData, LoadPhase.PHASE_SHARE_FILE,
              LoadPixelMapCode.IMAGE_LOAD_SHARE_FILE_FAILED_CODE)
            loadError = 'LoadDataShareFileClient fs.read err happened uri=' + request.src + ' err.msg=' + err?.message +
              ' err.code=' + err?.code
          })
        }).catch((err: BusinessError) => {
          ImageKnifeLoader.assembleError(callBackData, LoadPhase.PHASE_SHARE_FILE,
            LoadPixelMapCode.IMAGE_LOAD_SHARE_FILE_FAILED_CODE)
          loadError = 'LoadDataShareFileClient fs.stat err happened uri=' + request.src + ' err.msg=' + err?.message +
            ' err.code=' + err?.code
        })
      }).catch((err: BusinessError) => {
        ImageKnifeLoader.assembleError(callBackData, LoadPhase.PHASE_SHARE_FILE,
          LoadPixelMapCode.IMAGE_LOAD_SHARE_FILE_FAILED_CODE)
        loadError = 'LoadDataShareFileClient fs.open err happened uri=' + request.src + ' err.msg=' + err?.message +
          ' err.code=' + err?.code
      })
    }
    if (resBuf === undefined || resBuf === null) {
      callBackTimeInfo.requestEndTime = Date.now();
      ImageKnifeLoader.makeEmptyResult(request, loadError, callBackData);
    } else {
      ImageKnifeLoader.parseFile(resBuf, fileKey, request, callBackData);
    }
    return;
  }
}