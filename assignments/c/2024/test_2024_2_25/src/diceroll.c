#include "../inc/diceroll.h"

#include <stdio.h>
#include <stdlib.h>

// 进行初始化
int roll_count = 0;

// 定义为这个文件私有
// 只有 roll_n_dice 可以使用
// 类似类的私有成员函数
static int rollem(int sides) {
  // 生成的点数
  int roll;
  // 随机数生成
  roll = rand() % sides + 1;
  // 返回
  return roll;
}

int roll_n_dice(int dice, int sides) {
  // 循环变量，代表次数
  int d;
  // 总的点数
  int total = 0;
  // 如果面数小于 2
  if (sides < 2) {
    // 提示语句
    printf("Need at least 2 sides.\n");
    return -2;
  }
  // 如果次数小于 1
  if (dice < 1) {
    printf("Need at least 1 die.\n");
    return -1;
  }
  // 开始循环
  for (d = 0; d < dice; ++d) {
    total += rollem(sides);
  }
  // 返回循环后的值
  return total;
}