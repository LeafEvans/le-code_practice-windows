#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getMemory(char **p) { *p = (char *)malloc(100); }

void test(void) {
  char *str = NULL;
  getMemory(&str);
  strcpy(str, "hello world");
  printf(str);
  free(str);
  str = NULL;
}

int main(void) {
  test();
  return 0;
}