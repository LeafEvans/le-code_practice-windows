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
import { ImageKnifeData } from '../model/ImageKnifeData';
import util from '@ohos.util';
import { IMemoryCache } from './IMemoryCache';

export class MemoryLruCache implements IMemoryCache {
  maxMemory: number = 0
  currentMemory: number = 0
  maxSize: number = 0
  private lruCache: util.LRUCache<string, ImageKnifeData>
  readonly defaultMaxSize: number = 65536;
  readonly defaultSize: number = 512;
  readonly defaultMaxMemorySize: number = 10 * 1024 * 1024 * 1024;
  readonly defaultMemorySize: number = 1024 * 1024 * 1024;

  constructor(size: number, memory: number) {
    if (size <= 0 || size > this.defaultMaxSize) {
      size = this.defaultSize;
    }
    if (memory <= 0 || memory > this.defaultMaxMemorySize) {
      memory = this.defaultMemorySize;
    }

    this.lruCache = new util.LRUCache(size);
    this.maxMemory = memory;
    this.maxSize = size;
    this.currentMemory = 0;
  }

  // 添加缓存键值对
  put(key: string, value: ImageKnifeData): void {
    if (key == null || value == null) {
      throw new Error('key or value is invalid ');
    }

    let size = this.getImageKnifeDataSize(value)
    if (size <= 0 || size >= this.maxMemory) {
      return
    }

    // 如果size满了的话，需要按照LRU的方式删除第一个
    if (this.lruCache.length == this.maxSize && !this.lruCache.contains(key)) {
      this.remove(this.lruCache.keys()[0])
    } else if (this.lruCache.contains(key)) {
      this.remove(key)
    }

    this.lruCache.put(key, value)
    this.currentMemory += size
    this.trimToSize()
  }

  get(key: string): ImageKnifeData | undefined {
    return this.lruCache.get(key)
  }

  // 移除键为key的缓存
  remove(key: string): ImageKnifeData | undefined {
    if (key == null) {
      throw new Error('key is null,checking the parameter');
    }

    let remove: ImageKnifeData | undefined = this.lruCache.remove(key)
    if (remove !== undefined) {
      this.removeMemorySize(remove)
    }
    return remove
  }

  removeAll(): void {
    this.lruCache.clear()
    this.currentMemory = 0;
  }

  size(): number {
    return this.lruCache.length
  }

  // 移除较少使用的缓存数据
  trimToSize(): void {
    while (true) {
      if (this.currentMemory <= this.maxMemory || this.lruCache.isEmpty()) {
        break
      }
      let delkey = this.lruCache.keys()[0]
      let data: ImageKnifeData | undefined = this.lruCache.get(delkey)
      if (data != undefined) {
        this.removeMemorySize(data)
      }
      this.lruCache.remove(delkey)
    }
  }

  private removeMemorySize(value: ImageKnifeData): void {
    if (value.source != undefined) {
      if (typeof value.source === 'string' && value.source != '') {
        this.currentMemory -= value.source.length
      } else if (value.source == '') {
        for (let index = 0;index < value.imageAnimator!.length;index++) {
          let pixelMap = value.imageAnimator![index].src as PixelMap
          this.currentMemory -= pixelMap.getPixelBytesNumber()
        }
      } else {
        this.currentMemory -= value.source.getPixelBytesNumber();
        // value.source.release()
      }
    }
  }

  private getImageKnifeDataSize(value: ImageKnifeData): number {
    if (value.source != undefined) {
      if (typeof value.source === 'string' && value.source != '') {
        return value.source.length
      } else if (value.source == '') {
        let size: number = 0
        for (let index = 0; index < value.imageAnimator!.length; index++) {
          let pixelMap = value.imageAnimator![index].src as PixelMap
          size += pixelMap.getPixelBytesNumber()
        }
        return size
      } else {
        return value.source.getPixelBytesNumber();
      }
    }
    return 0
  }
}