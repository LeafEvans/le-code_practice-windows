#include <iostream>

#include "SimpleCircleList.h"

using namespace std;

void Josephus(int n, int m) {
  SimpleCircleList<int> scl;

  int nOut, nWiner = 0;

  for (int i = 0; i < n; ++i) {
    scl.Insert(i, i + 1);
  }

  scl.Head();

  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < m; ++j) {
      int nData;
      scl.Next(nData);
    }
    scl.DeleteCur(nOut);
    cout << nOut << ' ';
  }
  scl.GetElem(0, nWiner);
  cout << endl << "优胜者：" << nWiner << endl;
}

int main() {
  Josephus(3, 8);
  return 0;
}