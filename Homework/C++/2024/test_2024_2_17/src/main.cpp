/* int main(int argc, char** argv) {
  cout << "hello world!" << endl;
  return 0;
} */

/* inline int func(int x, int y) { return x + y; }

int main(int argc, char** argv) {
  cout << func(10, 30) * 10 << endl;
  return 0;
} */

/* void testFunc(int a = 10, int b = 20) { cout << "a + b = " << a + b << endl;
}

int main(int argc, char** argv) {
  testFunc();          // 什么参数都没有传
  testFunc(100);       // 只传了 a 参数
  testFunc(100, 200);  // 两个参数都传了
  return EXIT_SUCCESS;
} */

/* float func1(float r, float pi = 3.14) { return pi * r * r; }

// 声明一个带缺省参数的函数
float func2(float r, float pi = 3.14);
// 如果带默认参数的函数被声明了，实现的时候不需要默认参数
float func2(int r, float pi) { return pi * r * r; }
int main(int argc, char** argv) {
  cout << func1(1.45, 3.1415926) << endl;
  return EXIT_SUCCESS;
} */

/* void func(void) {}
void func(int x) {}
void func(char x) {}
void func(int x, int y) {}
void func(int x, char y) {}
void func(char y, int x) {} */

/* namespace name_b {
void func(void) {}
void func(char x) {}
}  // namespace name_b

namespace name_a {
void func(void) { cout << "void func(int x)" << endl; }
void func(char x) { cout << "void func(int x)" << endl; }
void func(int x, char y) { cout << "void func(int x, char y)" << endl; }
void func(char x, int y) { cout << "void func(char x, int y)" << endl; }
}  // namespace name_a

int main(void) {
  name_a::func();
  name_a::func('c', 20);
  name_a::func('H');
  name_a::func(20, 'H');
  return 0;
} */

/* typedef struct Teacher {
  char name[32];
  int age;
} Teacher;

void sort(int *a) {
  // ...
}

void sort(char *a) {
  // ...
}

void sort(Teacher *a) {
  // ...
}

int main(void) {
  // 根据不同的参数，调用不同的函数进行排序
  int a[10];
  sort(a);
  char b[10];
  sort(b);
  Teacher c[10];
  sort(c);
  return EXIT_SUCCESS;
} */

/* class CAnimal {
 public:
  // 属性
  char name[32];  // 名字
  int age;        // 年龄
  // 方法
  void cry(const char *voice) { cout << name << ":" << voice << endl; }
  // 描述动物叫的行为，voice 为叫的声音
};

int main(int argc, char *argv[]) {
  CAnimal cat;
  memset(cat.name, 0, sizeof(cat.name));
  strcpy(cat.name, "Judy");
  cat.cry("Meow~~");
  cout << cat.name << endl;
  return EXIT_SUCCESS;
} */

/* class Test {
 public:
  void func() {
    f1();
    f2();
    f3();
  }

 private:
  // 隐藏实现细节，这些函数外部访问不到
  void f1() {}
  void f2() {}
  void f3() {}
}; */

#include <cstdlib>
#include <iostream>

#include "box.hpp"

using namespace std;

int main(int argc, char **argv) {
  Box b;

  b.set_length(10);
  b.set_width(20);
  b.set_height(30);

  cout << b.get_area() << endl;
  cout << b.get_volumn() << endl;

  return EXIT_SUCCESS;
}




