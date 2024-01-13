#include <stdio.h>
#include <stdlib.h>

long long gcd(long long a, long long b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

void simplify(long long *num, long long *den) {
  long long g = gcd(abs(*num), abs(*den));
  *num /= g;
  *den /= g;
  if (*den < 0) {
    *den = -*den;
    *num = -*num;
  }
}

int main(void) {
  int n = 0;
  long long num_sum = 0;
  long long den_sum = 1;
  
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    long long int num = 0;
    long long int den = 0;
    scanf("%lld/%lld", &num, &den);
    num_sum = num_sum * den + num * den_sum;
    den_sum *= den;

    simplify(&num_sum, &den_sum);
  }

  if (den_sum == 1) {
    printf("%lld\n", num_sum);
  } else if (num_sum == 0) {
    printf("0\n");
  } else {
    printf("%lld/%lld\n", num_sum, den_sum);
  }

  return 0;
}