#include <iostream>

#include "array.hpp"

using namespace std;

int main(int argc, char** argv) {
  Array a;
  a.insert(1, 20);
  a.insert(2, 20);
  a.insert(3, 20);
  a.insert(4,10);
  a.remove_data(20);

  for (int i = 0; i < a.item_num(); ++i) {
    cout << a.get_data(i) << " ";
  }
  cout << endl;

  return 0;
}
