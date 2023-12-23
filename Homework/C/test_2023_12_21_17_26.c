#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  int *p = (int *)calloc(10, sizeof(int));
  if (p == NULL) {
    printf("%s\n", strerror(errno));
  }
  for (int i = 0; i < 10; ++i) {
    printf("%d ", *(p + i));
  }
  free(p);
  p = NULL;
  return 0;
}