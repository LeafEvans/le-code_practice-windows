#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  int *p = (int *)malloc(40);
  if (NULL == p) {
    printf("%s\n", strerror(errno));
  }
  for (int i = 0; i < 10; ++i) {
    *(p + i) = i + 1;
  }
  int *ptr = (int *)realloc(p, 80);  // 定义一个新的变量去接收，而不是原来的变量，防止出现空指针
  if (ptr != NULL) {
    p = ptr;
    ptr = NULL;
  }
  for (int i = 0; i < 10; ++i) {
    printf("%d ", *(p + i));
  }
  return 0;
}