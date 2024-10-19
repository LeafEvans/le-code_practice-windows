#include <iostream>

#include "simple_circle_list.h"

using namespace std;

static void Josephus(int n, int m) {
  SimpleCircleList<int> scl;  // 定义空循环链表
  int nOut, nWiner = 0;

  for (int i = 0; i < n; ++i) {
    scl.Insert(i, i + 1);  // 建立数据为 1, 2,..., n 的循环链表
  }

  scl.Head();  // 让当前节点返回头节点

  for (int i = 0; i < n - 1; ++i) {
    // 循环 n - 1 次，让 n - 1 个人出列
    for (int j = 0; j < m; ++j) {
      // 报数 m 次
      int nData;
      scl.Next(nData);
    }
    // 删除当前节点
    scl.DeleteCur(nOut);
    cout << nOut << endl;
  }

  // 得到这个元素
  scl.GetElem(0, nWiner);
  cout << endl << "优胜者: " << nWiner << endl;
}

int main() {
  Josephus(3, 8);
  return 0;
}