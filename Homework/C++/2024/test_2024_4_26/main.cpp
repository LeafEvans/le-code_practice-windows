/* #include <iostream>

using namespace std;

template <class T>
void mySwap(T &a, T &b) {
  const T temp = a;
  a = b;
  b = temp;
}

template <typename T>
void bubbleSort(T *arr, int len) {
  for (int i = 0; i < len - 1; ++i) {
    for (int j = 0; j < len - 1 - i; ++j) {
      if (arr[j + 1] > arr[j]) mySwap(arr[j + 1], arr[j]);
    }
  }
}

template <typename T>
void printArr(T *arr, int len) {
  for (int i = 0; i < len; ++i) {
    cout << arr[i] << ' ';
  }
  cout << '\n';
}

int main() {
  int arr[10] = {1, 32, 44, 2, 11, 222, 332, 2312, 78, 10};
  printArr(arr, 10);
  bubbleSort(arr, 10);
  printArr(arr, 10);
  return 0;
} */
#include <iostream>

#include "test.h"

using namespace std;

template <class T = short, class D = int>
class CMath {
 public:
  void print() {
    cout << "m_t: " << typeid(m_t).name() << ", "
         << "m_d: " << typeid(m_d).name() << '\n';
  }

 private:
  T m_t;
  D m_d;
};

int main() {
  cout << "Hello World!\n";
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      cout << add(i, j) << ' ';
    }
    cout << '\n';
  }
  return 0;
}
