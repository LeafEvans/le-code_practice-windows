#include <stdio.h>

struct A {
  int a : 3;
  int b : 4;
  int c : 5;
  int d : 4;
};

int main(void) {
  struct S s = {0};
  s.a = 10;
  s.b = 12;
  s.c = 3;
  s.d = 4;
  return 0;
}