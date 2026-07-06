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
import util from '@ohos.util';
import { FileUtils } from '../utils/FileUtils';
import fs from '@ohos.file.fs';
import { LogUtil } from '../utils/LogUtil';

const INT_MAX = 2147483647
/**
 * 二级文件缓存
 * 主线程通过lruCache管理缓存大小
 * 子线程直接读写文件
 */
export class FileCache {
  static CACHE_FOLDER: string = 'ImageKnife' // context cacheDir 的缓存文件目录
  maxMemory: number = 0
  currentMemory: number = 0
  maxSize: number = 0
  path: string = ''
  private lruCache: util.LRUCache<string, number>
  private isInited: boolean = false
  private context?: Context
  readonly defaultMaxMemorySize: number = 10 * 1024 * 1024 * 1024;
  readonly defaultMemorySize: number = 1024 * 1024 * 1024;

  constructor(context: Context, size: number, memory: number) {
    if (size <= 0 || size > INT_MAX) {
      size = INT_MAX;
    }
    if (memory <= 0 || memory > this.defaultMaxMemorySize) {
      memory = this.defaultMemorySize;
    }
    this.lruCache = new util.LRUCache(size);
    this.maxMemory = memory;
    this.currentMemory = 0;
    this.maxSize = size;
    this.context = context;
  }

  /**
   * 遍历缓存文件目录，初始化缓存
   */
  public async initFileCache(path: string = FileCache.CACHE_FOLDER) {
    if (this.isInited) {
      return
    }
    let startTime = Date.now()
    if (this.context && path.startsWith(this.context.cacheDir) === true) {
      this.path = path
    } else {
      FileCache.CACHE_FOLDER = path
      this.path = this.context?.cacheDir + FileUtils.SEPARATOR + FileCache.CACHE_FOLDER + FileUtils.SEPARATOR
    }
    await FileUtils.getInstance().createFolder(this.path)
    // 遍历缓存目录下的文件，按照时间顺序加入缓存
    let filenames: string[] = await FileUtils.getInstance().ListFile(this.path)

    interface CacheFileInfo {
      file: string;
      ctime: number;
      size: number;
    }

    // 按照上次访问该文件的时间排序
    let cachefiles: CacheFileInfo[] = []
    for (let i = 0; i < filenames.length; i++) {
      let stat: fs.Stat | undefined = await FileUtils.getInstance().Stat(this.path + filenames[i])
      cachefiles.push({
        file: filenames[i],
        ctime: stat === undefined ? 0 : stat.ctime,
        size: stat?.size ?? 0
      })
    }
    let sortedCachefiles: CacheFileInfo[] = cachefiles.sort((a, b) => a.ctime - b.ctime)

    for (let i = 0; i < sortedCachefiles.length; i++) {
      const fileSize: number = sortedCachefiles[i].size;
      // 处理数量超过size的场景，移除即将排除的文件
      if (this.lruCache.length == this.maxSize && !this.lruCache.contains(sortedCachefiles[i].file)) {
        let remove: number | undefined = this.lruCache.remove(this.lruCache.keys()[0])
        if (remove !== undefined) {
          FileUtils.getInstance().deleteFile(this.path + this.lruCache.keys()[0])
          this.removeMemorySize(fileSize)
        }
      }

      this.lruCache.put(sortedCachefiles[i].file, fileSize)
      this.addMemorySize(fileSize)
    }

    this.trimToSize();
    LogUtil.info('image init initFileCache:' + (Date.now() - startTime) + ',num:' + filenames.length + ',nums:' + this.lruCache.length + ',size:' + this.currentMemory)
    this.isInited = true
  }

  public isFileCacheInit():boolean {
    return this.isInited
  }

  public getCacheFolder(): string {
    return FileCache.CACHE_FOLDER
  }

  // 添加缓存键值对,同时写文件
  put(key: string, value: ArrayBuffer): void {
    if (key == null || value == null) {
      throw new Error('key or value is invalid ');
    }
    if (!this.isInited) {
      return
    }

    // 如果size满了的话，需要按照LRU的方式删除第一个
    if (this.lruCache.length == this.maxSize && !this.lruCache.contains(key)) {
      this.remove(this.lruCache.keys()[0])
    } else if (this.lruCache.contains(key)) {
      this.remove(key)
    }

    let pre = this.lruCache.put(key, value.byteLength)
    FileUtils.getInstance().writeDataSync(this.path + key, value)
    if (pre !== undefined) {
      this.addMemorySize(value)
    }
    this.trimToSize()
  }

