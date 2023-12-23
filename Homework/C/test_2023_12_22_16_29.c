#include <stdio.h>

void getMemory(char *p) { p = (char *)malloc(100); }
// 因为传的是形参，所以函数执行完后销毁，无法找到

void test(void) {
  char *str = NULL;
  getMemory(str);
  strcpy(str, "hello world");  // 对空指针进行解引用，还将值赋进去，程序崩溃
  printf(str);
}

int main(void) {
  test();
  return 0;
}