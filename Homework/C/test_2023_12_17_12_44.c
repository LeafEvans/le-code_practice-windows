#include <stdio.h>

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int selsectionSort(int arr[], int len) {
  for (int i = 0; i < len; ++i) {
    int max = i;
    for (int j = i + 1; j < len; ++j) {
      if (arr[j] > arr[max]) max = j;
    }
    swap(&arr[i], &arr[max]);
  }
}

int main(void) {
  int n = 0;
  int m = 0;

  scanf("%d %d", &n, &m);

  int arr[n];

  for (int i = 0; i < n; ++i) scanf("%d", &arr[i]);
  selsectionSort(arr, n);

  for (int i = 0; i < m; ++i) {
    printf("%d ", arr[i]);
  }

  return 0;
}