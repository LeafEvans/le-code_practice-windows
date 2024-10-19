#include <stdio.h>

int main(void) {
  union {
    short k;
    char i[2];
  } *s, a;
  s = &a;
  s->i[0] = 0x39;
  s->i[1] = 0x38;
  printf("%x\n", a.k);

  return 0;
}