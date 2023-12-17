// 杨式矩阵
// 1 2 3 
// 4 5 6
// 7 8 9

#include <stdio.h>

struct Point {
  int x;
  int y;
};

struct Point findNum(int arr[3][3], int row, int col, int k) {
  int x = 0;
  int y = col - 1;
  struct Point p = {-1, 1};

  while (x < row && y >= 0) {
    if (k < arr[x][y]) {
      y--;  // 必定不在最后一列
    } else if (k > arr[x][y]) {
      x++;  // 必定不在这一行
    } else {
      p.x = x;
      p.y = y;
      return p;
    }
  }
  return p;
}

int main(void) {
  int arr[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int k = 0;
  scanf("%d", &k);
  struct Point ret = findNum(arr, 3, 3, k);
  printf("%d %d", ret.x, ret.y);
  return 0;
}