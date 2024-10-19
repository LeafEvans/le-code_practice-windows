#define _CRT_SECURE_NO_WARNINGS

#include <cstdbool>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

// #include <iostream>
//
// using namespace std;
//
// namespace student_info_handle {
// int a = 10;
// void func() { cout << "student_info_handle" << endl; }
// }  // namespace student_info_handle
//
// int main(int argc, char **argv) {
//   namespace stuInfoH = student_info_handle;
//   stuInfoH::func();
//   return 0;
// }

// #include <iostream>
//
// int main(int argc, char** argv) {
//   int a = 10;
//   int& p = a;
//   p = 200;
//   std::cout << a << std::endl;
//   return 0;
// }

// #include <iostream>
//
// using namespace std;
// int main(int argc, char** argv) {
//   int a = 10;
//   // 给变量 a 取一个别名 b
//   int& b = a;
//   cout << "a:" << a << endl;
//   cout << "b:" << b << endl;
//   cout << "------------" << endl;
//   // 操作 b 相当于操作 a 本身
//   b = 100;
//   cout << "a:" << a << endl;
//   cout << "b:" << b << endl;
//   int& c = a;
//   c = 200;
//   cout << "a:" << a << endl;
//   cout << "b:" << b << endl;
//   cout << "c:" << c << endl;
//   cout << "------------" << endl;
//   // a, b, c 的地址都是相同的
//   cout << "a:" << &a << endl;
//   cout << "b:" << &b << endl;
//   cout << "c:" << &c << endl;
//   return 0;
// }

// #include <iostream>
//
// int main(int argc, char* argv[]) {
//   std::cout << "Hello World!\n";
//   return 0;
// }

// #include <iostream>
//
// using namespace std;
//
// int main(int argc, char** argv) {
//   int a = 100;
//   int& b = a;
//   int c = 200;
//   cout << b << endl;
//   b = c;
//   // 不是让 b 引用 c，而是将 c 的值赋值给 b，等价于 b = 200，即 a = 200
//   cout << b << endl;
//   cout << a << endl;
//   return 0;
// }

// #include <iostream>
//
// using namespace std;

// int main(int argc, char* argv[]) {
//   // 引用所占内存空间的大小
//   float ch = 'a';
//   float& p = ch;
//   cout << sizeof(p) << endl;
//   // sizeof 并不是在求某个变量的大小，而是求某个数据类型的大小
//   return 0;
// }

// 使用结构体来验证大小，64 位机器，指针大小为 16
// #include <iostream>
//
// using namespace std;
//
// struct test {
//  int& a;  // 8
//  int& b;  // 8
//};         // 16
//
// int main(int argc, char** argv) {
//  cout << sizeof(struct test) << endl;
//  return 0;
//}

// #include <iostream>
//
// using namespace std;
//
// typedef struct Teacher {
//   char name[32];
//   int age;
// } Teacher;
//
// void printfT2(Teacher& t) {
//   cout << t.age << endl;
//   t.age = 32;  // 改变结构体的成员变量
// }
//
// void printfT1(Teacher* const t) {
//   cout << t->age << endl;
//   t->age = 33;
// }  // 功能与 T2 相同
//
// int main(int argc, char** argv) {
//   Teacher teacher = {0};
//   teacher.age = 30;
//   printfT2(teacher);
//   cout << teacher.age << endl;
//   printfT1(&teacher);  // 传递地址
//   cout << teacher.age << endl;
//   return 0;
// }

// void swap1(int& a, int& b) {
//   int t = a;
//   a = b;
//   b = t;
// }
//
// void swap2(int* a, int* b) {
//   int t = *a;
//   *a = *b;
//   *b = t;
// }

