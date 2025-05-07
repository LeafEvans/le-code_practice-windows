#include <stdio.h>

struct S1 {
  char c1;
  int i;
  char c2;
};

struct S2 {
  char c1;
  char c2;
  int i;
};

int main(void) {
  printf("%d\n", sizeof(struct S1));
  printf("%d\n", sizeof(struct S2));
  return 0;
}
