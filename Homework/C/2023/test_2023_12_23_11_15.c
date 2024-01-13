#include <stdio.h>
#include <string.h>

char *getMemory(void) {
  char *p = "hello world";
  return p;
}

void test(void) {
  char *str = NULL;
  str = getMemory();
  printf(str);
}

int main(void) {
  test();
  return 0;
}