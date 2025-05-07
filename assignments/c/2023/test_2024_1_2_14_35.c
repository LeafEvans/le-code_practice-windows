#include <stdio.h>

int countStep(int);

int main(void) {
  int t = 0;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    int n = 0;
    scanf("%d", &n);
    printf("%d\n", countStep(n));
  }
  return 0;
}

int countStep(int n) {
  int count = 0;

  while (n != 1) {
    if (n % 2 == 0) {
      n /= 2;
      ++count;
    } else {
      n = (3 * n + 1) / 2;
      ++count;
    }
  }

  return count;
}