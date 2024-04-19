#include <cstddef>
#include <iostream>

using namespace std;

void func(int *p) { cout << "void func(int *p)" << endl; }

void func(int p) { cout << "void func(int p)" << endl; }

int main(int argc, char **argv) {
  func(nullptr);
  return 0;
}
