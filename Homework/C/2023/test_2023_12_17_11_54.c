#include <stdio.h>

int main(void) {
  int n = 0;
  scanf("%d", &n);

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= i; ++j) {
      printf("%d*%d=%-3d", i, j, i * j);
    }
    printf("\n");
  }

  return 0;
}