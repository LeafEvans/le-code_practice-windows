#include <assert.h>
#include <stdio.h>
#include <string.h>

void *myMemmove(void *dest, void *src, size_t num) {
  assert(dest && src);
  void *ret = dest;
  if (dest < src) {
    while (num--)  // 与 memcpy 一致
    {
      *(char *)dest = *(char *)src;
      dest = (char *)dest + 1;
      src = (char *)src + 1;
    }
    return ret;
  } else {
    while (num--) {
      // num 判断后减 1，只剩 num - 1 个字节
      // 跳过 num - 1 个字节后就时指向目标数据的最后一个字节，然后解引用赋值
      *((char *)dest + num) = *((char *)src + num);
    }  // 之后 num 再减一，就可以实现
    return ret;
  }
}

int main(void) {
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  myMemmove(arr, arr + 2, 20);
  for (int i = 0; i < 10; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
  return 0;
}