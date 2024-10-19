#include <stdio.h>

int main(void) {
  float n = 0.0f;
  float arr[12] = {0};

  scanf("%f", &n);

  float max = 0.0f;

  for (int i = 0; i < 12; i++) {
    scanf("%f", &arr[i]);
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  printf("%.2f\n", n * max);

  return 0;
}