// #include <iostream>
//
// using namespace std;
//
// void swap(int& a, int& b) {
//   int temp = a;
//   a = b;
//   b = temp;
// }
//
// void selectionSort(int arr[], int sz) {
//   for (int i = 0; i < sz - 1; ++i) {
//     int min = i;
//     for (int j = i + 1; j < sz; ++j) {
//       if (arr[j] < arr[min]) min = j;
//     }
//     swap(arr[i], arr[min]);
//   }
// }
//
// int main(int argc, char** argv) {
//   int arr[7] = {64, 34, 25, 12, 22, 11, 90};
//   int sz = sizeof(arr) / sizeof(arr[0]);
//   for (int i = 0; i < sz; ++i) {
//     cout << arr[i] << " ";
//   }
//   cout << endl;
//   selectionSort(arr, sz);
//   for (int i = 0; i < sz; ++i) {
//     cout << arr[i] << " ";
//   }
//   cout << endl;
//   return 0;
// }

// #define ADD(x, y) x + y
//
// int main(int argc, char** argv) {
//   int ret1 = ADD(10, 20) * 10;
//   cout << "ret1: " << ret1 << endl;
//   return 0;
// }

// #define Max(a, b) (a) > (b) ? (a) : (b)
//
// int main(int argc, char** argv) {
//   int ret;
//   ret = Max(10, 20);
//   cout << ret << endl;
//   return 0;
// }

// class Teacher {
//  public:
//   char name[32];
//
//   void set_age(int age) {
//     // 设置 _age 属性
//     if (age > 200 || age < 0) {
//       // 阈值判断，函数形参的合法性检查
//       cout << "age error" << endl;
//       return;
//     }
//     cout << "void set_age(int age)" << endl;
//     _age = age;  // 在类的内部访问 private 成员
//   }
//
//   int get_age(void) { return _age; }
//
//  private:
//   int _age;
//   char _sex;
// };
//
// int main(int argc, char** argv) {
//   Teacher t;
//   strcpy(t.name, "list");
//   cout << t.name << endl;
//   return EXIT_SUCCESS;
// }

// class Box {
//  public:
//   Box(void) {
//     _length = 10;
//     _width = 10;
//     _height = 10;
//   }

//  int get_length(void) { return _length; }
//  int get_width(void) { return _width; }
//  int get_height(void) { return _height; }

// private:
//  int _length;
//  int _width;
//  int _height;
//};

// class Box {
//  public:
//   Box(int length, int width, int height)
//       : _length(length), _width(width), _height(height), p(_length) {
//     // 等价于：
//     // _length = length;
//     // _width = width;
//     // _height height;
//     // 但是不能 p = _length;
//     // 因为引用在定义的时候就要初始化，而是对引用的对象进行赋值
//     cout << "Box(int length, int width, int height);" << endl;
//   }
//
//   int get_length(void) { return _length; }
//   int get_width(void) { return _width; }
//   int get_height(void) { return _height; }
//
//  private:
//   int _length;
//   int _width;
//   int _height;
//   int& p;
// };
//
// class Test {
//  public:
//   Test(int num) : _num(num){};
//
//  private:
//   const int _num;
// };
//
// int main(void) {
//   // 实例化一个对象
//   Box box(10, 200, 30);
//
//   cout << box.get_length() << endl;
//   cout << box.get_width() << endl;
//   cout << box.get_height() << endl;
//   return EXIT_SUCCESS;
// }

// int main(int argc, char **argv) {
//   Box c();
//   // 不是实例化一个对象，而是声明一个函数，返回值为 Box
//   // 函数的名字叫做 c，函数的形参列表为空
//   return EXIT_SUCCESS;
// }

// class A {
//  public:
//   int x;
//   A(int a) { x = a; }
//   // 没有实现无参的构造函数
// };
//
// class B {
//  public:
//   B(int num) : _a(num) { cout << "B(int num);" << endl; }
//   // 使用初始化成员列表就可以使用有参构造函数
//   // 就可以避免使用无参构造函数
//  private:
//   A _a;
//   // 在初始化的时候，没有无参的构造函数
//   // 即无法调用 A::A()
//   // 无法在 B 中实例化一个对象
// };

