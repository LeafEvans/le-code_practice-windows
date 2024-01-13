#include <stdio.h>

int changeNum(int num) {
  int new_num = 0;

  while (num) {
    if (num % 10 % 2 == 0) {
      new_num = new_num * 10;
    } else {
      new_num = new_num * 10 + 1;
    }
    num /= 10;
  }

  return new_num;
}

int main(void) {
  int n = 0;
  scanf("%d", &n);
  printf("%d\n", changeNum(n));
  return 0;
}