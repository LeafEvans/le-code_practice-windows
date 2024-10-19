#include "array.h"

int main(int argc, char* argv[]) {
  Array a(2);
  a.insert(10, 20);
  a.insert(1, 50);
  a.insert(2, 50);
  a.insert(2, 30);

  a.remove_value(30);
  for (uint i = 0; i < a.item_num(); ++i) {
    cout << a.data(i) << " ";
  }
  cout << endl;

  return 0;
}
