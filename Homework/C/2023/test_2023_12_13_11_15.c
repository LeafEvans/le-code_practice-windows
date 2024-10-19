#include <stdio.h>

#define MAX_LEN 10

int main(void) {
  int arr[MAX_LEN][MAX_LEN] = {0};
  int n = 0;

  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= i; j++) {  // j <= i 便于初始化
      if (j == 0 || j == i) {
        arr[i][j] = 1;
      } else {
        arr[i][j] = arr[i - 1][j] + arr[i - 1][j - 1];
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= i; j++) {
      printf("%-4d", arr[i][j]);
    }
    printf("\n");
  }

  return 0;
}
