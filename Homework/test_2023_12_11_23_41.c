#include <assert.h>
#include <stdio.h>

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int binarySearch(int arr[], int len, int target) {
  int left = 0;
  int right = len - 1;
  int mid = 0;

  while (left <= right) {
    mid = left + (right - left) / 2;

    if (arr[mid] > target) {
      right = mid - 1;
    } else if (arr[mid] < target) {
      left = mid + 1;
    } else {
      return mid;
    }
  }

  return -1;
}

void insertionSort(int *arr, int len) {
  int i = 0;
  int j = 0;

  for (i = 1; i < len; i++) {
    int key = arr[i];

    for (j = i - 1; j >= 0 && arr[j] > key; j--) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = key;
  }
}

void selectionSort(int *arr, int len) {
  int i = 0;
  int j = 0;

  for (i = 0; i < len - 1; i++) {
    int min = i;

    for (j = i + 1; j < len; j++) {
      if (arr[j] < arr[min]) {
        min = j;
      }
      swap(&arr[min], &arr[i]);
    }
  }
}

char *myStrstr(const char *str1, const char *str2) {
  assert(str1 && str2);
  const char *ptr1 = str1;
  const char *ptr2 = str2;
  const char *ptr3 = ptr1;

  while (*ptr3) {
    ptr1 = ptr3;
    ptr2 = str2;

    while (*ptr1 != '\0' && *ptr2 != '\0' && *ptr1 == *ptr2) {
      ptr1++;
      ptr2++;
    }

    if (*ptr2 == '\0') {
      return (char *)ptr3;
    }

    ++ptr3;
  }

  return NULL;
}

void bubbleSort(int *arr, int len) {
  for (int i = 0; i < len - 1; i++) {
    for (int j = 0; j < len - 1 - i; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
      }
    }
  }
}

int main(void) {
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  printf("%d\n", binarySearch(arr, sizeof(arr) / sizeof(arr[0]), 6));
  return 0;
}