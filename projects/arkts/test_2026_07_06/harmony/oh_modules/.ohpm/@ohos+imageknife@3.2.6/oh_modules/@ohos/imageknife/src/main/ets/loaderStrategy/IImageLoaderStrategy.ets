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
import { ImageKnifeData, ImageKnifeRequestWithSource, RequestJobRequest, TimeInfo } from '../model/ImageKnifeData';
import List from '@ohos.util.List';

// 定义图片加载策略接口
export interface IImageLoaderStrategy {
  loadImage(
    request: RequestJobRequest,
    requestList: List<ImageKnifeRequestWithSource> | undefined,
    fileKey: string,
    callBackData: ImageKnifeData,
    callBackTimeInfo: TimeInfo
  ): Promise<void>;
}