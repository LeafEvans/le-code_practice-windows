#include <stdio.h>

int main(void) {
  int n = 0;
  scanf("%d", &n);

  while (n--) {
    int a = 0;
    int b = 0;
    int c = 0;
    scanf("%d %d %d", &a, &b, &c);

    int quotient = a / b;
    int remainder = a % b;

    printf("%d.", quotient);

    for (int i = 0; i < c; i++) {
      remainder *= 10;
      int digit = remainder / b;
      remainder %= b;
      if (i == c - 1 && remainder * 10 / b >= 5) digit++;
      printf("%d", digit);
    }
    printf("\n");
  }

  return 0;
}
