#include <stdio.h>

long long findGcd(long long a, long long b) {
  long long c = 0;

  while (c = a % b) {
    a = b;
    b = c;
  }

  return b;
}

long long findLcm(long long a, int b) {
  long long c = findGcd(a, b);
  return (a * b) / c;
}

int main(void) {
  long long n = 0;
  long long m = 0;

  while (scanf("%lld %lld", &n, &m) == 2) {
    printf("%d\n", findGcd(n, m) + findLcm(n, m));
  }
  return 0;
}