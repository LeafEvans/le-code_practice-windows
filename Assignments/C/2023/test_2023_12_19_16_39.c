#include <stdio.h>

int main(void) {
  int n = 0;

  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int x = 0;
    int y = 0;

    scanf("%d %d", &x, &y);
    
    for (int j = 0; j <= x; ++j) {
      for (int k = 0; k <= x; ++k) {
        for (int m = 0; m <= x; ++m) {
          if (j * 3 + k * 2 + m == y && j + k + m == x) printf("%d %d %d\n", j, k, m);
        }
      }
    }
  }

  return 0;
}