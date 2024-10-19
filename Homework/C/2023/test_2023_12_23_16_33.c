#include <stdio.h>

struct test {
  int i;
  short c;
  char *p;
  char s[10];
};

int main(void) {
  struct test *pt = NULL;
  printf("&s = %x\n", pt->s);  // 等价于 printf("%x\n", &(pt->s) );
  printf("&i = %x\n", &pt->i);  // 因为操作符优先级，没有写成 &(pt->i)
  printf("&c = %x\n", &pt->c);
  printf("&p = %x\n", &pt->p);
  return 0;
}