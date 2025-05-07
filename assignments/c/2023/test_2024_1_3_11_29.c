#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int n = 0;
  scanf("%d", &n);

  for (int i = 0; i < n; ++i) {
    long long a = 0;
    long long b = 0;
    int c = 0;

    if ((a > 0 && b < 0) || (a < 0 && b > 0)) {
      printf("-");
      b = -a;
    }
    scanf("%lld %lld %d", &a, &b, &c);

    long long integer_part = a / b;
    printf("%lld", integer_part);

    printf(".");
    long long remainder = a % b;

    for (int j = 0; j < c; ++j) {
      remainder *= 10;
      int digit = remainder / b;
      printf("%d", digit);
      remainder %= b;

      if (j == c - 1) {
        remainder *= 10;
        if (remainder / b >= 5) {
          fseek(stdout, -1, SEEK_CUR);
          printf("%d", digit + 1);
        }
      }
    }
    printf("\n");
  }

  return 0;
}