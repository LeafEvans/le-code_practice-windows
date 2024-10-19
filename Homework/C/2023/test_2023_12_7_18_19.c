#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = *a;
}

int cmpStr(const void *e1, const void *e2) {
  return strcmp(*(char **)e1,
                *(char **)e2);  // 这个比较函数传进去的是数组每个元素的地址
  // 而每个元素又是一个地址，所以这个指针要被强制类型转换为二级指针，然后解引用得到每个字符串的首元素地址
  // 之后作为参数输入 strcmp 函数进行比较
}

void insertionSort(int arr[], int len) {
  int i = 0;
  int j = 0;

  for (i = 1; i <= len; i++) {
    int key = arr[i];

    for (j = i - 1; j >= 0 && arr[j] > key; j--) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = key;
  }
}

void selectionSort(int arr[], int len) {
  int i = 0;
  int j = 0;

  for (i = 0; i < len - 1; i++) {
    int min = arr[i];
    for (j = i + 1; j < len; j++) {
      if (min > arr[j]) min = j;
    }

    swap(&arr[j], &arr[i]);
  }
}

int main(void) {
  char str1[21] = {0};
  char str2[21] = {0};
  char str3[21] = {0};
  char str4[21] = {0};
  char str5[21] = {0};
  char *arr[5] = {str1, str2, str3, str4, str5};

  for (int i = 0; i < 4; i++) {
    scanf("%s", arr[i]);
  }

  qsort(arr, 4, sizeof(arr[0]), cmpStr);
  for (int i = 0; i < 4; i++) {
    printf("%s\n", arr[i]);
  }
  printf("\n");

  scanf("%s", arr[4]);
  qsort(arr, 5, sizeof(arr[0]), cmpStr);
  for (int i = 0; i < 5; i++) {
    printf("%s\n", arr[i]);
  }

  return 0;
}