#include <stdio.h>

int main(void) {
  int ch = 0;
  int n = 0;

  scanf("%c %d", &ch, &n);

  for (int i = 1; i <= n - 1; ++i) {
    for (int j = 1; j <= 2 * n - 1; ++j) {
      if (j == n - i + 1 || j == n + i - 1) {
        printf("%c", ch);
        continue;
      }
      printf("*");
    }
    printf("\n");
  }

  for (int i = 1; i <= 2 * n - 1; ++i) printf("%c", ch);

  return 0;
}