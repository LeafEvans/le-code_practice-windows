#include <stdio.h>

int main(void) {
  int n = 0;
  int l = 0;
  int k = 0;
  int y = 0;
  int min = -1;

  scanf("%d %d %d %d", &n, &l, &k, &y);

  char team[n][100];

  for (int i = 0; i < n; ++i) scanf("%s", team[i]);

  for (int i = 0; i < n; ++i) {
    int tmp = 0;
    for (int j = 0; team[i][j] != '\0'; ++j) {
      switch (team[i][j]) {
        case 'A':
          tmp += y + l + k;
          break;
        case 'B':
          tmp += 2 * l + k;
          break;
        case 'C':
          tmp += 3 * l + 3 * k + 2 * y;
          break;
      }
    }
    if (min > tmp || min == -1) min = tmp;
  }

  printf("%d\n", min);

  return 0;
}