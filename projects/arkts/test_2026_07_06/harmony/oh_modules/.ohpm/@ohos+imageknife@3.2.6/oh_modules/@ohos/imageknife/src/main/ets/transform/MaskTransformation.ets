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
import { PixelMapTransformation } from './PixelMapTransformation';
import { Size } from '@kit.ArkUI';
import { image } from '@kit.ImageKit';
import { resourceManager } from '@kit.LocalizationKit';
import { CalculatePixelUtils } from '../utils/CalculatePixelUtils';
import { ColorUtils } from '../utils/ColorUtils';
import { PixelEntry } from './entry/PixelEntry';

/**
 * 图片变换：遮罩效果
 */
@Sendable
export class MaskTransformation extends PixelMapTransformation {
  private mResourceId: number;
  private mResourceModuleName: string;

  constructor(resource: Resource) {
    super();
    this.mResourceId = resource.id;
    this.mResourceModuleName = resource.moduleName;
  }

  getName(): string {
    return this.constructor.name + ';resourceId:' + this.mResourceId + ';resourceModuleName:' + this.mResourceModuleName;
  }

  async transform(context: Context, toTransform: PixelMap, width: number, height: number): Promise<PixelMap> {
    let imageInfo = await toTransform.getImageInfo();
    let size: Size = {
      width: imageInfo.size.width,
      height: imageInfo.size.height
    };
    if (!size) {
      console.error('MaskTransformation The image size does not exist.');
      return toTransform;
    }
    let pixelMapWidth: number = size.width;
    let pixelMapHeight: number = size.height;
    let targetWidth: number = width;
    let targetHeight: number = height;
    if (pixelMapWidth > targetWidth && pixelMapHeight > targetHeight) {
      let scale = Math.max(targetWidth / pixelMapWidth, targetHeight / pixelMapHeight);
      await toTransform.scale(scale, scale);
      return await this.openInternal(context, toTransform, scale * pixelMapWidth, scale * pixelMapHeight);
    }
    return await this.openInternal(context, toTransform, size.width, size.height);
  }

  private async openInternal(context: Context, bitmap: PixelMap, width: number, height: number): Promise<PixelMap> {
    if (context == undefined) {
      console.error('MaskTransformation openInternal the context is undefined.');
      return bitmap;
    }
    let moduleContext = context.createModuleContext(this.mResourceModuleName);
    if (moduleContext == undefined) {
      console.error('MaskTransformation openInternal the moduleContext is undefined.');
      return bitmap;
    }
    let resourceManager = moduleContext.resourceManager as resourceManager.ResourceManager;
    if (resourceManager == undefined) {
      console.error('MaskTransformation openInternal the resourceManager is undefined.');
      return bitmap;
    }
    let array: Uint8Array = await resourceManager.getMediaContent(this.mResourceId);
    let buffer = array.buffer.slice(array.byteOffset, array.byteLength + array.byteOffset);
    let imageSource: image.ImageSource = image.createImageSource(buffer);
    let options: image.DecodingOptions = {
      editable: true,
      desiredSize: {
        width: width,
        height: height
      }
    };
    let maskBitmap: PixelMap = await imageSource.createPixelMap(options);
    imageSource.release()
    return await this.mask(bitmap, maskBitmap);
  }

  async mask(bitmap: PixelMap, maskBitmap: PixelMap): Promise<PixelMap> {
    let imageInfo = await bitmap.getImageInfo();
    let size: Size = {
      width: imageInfo.size.width,
      height: imageInfo.size.height
    };
    if (!size) {
      console.error('MaskTransformation mask the image size does not exist.');
      return bitmap;
    }
    let width = size.width;
    let height = size.height;
    let rgbData = CalculatePixelUtils.createInt2DArray(height, width);
    let bufferData = new ArrayBuffer(bitmap.getPixelBytesNumber());
    await bitmap.readPixelsToBuffer(bufferData);
    let dataArray = new Uint8Array(bufferData);
    let ph = 0;
    let pw = 0;
    for (let index = 0; index < dataArray.length; index += 4) {
      const r = dataArray[index];
      const g = dataArray[index+1];
      const b = dataArray[index+2];
      const f = dataArray[index+3];
      let entry = new PixelEntry();
      entry.a = 0;
      entry.b = b;
      entry.g = g;
      entry.r = r;
      entry.f = f;
      entry.pixel = ColorUtils.rgb(entry.r, entry.g, entry.b);
      rgbData[ph][pw] = ColorUtils.rgb(entry.r, entry.g, entry.b);
      if (pw == width - 1) {
        pw = 0;
        ph++;
      } else {
        pw++;
      }
    }
    let imageInfoMask = await maskBitmap.getImageInfo();
    let sizeMask: Size = {
      width: imageInfoMask.size.width,
      height: imageInfoMask.size.height
    };
    if (!sizeMask) {
      console.error('MaskTransformation mask the sizeMask size does not exist.');
      return bitmap;
    }
    let widthMask = sizeMask.width;
    let heightMask = sizeMask.height;
    let rgbDataMask = CalculatePixelUtils.createInt2DArray(heightMask, widthMask);
    let pixEntry: Array<PixelEntry> = new Array();
    let bufferDataM = new ArrayBuffer(maskBitmap.getPixelBytesNumber());
    await maskBitmap.readPixelsToBuffer(bufferDataM);
    let dataArrayM = new Uint8Array(bufferDataM);
    let phM = 0;
    let pwM = 0;
    for (let index = 0; index < dataArrayM.length; index += 4) {
      const r = dataArrayM[index];
      const g = dataArrayM[index+1];
      const b = dataArrayM[index+2];
      const f = dataArrayM[index+3];
      let entry = new PixelEntry();
      entry.a = 0;
      entry.b = b;
      entry.g = g;
      entry.r = r;
      entry.f = f;
      entry.pixel = ColorUtils.rgb(entry.r, entry.g, entry.b);
      pixEntry.push(entry);
      if (entry.r == 0 && entry.g == 0 && entry.b == 0) {
        rgbDataMask[phM][pwM] = rgbData[phM][pwM];
      } else {
        rgbDataMask[phM][pwM] = ColorUtils.rgb(entry.r, entry.g, entry.b);
      }
      if (pwM == widthMask - 1) {
        pwM = 0;
        phM++;
      } else {
        pwM++;
      }
    }
    let bufferNewData = new ArrayBuffer(maskBitmap.getPixelBytesNumber());
    let dataNewArray = new Uint8Array(bufferNewData);
    let index = 0;
    let mh = 0;
    let nw = 0;
    for (let i = 0; i < dataNewArray.length; i += 4) {
      let pixel1 = rgbDataMask[mh][nw];
      if (nw == widthMask - 1) {
        nw = 0;
        mh++;
      } else {
        nw++;
      }
      let pR = ColorUtils.red(pixel1);
      let pG = ColorUtils.green(pixel1);
      let pB = ColorUtils.blue(pixel1);
      dataNewArray[i] = pR;
      dataNewArray[i+1] = pG;
      dataNewArray[i+2] = pB;
      dataNewArray[i+3] = pixEntry[index].f;
      index++;
    }
    await maskBitmap.writeBufferToPixels(bufferNewData);
    return maskBitmap;
  }
}