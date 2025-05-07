#include <stdio.h>

int main(void) {
  int n = 0;
  int m = 0;
  int num = 0;

  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &m);
    for (int j = 2; j <= m; ++j) {
      num += (j - 1) * j * (j + 1);
    }
    printf("%d\n", num);
  }

  return 0;
}