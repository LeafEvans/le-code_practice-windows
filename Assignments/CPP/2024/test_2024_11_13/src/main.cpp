#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
  cout << "hello world!" << endl;
  int a = 0;
  a = std::clamp(a, -1, 10);
  for (int i = 0; i < 10; ++i) {
    cout << i << ' ';
  }
  return 0;
}
