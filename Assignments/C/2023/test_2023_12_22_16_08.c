#include <stdio.h>

int main(void) {
  int *p = (int *)malloc(40);

  free(p);
  p = NULL;
  free(p);

  return 0;
}