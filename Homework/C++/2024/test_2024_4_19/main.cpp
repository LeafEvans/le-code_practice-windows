#include <iostream>

using namespace std;

template <typename T>
T myAdd(T a, T b) {
  return a + b;
}

int main() {
  int a = 10;
  int b = 20;
  double da = 1.14;
  double db = 2.14;
  myAdd(a, b);
  myAdd(da, db);
  myAdd(a, a);
  return 0;
}
