#include <stdio.h>

int main(void) {
  printf("%d\n", M);
#undef M
  printf("%d\n", M);
  return 0;
}