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

export function combineArrayBuffers(arrayBuffers: ArrayBuffer[]): ArrayBuffer {
  // 计算多个ArrayBuffer的总字节大小
  let totalByteLength = 0;
  for (const arrayBuffer of arrayBuffers) {
    totalByteLength += arrayBuffer.byteLength;
  }

  // 创建一个新的ArrayBuffer
  const combinedArrayBuffer = new ArrayBuffer(totalByteLength);

  // 创建一个Uint8Array来操作新的ArrayBuffer
  const combinedUint8Array = new Uint8Array(combinedArrayBuffer);

  // 依次复制每个ArrayBuffer的内容到新的ArrayBuffer中
  let offset = 0;
  for (const arrayBuffer of arrayBuffers) {
    const sourceUint8Array = new Uint8Array(arrayBuffer);
    combinedUint8Array.set(sourceUint8Array, offset);
    offset += sourceUint8Array.length;
  }

  return combinedArrayBuffer;
}