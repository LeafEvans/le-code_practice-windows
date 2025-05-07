#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  int arr[n];
  scanf("%d", &n);
  int *p = (int *)malloc(INT_MAX);

  if (p == NULL) {
    printf("%s\n", strerror(errno));
    return 1;
  }

  return 0;
}
