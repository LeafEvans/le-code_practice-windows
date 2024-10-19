#include <stdio.h>

int main(void) {
  int n = 0;
  int m = 0;

  scanf("%d", &n);

  int pm[n][3];

  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= n; ++j) {
      for (int k = 0; k <= n; ++k) {
        if (i * 5 + j * 3 + k / 3 == n && k % 3 == 0 && i + j + k == n) {
          pm[m][0] = i;
          pm[m][1] = j;
          pm[m][2] = k;
          ++m;
        }
      }
    }
  }

  if (m) {
    for (int i = 0; i < m; ++i) {
      printf("%d %d %d\n", pm[i][0], pm[i][1], pm[i][2]);
    }
  } else {
    printf("NO\n");
  }

  return 0;
}