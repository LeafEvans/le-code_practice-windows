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


export namespace CalculatePixelUtils {

  export function createInt2DArray(first_len: number, second_len: number): Array<Array<number>> {
    let array = new Array<Array<number>>();
    for (let f = 0; f < first_len; f++) {
      let s1 = new Array<number>();
      for (let s = 0; s < second_len; s++) {
        s1.push(0);
      }
      array.push(s1);
    }
    return array;
  }
}