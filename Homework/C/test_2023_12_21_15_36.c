#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  int *p = (int *)malloc(40);
  if (p == NULL) {
    printf("%s\n", strerror(errno));  // 开辟失败返回错误信息
    return 1;  // 历史习惯，返回0代表正常进行，所以用return 1表示正常返回
  }

  for (int i = 0; i < 10; ++i) {
    *(p + i) = i;
    printf("%d ", *(p + i));
  }
  free(p);   // 释放相应的内存空间
  p = NULL;  // 将p的值赋值为空指针，防止有人使用，变成野指针
  return 0;
}