#include <ctype.h>
#include <math.h>
#include <stdio.h>

int main(int argc, char** argv) {
  int *x = NULL;
  for (int i = 0; i < 10; ++i) {
    printf("%.0f ", pow(i, i));
  }
  putchar('\n');
  return 0;
}
