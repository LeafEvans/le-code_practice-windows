#include <stdio.h>
#include <stdlib.h>

long long gcd(long long a, long long b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

void simplify(long long *numerator, long long *denominator) {
  long long g = gcd(abs(*numerator), abs(*denominator));
  *numerator /= g;
  *denominator /= g;
  if (*denominator < 0) {
    *denominator = -*denominator;
    *numerator = -*numerator;
  }
}

int main() {
  int n;
  long long numerator_sum = 0, denominator_sum = 1;

  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    long long numerator, denominator, g;
    scanf("%lld/%lld", &numerator, &denominator);

    numerator_sum = numerator_sum * denominator + numerator * denominator_sum;
    denominator_sum *= denominator;

    simplify(&numerator_sum, &denominator_sum);
  }

  if (denominator_sum == 1) {
    printf("%lld\n", numerator_sum);
  } else if (numerator_sum == 0) {
    printf("0\n");
  } else {
    printf("%lld/%lld\n", numerator_sum, denominator_sum);
  }

  return 0;
}