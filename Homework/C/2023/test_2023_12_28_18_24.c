#include <stdio.h>

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void selectSort(int arr[], int len) {
  for (int i = 0; i < len - 1; ++i) {
    int min = i;
    for (int j = i + 1; j < len; ++j) {
      if (arr[min] > arr[j]) {
        min = j;
      }
    }
    swap(&arr[min], &arr[i]);
  }
}

int main(void) {
  int n = 0;
  scanf("%d", &n);

  int arr[n];

  for (int i = 0; i < n; ++i) {
    scanf("%d", &arr[i]);
  }

  selectSort(arr, n);

  for (int i = 0; i < n; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  return 0;
}