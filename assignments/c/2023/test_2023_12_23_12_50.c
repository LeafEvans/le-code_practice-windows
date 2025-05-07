#include <stdio.h>
#include <stdlib.h>

typedef struct st_type {
  int i;
  int a[0];
} type_a;

int main(void) {
  type_a* pt = (type_a*)malloc(sizeof(type_a) + 40);
  if (pt == NULL) return 1;
  pt->i = 100;
  for (int i = 0; i < 10; ++i) {
    pt->a[i] = i;
  }
  for (int i = 0; i < 10; ++i) {
    printf("%d ", pt->a[i]);
  }
  type_a* ptr = (type_a*)realloc(pt, sizeof(type_a) + 80);
  if (ptr != NULL) {
    pt = ptr;
    ptr = NULL;
  }
  free(pt);
  pt = NULL;
  return 0;
}