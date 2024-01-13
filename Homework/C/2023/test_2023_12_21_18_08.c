#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  int *p = (int *)malloc(40);
  if (p == NULL) {
    return 1;
  }

  for (int i = 0; i < 10; ++i) {
    *(p + i) = i;
    printf("%d ", *(p + i));
  }

  free(p);
  p = NULL;

  return 0;
}