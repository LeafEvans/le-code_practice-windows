#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getMemory(char **p, int num) { *p = (char *)malloc(num); }

void test(void) {
  char *str = NULL;
  getMemory(&str, 100);
  strcpy(str, "hello");
  printf(str);
  free(str);
  str = NULL;
}

int main(void) {
  test();
  return 0;
}