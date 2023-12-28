#define SQUARE(X) ((X) * (X))
#define DOUBLE(X) ((X) + (X))
#define M 100
#include <stdio.h>

int main(void) {
  printf("%d %d\n", SQUARE(M + 2), DOUBLE(M + 2));
  return 0;
}