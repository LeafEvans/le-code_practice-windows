#include <stdio.h>

int function(int n) {
  int a = 1;
  int b = 2;
  int c = 1;

  while (n > 2) {
    c = a + b;
    a = b;
    b = c;
    --n;
  }

  return c;
}

int main(void) {
  int n = 0;

  scanf("%d", &n);
  for (int j = 0; j < n; ++j) {
    int i = 0;
    scanf("%d", &i);
    printf("%d\n", function(i));
  }
}