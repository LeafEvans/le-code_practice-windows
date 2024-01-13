#include <stdio.h>

int main(void) {
  int n = 0;
  scanf("%d", &n);

  int sno[n];
  int grades[n][3];
  float avg[n];
  float max_avg = 0.0f;

  for (int i = 0; i < n; ++i) {
    scanf("%d %d %d %d", &sno[i], &grades[i][0], &grades[i][1], &grades[i][2]);
    avg[i] = (grades[i][0] + grades[i][1] + grades[i][2]) / 3.0;
    if (avg[i] > max_avg) max_avg = avg[i];
  }

  for (int i = 0; i < n; ++i) printf("%.2f\n", avg[i]);

  for (int i = 0; i < n; ++i) {
    if (max_avg == avg[i]) printf("%d %.2f\n", sno[i], avg[i]);
  }

  return 0;
}