#include <stdio.h>

int main(void) {
  int n = 0;
  int flag = 1;

  scanf("%d", &n);

  int arr[n][n];

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
        scanf("%d", &arr[i][j]);
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      if (arr[i][j] != 0) {
        flag = 0;
        break;
      } 
    }
    if (flag == 0) {
      break;
    }
  }

  printf(flag ? "YES\n" : "NO\n");

  return 0;
}