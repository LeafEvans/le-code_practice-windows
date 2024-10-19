#include <stdio.h>

int test(void) {
  // 开辟空间
  int *p = (int *)malloc(100);
  if (p == NULL) return p;

  return p;
}

int main(void) {
  int *ret = test();  // 忘记释放
  
  return 0;
}