#include <stdio.h>

int checkSys(void) {
  union {
    char c;
    int a;
  } u;
  u.c = 1;
  return u.a;
}

int main(void) {
  printf(checkSys() ? "小端\n" : "大端\n");
  return 0;
}