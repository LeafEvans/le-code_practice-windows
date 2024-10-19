#include <stdio.h>

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int main(void) {
  int n = 0;
  int arr[4] = {0};
  scanf("%d", &n);
  for (int j = 0; j < n; ++j) {
    for (int i = 0; i < 4; ++i) {
      scanf("%d", &arr[i]);
    }

    int min = arr[0];
    int max = arr[0];

    for (int i = 0; i < 4; ++i) {
      if (min > arr[i]) swap(&min, &arr[i]);
      if (max < arr[i]) swap(&max, &arr[i]);
    }

    printf("%d %d\n", max, min);
  }

  return 0;
}