  // 添加缓存键值对，但不写文件（用于子线程已经写文件的场景）
  putWithoutWriteFile(key: string, value: ArrayBuffer | number): void {
    if (key == null || value == null) {
      throw new Error('key or value is invalid ');
    }
    if (!this.isInited) {
      return
    }

    // 如果size满了的话，需要按照LRU的方式删除第一个
    if (this.lruCache.length == this.maxSize && !this.lruCache.contains(key)) {
      this.remove(this.lruCache.keys()[0])
    } else if (this.lruCache.contains(key)) {
      this.lruCache.remove(key)
      this.lruCache.put(key, typeof value == 'number' ? value : value.byteLength)
      return
    }

    this.lruCache.put(key, typeof value == 'number' ? value : value.byteLength)
    this.addMemorySize(value)
    this.trimToSize()
  }

  get(key: string): ArrayBuffer | undefined {
    if (!this.isInited) {
      return
    }

    if (this.lruCache.get(key) !== undefined) {
      // TODO 如何才能修改文件访问时间呢
      return FileUtils.getInstance().readFileSync(this.path + key)
    }
    return undefined
  }

  // 移除键为key的缓存
  remove(key: string): void {
    if (key == null) {
      throw new Error('key is null,checking the parameter');
    }
    if (!this.isInited) {
      return
    }

    let remove: number | undefined = this.lruCache.remove(key)
    if (remove !== undefined) {
      FileUtils.getInstance().deleteFile(this.path + key)
      this.removeMemorySize(remove)
    }
  }

  async removeAll(): Promise<void> {
    if (!this.isInited) {
      return
    }
    this.lruCache.clear()
    this.currentMemory = 0;

    let filenames: string[] = await FileUtils.getInstance().ListFile(this.path)
    for (let i = 0; i < filenames.length; i++) {
      await FileUtils.getInstance().deleteFile(this.path + filenames[i])
    }
  }

  size(): number {
    return this.lruCache.length
  }

  // 移除较少使用的缓存数据
  private trimToSize(): void {
    while (true) {
      if (this.currentMemory <= this.maxMemory || this.lruCache.isEmpty()) {
        break
      }
      let delkey = this.lruCache.keys()[0]
      let remove: number | undefined = this.lruCache.remove(delkey)
      if (remove !== undefined) {
        FileUtils.getInstance().deleteFile(this.path + delkey)
        this.removeMemorySize(remove)
      }
      this.lruCache.remove(delkey)
    }
  }

  private removeMemorySize(value: ArrayBuffer | number): void {
    if (typeof value == 'number') {
      this.currentMemory -= value
    }
    else if (value != undefined) {
      this.currentMemory -= value.byteLength
      LogUtil.debug('FileCache removeMemorySize: ' + value.byteLength + ' currentMemory：' + this.currentMemory)
    }
  }

  private addMemorySize(value: ArrayBuffer | number): void {
    if (typeof value == 'number') {
      this.currentMemory += value
      LogUtil.debug('FileCache addMemorySize: ' +  value + ' currentMemory：' + this.currentMemory)
    }
    else if (value != undefined) {
      this.currentMemory += value.byteLength
      LogUtil.debug('FileCache addMemorySize: ' + value.byteLength + ' currentMemory：' + this.currentMemory)
    }
  }

  /**
   * 子线程里只写入缓存文件
   * @param context
   * @param key
   * @param value
   */
  static saveFileCacheOnlyFile(context: Context, key: string, value: ArrayBuffer, folder: string = FileCache.CACHE_FOLDER): boolean {
    // 写文件
    if (!FileUtils.getInstance()
      .writeFileSync(context.cacheDir + FileUtils.SEPARATOR + folder + FileUtils.SEPARATOR + key, value)) {
      FileUtils.getInstance().createFolderSync(context.cacheDir + FileUtils.SEPARATOR + folder + FileUtils.SEPARATOR)
      FileUtils.getInstance()
        .writeFileSync(context.cacheDir + FileUtils.SEPARATOR + folder + FileUtils.SEPARATOR + key, value)
    }
    return true
  }

  /**
   * 子线程中，通过文件名，直接查找是否有文件缓存
   * @param context
   * @param key
   * @returns
   */
  static getFileCacheByFile(context: Context, key: string, folder: string = FileCache.CACHE_FOLDER): ArrayBuffer | undefined {
    // 从文件获取查看是否有缓存
    return FileUtils.getInstance()
      .readFileSync(context.cacheDir + FileUtils.SEPARATOR + folder + FileUtils.SEPARATOR + key)
  }

  /**
   * 获取key缓存数据绝对路径
   *
   * @params key 数值
   */
  getFileToPath(key: string): string {
    if(!!!key) {
      throw new Error('key is null,checking the parameter')
    }
    let path = this.path + key
    if(FileUtils.getInstance().exist(path)) {
      return path
    } else {
      return ''
    }
  }
}