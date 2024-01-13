#include <stdio.h>

int main(void) {
  int aa[2][5] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int *ptr1 = (int *)(&aa + 1);  // 取出整个数组的地址，然后加1，再强制类型转换
  int *ptr2 = (int *)(*(aa + 1));
  // 对第二行的地址进行解引用，就是第二行首元素的地址
  printf("%d,%d\n", *(ptr1 - 1), *(ptr2 - 1));  // 2,5
  return 0;
}