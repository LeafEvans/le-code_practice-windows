#include <stddef.h>
#include <stdio.h>

struct S1 {
  char c1;
  int i;
  char c2;
};

struct S3 {
  double d;
  char c;
  int i;
};

struct S4 {
  char c1;  // 偏移量为0
  struct S3 s;  // 嵌套的结构体，其最大对齐数为8，那就对齐到偏移量为8的整数倍
  double d;  // 对齐数为8，对齐到8的整数倍
};

int main(void) {
  printf("%d\n", sizeof(struct S3));
  printf("%d\n", sizeof(struct S4));
  return 0;
}