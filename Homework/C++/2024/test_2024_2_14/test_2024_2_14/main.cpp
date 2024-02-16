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


