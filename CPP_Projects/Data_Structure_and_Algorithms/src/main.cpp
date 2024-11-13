#include <iostream>
#include <algorithm>

#include "char_string.h"

using namespace std;

int main() {
  CharString a = "ABACD";
  CharString b = "ABA";
  cout << a.Index(b, 0) << endl;
  return 0;
}
