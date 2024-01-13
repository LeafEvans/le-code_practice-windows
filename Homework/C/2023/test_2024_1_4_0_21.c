#include <stdio.h>

void insertionSort(int arr[], int len) {
  int i, j;
  for (i = 1; i < len; ++i) {
    int key = arr[i];
    for (j = i - 1; j >= 0 && arr[j] > key; --j) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = key;
  }
}

int main(void) {
  int n = 0;
  int arr[10] = {0};

  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 10; ++j) {
      scanf("%d", &arr[j]);
    }
    insertionSort(arr, sizeof(arr) / sizeof(arr[0]));
    for (int j = 0; j < 10; ++j) {
      printf("%d ", arr[j]);
    }
    printf("\n");
  }

  return 0;
}