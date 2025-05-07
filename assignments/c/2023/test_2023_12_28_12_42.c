#include <stdio.h>
#define PRINT(N, FORMAT) printf("The value of " #N " is " FORMAT "\n", N)

int main(void) {
  int a = 5;
  PRINT(a, "%d");
  float f = 3.14f;
  PRINT(f, "%f");
  return 0;
}
