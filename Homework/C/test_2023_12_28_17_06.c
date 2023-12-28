#include <stddef.h>
#include <stdio.h>

struct S {
  char c1;
  int i;
  char c2;
};

#define OFFSETOF(TYPE, M_NAME) (size_t) & (((TYPE*)0)->M_NAME)

int main(void) {
  struct S s = {0};
  printf("%d\n", offsetof(struct S, c1));
  printf("%d\n", offsetof(struct S, i));
  printf("%d\n", offsetof(struct S, c2));
  return 0;
}