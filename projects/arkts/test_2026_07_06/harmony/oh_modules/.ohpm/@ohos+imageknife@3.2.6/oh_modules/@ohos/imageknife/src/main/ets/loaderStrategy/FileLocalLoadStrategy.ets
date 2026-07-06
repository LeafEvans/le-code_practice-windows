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
import { RequestJobRequest, ImageKnifeRequestWithSource, ImageKnifeData, TimeInfo } from '../model/ImageKnifeData';
import { IImageLoaderStrategy } from './IImageLoaderStrategy';
import List from '@ohos.util.List';
import { ImageKnifeLoader } from '../ImageKnifeLoader';
import { LoadPhase, LoadPixelMapCode } from '../utils/Constants';
import fs from '@ohos.file.fs';

export class FileLocalLoadStrategy implements IImageLoaderStrategy {
  loadImage(request: RequestJobRequest, requestList: List<ImageKnifeRequestWithSource> | undefined, fileKey: string,
    callBackData: ImageKnifeData, callBackTimeInfo: TimeInfo): Promise<void> {
    let resBuf: ArrayBuffer | undefined;
    let loadError: string = '';
    if (typeof request.src === 'string' && ImageKnifeLoader.isLocalLoadSrc(request.context, request.src)) {
      ImageKnifeLoader.assembleError(callBackData, LoadPhase.PHASE_LOCAL_FILE);
      try {
        const stat = fs.statSync(request.src);
        if (stat.size > 0) {
          const file = fs.openSync(request.src, fs.OpenMode.READ_ONLY);
          resBuf = new ArrayBuffer(stat.size);
          fs.readSync(file.fd, resBuf);
          fs.closeSync(file);
        }
      } catch (err) {
        ImageKnifeLoader.assembleError(callBackData, LoadPhase.PHASE_LOCAL_FILE,
          LoadPixelMapCode.IMAGE_LOAD_LOCAL_FILE_FAILED_CODE);
        loadError = `LocalLoadSrc: ${request.src}, err: ${err}`;
        ImageKnifeLoader.makeEmptyResult(request, loadError,
          ImageKnifeLoader.assembleError(
            callBackData,
            LoadPhase.PHASE_LOCAL_FILE,
            LoadPixelMapCode.IMAGE_LOAD_LOCAL_FILE_FAILED_CODE
          )
        );
      }
    } else {
      loadError = `Parameter not supported: ${request.src}`;
      ImageKnifeLoader.makeEmptyResult(request, loadError, callBackData);
    }

    if (resBuf === undefined || resBuf === null) {
      callBackTimeInfo.requestEndTime = Date.now();
      ImageKnifeLoader.makeEmptyResult(request, loadError, callBackData);
    } else {
      ImageKnifeLoader.parseFile(resBuf, fileKey, request, callBackData);
    }
    return Promise.resolve();
  }
}