#include <stdio.h>
#include <stdlib.h>

struct S {
  int n;
  int *arr;
};

int main(void) {
  struct S s;
  s.n = 100;
  s.arr = (int *)malloc(40);
  if (s.arr == NULL) return 1;
  for (int i = 0; i < 10; ++i) {
    s.arr[i] = i;
  }
  for (int i = 0; i < 10; ++i) {
    printf("%d ", s.arr[i]);
  }
  int *ptr = (int *)realloc(s.arr, 80);
  if (ptr == NULL) return 1;
  free(s.arr);
  s.arr = NULL;
  return 0;
}