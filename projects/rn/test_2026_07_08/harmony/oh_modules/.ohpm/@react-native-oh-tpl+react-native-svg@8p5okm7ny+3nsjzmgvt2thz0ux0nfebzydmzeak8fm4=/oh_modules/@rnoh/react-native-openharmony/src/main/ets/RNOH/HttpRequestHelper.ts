/**
 * Copyright (c) 2024 Huawei Technologies Co., Ltd.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

import http from '@ohos.net.http';

export type FetchOptions = {
  headers?: Record<string, any>,
  usingCache?: boolean
}

export type FetchResult = {
  headers: Object,
  result: ArrayBuffer,
  responseCode?: number
}

export async function fetchDataFromUrl(url: string, options: FetchOptions = { usingCache: true }, onProgress?: (progress: number) => void): Promise<FetchResult> {
  return new Promise((resolve, reject) => {
    const httpRequest = http.createHttp();
    const dataChunks: ArrayBuffer[] = [];
    let result: ArrayBuffer | undefined;
    let headers: Object | undefined;
    let responseCode: number | undefined;

    let dataReceiveProgressHandler: ((progress: { receiveSize: number, totalSize: number }) => void) | undefined;
    let headersReceiveHandler: ((data: Object) => void) | undefined;
    let dataReceiveHandler: ((chunk: ArrayBuffer) => void) | undefined;
    let dataEndHandler: (() => void) | undefined;

    function cleanUp() {
      try {
        if (dataReceiveProgressHandler) {
          httpRequest.off("dataReceiveProgress", dataReceiveProgressHandler);
          dataReceiveProgressHandler = undefined;
        }
        if (headersReceiveHandler) {
          httpRequest.off("headersReceive", headersReceiveHandler);
          headersReceiveHandler = undefined;
        }
        if (dataReceiveHandler) {
          httpRequest.off("dataReceive", dataReceiveHandler);
          dataReceiveHandler = undefined;
        }
        if (dataEndHandler) {
          httpRequest.off("dataEnd", dataEndHandler);
          dataEndHandler = undefined;
        }
      } catch (err) {
        // eslint-disable-next-line no-console
        console.warn("Failed to remove httpRequest listeners: " + err);
      }
      httpRequest.destroy();
    }

    function maybeResolve() {
      if (result !== undefined && headers !== undefined && responseCode !== undefined) {
        resolve({ headers, result, responseCode });
        cleanUp();
      }
    }

    dataReceiveProgressHandler = ({ receiveSize, totalSize }) => {
      onProgress?.(receiveSize / totalSize);
    };

    httpRequest.on("dataReceiveProgress", dataReceiveProgressHandler);

    headersReceiveHandler = (data) => {
      headers = data;
      maybeResolve();
    };

    httpRequest.on("headersReceive", headersReceiveHandler);

    dataReceiveHandler = (chunk) => {
      dataChunks.push(chunk);
    };

    httpRequest.on("dataReceive", dataReceiveHandler);

    dataEndHandler = () => {
      const totalLength = dataChunks.map(chunk => chunk.byteLength).reduce((acc, length) => acc + length, 0);
      const data = new Uint8Array(totalLength);
      let offset = 0;
      for (const chunk of dataChunks) {
        const chunkArray = new Uint8Array(chunk);
        data.set(chunkArray, offset);
        offset += chunk.byteLength;
      }
      result = data.buffer;
      maybeResolve();
    };

    httpRequest.on("dataEnd", dataEndHandler);

    try {
      httpRequest.requestInStream(
        url,
        {
          header: options.headers,
          usingCache: options.usingCache
        },
        (err, data) => {
          responseCode = data
          if (err) {
            reject(new Error(`Couldn't fetch data from ${url}, ${err.message}`));
            cleanUp();
          } else {
            maybeResolve();
          }
        }
      );
    } catch (err) {
      reject(new Error(`Couldn't fetch data from ${url}, ${err.message}`));
      cleanUp();
    }
  })
}