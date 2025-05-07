#include <stdio.h>

int main(void) {
  int x = 0;
  int y = 0;
  int n = 0;
  scanf("%d", &n);

  for (int i = 0; i < n; ++i) {
    scanf("%d %d", &x, &y);

    if ((y - 2 * x) % 2 != 0 || y - 2 * x < 0) {
      printf("error\n");
    } else {
        int r = (y - 2 * x) / 2;
        int c = x - r;

        if (r < 0 || c < 0) {
          printf("error\n");
        } else {
          printf("%d %d", c, r);
        }
    }
  }

  return 0;
}