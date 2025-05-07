#include <stdio.h>

union Un {
  int a;
  char c;
};

int main(void) {
  union Un u;
  u.a = 0x11223344;
  printf("%p\n", u.a);
  u.c = 0x00;
  printf("%p\n", u.a);
  return 0;
}