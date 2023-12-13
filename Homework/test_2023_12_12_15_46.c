#include <stdio.h>

int singleNum(int arr[], int len) {
  int i = 0;
  int j = 0;
  int arr_tmp[100] = {0};

  for (i = 0; i < len; ++i) {
    for (j = i + 1; j < len; ++j) {
      if (arr[i] == arr[j] && arr_tmp[j] == 0) {
        arr_tmp[i] = 1;
        arr_tmp[j] = 1;
      }
    }
  }

  for (i = 0; i < len; i++) {
    if (arr_tmp[i] == 0) {
      return arr[i];
    }
  }

  return -1;
}

int main(void) {
  int n = 0;
  int arr[100] = {0};

  scanf("%d", &n);

  for (int i = 0; i < n; ++i) {
    scanf("%d", &arr[i]);
  }

  printf("%d\n", singleNum(arr, n));

  return 0;
}