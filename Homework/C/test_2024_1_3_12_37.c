#include <stdio.h>

int main(void) {
  int t = 0;
  scanf("%d", &t);

  for (int i = 0; i < t; ++i) {
    int n = 0;
    int floor = 0;
    int total_time = 0;

    scanf("%d", &n);
    for (int j = 0; j < n; ++j) {
      int temp = floor;
      scanf("%d", &floor);
      if (floor > temp) {
        total_time += 6 * (floor - temp) + 5;
      } else if (floor < temp) {
        total_time += 4 * (temp - floor) + 5;
      }
    }

    printf("%d\n", total_time);
  }

  return 0;
}