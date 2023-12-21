#include <stdio.h>

int main(void) {
  int n = 0;
  scanf("%d", &n);
  int arr[n][n];
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      scanf("%d", &arr[i][j]);
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      printf("%d ", arr[i][j] + arr[j][i]);
    }
    printf("\n");
  }

  return 0;
}