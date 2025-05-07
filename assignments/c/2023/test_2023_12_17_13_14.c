#include <stdio.h>

int function(int n) {
  if (n == 1) {
    return 1;
  } else if (n == 2) {
    return 2;
  } else {
    return function(n - 1) + function(n - 2);
  }
}

int main(void) {
  int n = 0;
  scanf("%d", &n);
  printf("%d\n", function(n));
  return 0;
}