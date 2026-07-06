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
// 加载策略工厂
import { CustomLoaderStrategy } from './CustomLoaderStrategy';
import { FileSystemLoaderStrategy } from './FileSystemLoaderStrategy';
import { HttpLoaderStrategy } from './HttpLoaderStrategy';
import { IImageLoaderStrategy } from './IImageLoaderStrategy';
import { ImageKnifeRequestSource, RequestJobRequest } from '../model/ImageKnifeData';
import { ResourceLoaderStrategy } from './ResourceLoaderStrategy';
import { FileLocalLoadStrategy } from './FileLocalLoadStrategy';
import { ImageKnifeLoader } from '../ImageKnifeLoader';

export class ImageLoaderFactory {
  static getLoaderStrategy(request: RequestJobRequest): IImageLoaderStrategy | null {
    if (typeof request.src === 'string') {
      if (request.src.startsWith('datashare://') || request.src.startsWith('file://')) {
        return new FileSystemLoaderStrategy();
      } else if(ImageKnifeLoader.isLocalLoadSrc(request.context, request.src)) {
        return new FileLocalLoadStrategy();
      } else if(request.customGetImage !== undefined &&
        request.requestSource === ImageKnifeRequestSource.SRC) {
        return new CustomLoaderStrategy();
      } else {
        return new HttpLoaderStrategy();
      }
    } else if (typeof request.src === 'number') {
      return new ResourceLoaderStrategy();
    }
    return null;
  }
}