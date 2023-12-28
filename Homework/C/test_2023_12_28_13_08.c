#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main(void) {
  int a = 5;
  int b = 4;
  int m = MAX(a++, b++);
  printf("%d\n", m);
  printf("a=%d b=%d\n", a, b);
  return 0;
}