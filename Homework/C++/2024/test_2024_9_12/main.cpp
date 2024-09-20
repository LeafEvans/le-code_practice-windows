#include <iostream>
#include "SqList.h"
#include "SimpleCircleList.h"

using namespace std;

bool printList(const int &elem) {
  printf("%d ", elem);
  return true;
}

void Josephus(int n, int m) {
  SimpleCircleList<int> la;
  int out, winner;
  for (int k = 0; k < n; ++k) {
    la.insert(k, k + 1);
  }
  cout << "出列者: ";
  la.toHead();

  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < m; ++j) {
      int data;
      la.toNext(data);
    }
    la.delCurr(out);
    cout << out << ' ';
  }
  la.getElem(0, winner);
  cout << endl << "优胜者: " << winner << endl;
}

int main() {
  Josephus(2, 3);
  return 0;
}
