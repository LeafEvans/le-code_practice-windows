#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

long int gcd(long int a, long int b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

void simplify(long int *num, long int *den) {
  long int g = gcd(abs(*num), abs(*den));
  *num /= g;
  *den /= g;

  if (*den < 0) {
    *num = -*num;
    *den = -*den;
  }
}

int main(void) {
  int n = 0;
  long int num_sum = 0;
  long int den_sum = 1;

  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    long int num = 0;
    long int den = 0;
    scanf("%d/%d", &num, &den);
    if (den == 0) {
      printf("error\n");
      return 1;
    }

    num_sum = num_sum * den + num * den_sum;
    den_sum *= den;

    simplify(&num_sum, &den_sum);
  }

  if (den_sum == 1) {
    printf("%d\n", num_sum);
  } else if (num_sum == 0) {
    printf("0\n");
  } else {
    printf("%d/%d\n", num_sum, den_sum);
  }

  return 0;
}