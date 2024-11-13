#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *pa, int *pb) {
  if (pa == pb) return;
  int temp = *pa;
  *pa = *pb;
  *pb = temp;
}

void quick_sort(int *arr, int left, int right) {
  if (left > right) {
    return;
  }

  int x = arr[left], i = left - 1, j = right + 1;

  while (i < j) {
    do {
      ++i;
    } while (arr[i] < x);

    do {
      --j;
    } while (arr[j] > x);

    if (i < j) {
      swap(&arr[i], &arr[j]);
    }
  }

  quick_sort(arr, left, j);
  quick_sort(arr, j + 1, right);
}

void merge_sort(int *arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int mid = left + ((right - left) >> 1);

  merge_sort(arr, left, mid);
  merge_sort(arr, mid + 1, right);

  int k = 0, i = left, j = mid + 1;

  int *temp = malloc(sizeof(int) * (right - left + 1));

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j]) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
    }
  }

  while (i <= mid) {
    temp[k++] = arr[i++];
  }

  while (j <= right) {
    temp[k++] = arr[j++];
  }

  for (int m = left, n = 0; m <= right; ++m, ++n) {
    arr[m] = temp[n];
  }

  free(temp);
}

int main(void) {
  srand((unsigned int)time(NULL));
  int arr[10] = {0};
  for (int i = 0; i < 10; i++) {
    arr[i] = rand() % 100 + 1;
    printf("%d ", arr[i]);
  }
  printf("\n");
  merge_sort(arr, 0, 9);
  for (int i = 0; i < 10; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");
  return 0;
}
