#include <stdio.h>

union Un {
  char arr[5];
  int i;
};

int main(void) {
  printf("%d\n", sizeof(union Un));
  return 0;
}