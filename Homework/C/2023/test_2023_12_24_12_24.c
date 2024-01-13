#include <stdio.h>

float sum(int a, int b) {
  int left = 0;
  int right = 0;
  float sum = 0.0f;

  if (a > b) {
    right = a;
    left = b;
  } else {
    right = b;
    left = a;
  }

  while (left <= right) {
    if (left == 0) {
      left++;
      continue;
    }
    sum += 1.0 / left;
    left++;
  }

  return sum;
}

int main(void) {
  int n = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int a = 0;
    int b = 0;
    scanf("%d %d", &a, &b);
    printf("%.3f\n", sum(a, b));
  }

  return 0;
}