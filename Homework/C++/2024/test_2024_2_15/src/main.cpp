#include <iostream>

using namespace std;

namespace name_a {
int x = 10;
void func(void) { cout << "name_a" << endl; }
}  // namespace name_a

namespace name_b {
int x = 10;
void func(void) { cout << "name_b" << endl; }
}  // namespace name_b

/* namespace A {
int a = 10;
namespace B {
int a = 20;
}
}  // namespace A */
// 命名空间的嵌套定义



/* void test(void) {
  cout << "A::a : " << A::a << endl;
  cout << "A::B::a :" << A::B::a << endl;
} */

/* int main(void) {
  test();
  return 0;
} */

/* int main(int argc, char** argv) {
  name_a::x = 100;
  name_b::x = 1000;
  cout << name_a::x << endl;
  cout << name_b::x << endl;
  name_a::func();
  name_b::func();
  return 0;
} */
