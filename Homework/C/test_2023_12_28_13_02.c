#include <stdio.h>
#define CAT(X, Y) X##Y

int main(void) {
  int SumNum = 100;
  printf("%d\n", CAT(Sum, Num));
  return 0;
}