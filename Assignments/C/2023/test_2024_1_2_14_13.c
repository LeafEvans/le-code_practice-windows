#include <stdio.h>

int ageN(int n, int a, int k) {
  if (n > 1) {
    return k + ageN(n - 1, a, k);
  } else if (n == 1) {
    return a;
  }
  return 0;
}

int main(void) {
  int n = 0;
  int a = 0;
  int k = 0;
  scanf("%d %d %d", &n, &a, &k);
  if (n < 2 || a > 100 || n > 100 || k > 100 || a <= 0 || k <= 0) {
    printf("Wrong Number\n");
    return 1;
  }
  printf("%d\n", ageN(n, a, k));
  return 0;
}