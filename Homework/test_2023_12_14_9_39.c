// 杨氏矩阵
// 1 2 3
// 4 5 6
// 7 8 9

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int binarySearch(int arr[], int num, int len) {
  int left = 0;
  int right = len - 1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (arr[mid] > num) {
      left = mid +1;
    } else if (arr[mid] < num ) {
      right = mid - 1;
    } else {
      return mid;
    }
  }
  return -1;
}

void bubbleSort(int arr[], int sz) {
  for (int i = 0; i < sz - 1; ++i) {
    int flag = 1;
    for (int j = 0; j < sz - 1 - i; ++j) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
        flag = 0;
      }
    }
    if (flag == 1) {
      return;
    }
  }
}

void insertionSort(int arr[], int sz) {
  int i = 0;
  int j = 0;
  for (i = 1; i < sz; ++i) {
    int key = arr[i];
  
    for (j = i - 1; j >= 0 && arr[j] > key; --j) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = key;
  }
}

void selectionSort(int arr[], int sz) {
  for (int i = 0; i < sz - 1; ++i) {
    int min = i;
    for (int j = i + 1; j < sz; ++j) {
      if (arr[j] < arr[min]) {
        min = j;
      }
    }
    swap(&arr[min], &arr[i]);
  }
}

int findNum(int arr[][3], int *px, int *py, int num) {
  int x = 0;
  int y = *py - 1;
  while (x < *px && y >= 0) {
    if (num > arr[x][3]) {
      ++x;
    } else if (num < arr[x][y]) {
      --y;
    } else {
      *px = x;
      *py = y;
      return 1;
    }
  }
  return 0;
}

int isValidIP(const char *ip) {
  int num = 0;
  int dots = 0;

  if (isdigit(*ip)) {
    while (*ip) {
      num = 0;

      if (*ip == '.') {
        ++ip;
        ++dots;

        if (dots > 3) return 0;
        continue;
      }

      if (dots > 0 && (!isdigit(*ip) || *ip == '0')) return 0;

      while (isdigit(*ip)) {
        num = num * 10 + (*ip - '0');

        if (num > 255) return 0;

        ++ip;
      }

      if (*ip != '\0' && *ip != '.') return 0;
    }

    return dots == 3;
  } else {
    return 0;
  }
}


int main(void) {
  return 0;
}