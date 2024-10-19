#include <string>

#include "../inc/Person.h"

using namespace std;

int main() {
  Person<string> person("Alice", "12313412");
  cout << person << endl;
  return 0;
}
