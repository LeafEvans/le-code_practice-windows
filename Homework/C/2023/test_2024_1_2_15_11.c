#include <stdio.h>

#define ARRAY_SIZE 16

void fillArray(int arr[ARRAY_SIZE][ARRAY_SIZE], int n) {
  // 可以想象一圈一圈进行填充，然后填到中心
  int num = 1;
  int top_row = 0;         // 定义顶部坐标
  int bottom_row = n - 1;  // 定义底部坐标
  int left_col = 0;        // 定义左侧坐标
  int right_col = n - 1;   // 定义右侧坐标

  while (top_row <= bottom_row && left_col <= right_col)
  // 当满足顶部坐标小于底部坐标，左侧坐标小于右侧坐标，就进行循环
  {
    // 在每次循环中，前两个循环是必定执行的
    for (int i = left_col; i <= right_col; ++i, ++num) {
      arr[top_row][i] = num;
    }
    ++top_row;

    for (int j = top_row; j <= bottom_row; ++j, ++num) {
      arr[j][right_col] = num;
    }
    --right_col;

    // 上面那个++后，这里就要进行判断
    if (top_row <= bottom_row) {
      for (int i = right_col; i >= left_col; --i, ++num) {
        arr[bottom_row][i] = num;
      }
      --bottom_row;
    }

    // 上面那个--后，这里就要进行判断
    if (left_col <= right_col) {
      for (int j = bottom_row; j >= top_row; --j, ++num) {
        arr[j][left_col] = num;
      }
      ++left_col;
    }
  }
}

int main(void) {
  int n = 0;
  int arr[ARRAY_SIZE][ARRAY_SIZE] = {0};

  scanf("%d", &n);
  fillArray(arr, n);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      printf("%-5d", arr[i][j]);
    }
    printf("\n");
  }

  return 0;
}