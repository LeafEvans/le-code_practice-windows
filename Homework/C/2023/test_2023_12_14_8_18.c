// 1  2  3  4
// 5  6  7  8
// 9  10 11 12
// 13 14 15 16
// 左下角和右上角有相应的特性

#include <stdio.h>

int findNum(int arr[4][4], int *px, int *py, int k) {
  int x = *px - 1;
  int y = 0;

  while (x >= 0 && y < *py) {
    if (k > arr[x][y]) {
      y++;
    } else if (k < arr[x][y]) {
      x--;
    } else {
      *px = x;
      *py = y;
      return 1;
    }
  }
  return 0;
}

int main(void) {
  int k = 0;
  int x = 4;
  int y = 4;
  int arr[4][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  scanf("%d", &k);
  if (findNum(arr, &x, &y, k)) {
    printf("%d %d\n", x, y);
  } else {
    printf("找不到\n");
  }
  return 0;
}