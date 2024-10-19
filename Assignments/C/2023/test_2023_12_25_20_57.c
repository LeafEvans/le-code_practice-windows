#include <stdio.h>

int insertionSort(int *arr, int len) {
  int i = 0;
  int j = 0;

  for (i = 1; i < len; ++i) {
    int key = arr[i];
    for (j = i - 1; j >= 0 && arr[j] > key; --j) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = key;
  }
}

int main(void) {
  int k = 0;
  scanf("%d", &k);

  int arr[k];

  for (int i = 0; i < k; ++i) scanf("%d ", &arr[i]);
  insertionSort(arr, k);

  switch (k) {
    case 6:
      for (int i = 0; i < 6; ++i) printf("%d ", arr[i]);
      printf("\n");
      break;
    case 7:
      for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 6; ++j) {
          if (j > 6 - i) {
            printf("%d ", arr[j + 1]);
            continue;
          }
          printf("%d ", arr[j]);
        }
        printf("\n");
      }
      break;
    case 8:
      
  }
  return 0;
}