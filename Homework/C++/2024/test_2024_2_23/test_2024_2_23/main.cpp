// #include <iostream>
//
// void swap(int& a, int& b) {
//   int temp = a;
//   a = b;
//   b = temp;
// }
//
// void bubbleSort(int arr[], int size) {
//   for (int i = 0; i < size - 1; ++i) {
//     for (int j = 0; j < size - 1 - i; ++j) {
//       if (arr[j] > arr[j + 1]) {
//         swap(arr[j], arr[j + 1]);
//       }
//     }
//   }
// }
//
// void insertionSort(int arr[], int size) {
//   int i, j;
//   for (i = 1; i < size; ++i) {
//     int key = arr[i];
//     for (j = i - 1; j >= 0 && arr[j] > key; --j) {
//       arr[j + 1] = arr[j];
//     }
//     arr[j + 1] = key;
//   }
// }
//
// void selectionSort(int arr[], int size) {
//   for (int i = 0; i < size - 1; ++i) {
//     int min = i;
//     for (int j = i + 1; j < size; ++j) {
//       if (arr[j] < arr[min]) {
//         min = j;
//       }
//     }
//     swap(arr[i], arr[min]);
//   }
// }
//
// int main(void) {
//   int arr[10] = {1, 23, 4, 25, 89, 5, 23, 90, 44, 27};
//   selectionSort(arr, 10);
//   for (int i = 0; i < 10; ++i) {
//     std::cout << arr[i] << " ";
//   }
//   std::cout << std::endl;
//   return 0;
// }

// #include <iostream>
//
// using namespace std;
//
// int main(void) {
//   cout << "Hello World!" << endl;
//   return 0;
// }

// #include <iostream>
//
// using namespace std;
//
// class C1 {
//  public:
//   int i;
//   int j;
//   int k;
// };
//
// class C2 {
//  public:
//   int i;
//   int j;
//   int k;
//
//  public:
//   // int getK(C2 *const this) { return this->k; }
//   // this 指针指向调用该成员函数的对象
//   int getK() { return k; }
//   void setK(int val) { k = val; }
// };
//
// class ABC {
//  public:
//   int x, y, z;
//   ABC(int x, int y, int z) {
//     this->x = x;
//     this->y = y;
//     this->z = z;
//   }
// };
//
// ABC a(1, 2, 3);  // ABC(&a, 1, 2, 3);
// ABC b(1, 2, 3);  // ABC(&b, 1, 2, 3);
//
// int main(void) {
//   C2 c2, c3;
//
//   c2.k = 100;
//   c2.getK();  // 等价于 getK(C2 *const c2);
//   c3.getK();  // 这样函数就知道是哪个对象调用它的
//   c2.setK(100);
//
//   return 0;
// }

// #include <iostream>
//
// using namespace std;
//
// class Sheep {
//  public:
//   char name[32];
//   int age;
//   Sheep(void) {
//     cout << "Sheep();" << endl;
//     count++;
//   }
//   ~Sheep() { count--; }
//   static int count;  // 只是声明声明了一个静态的成员变量
// };
//
//// 定义了 Sheep 这个类中的静态成员变量 count，
//// 并且初始化为 0（如果不初始化，默认为0）
// int Sheep::count = 0;
//
// int main(void) {
//   // 构造了 10 个 Sheep 对象
//   Sheep *p = new Sheep[10];
//   Sheep s1;
//   Sheep s2;
//   cout << sizeof(s2) << endl;
//   // 静态成员变量共享
//   cout << Sheep::count << endl;
//   cout << s1.count << endl;
//   cout << s2.count << endl;
//
//   return 0;
// }

// #include <iostream>
//
// using namespace std;
//
// class Sheep {
//  public:
//   char name[32];
//   int age;
//
//   Sheep() { count++; }
//   ~Sheep() { count--; }
//
//   static int sheep_num(void) { return count; }
//
//  private:
//   static int count;
// };
//
// int Sheep::count = 0;
//
// int main(void) {
//   Sheep *p = new Sheep[10];
//   cout << Sheep::sheep_num() << endl;
//   cout << p->sheep_num() << endl;
//   return 0;
// }

// class Math {
//  public:
//   static void sin() {}
//   static void cos() {}
//   static void tan() {}
//   static void cot() {}
// };
//
// class SortAlgrihm {
//
// };
//
// class SearthAlgrihm {
//
// };
//
// int main(void) {
//   Math::sin();
//   return 0;
// }

// #include <iostream>
// #include <string>
//
// int main(void) {
//   return 0;
// }

// #define _CRT_SECURE_NO_WARNINGS
//
// #include <cstring>
// #include <iostream>
//
// using namespace std;
//
// int main(void) {
//   const char *sep = "@.";
//   char email[] = "leafevans@foxmail.com";
//   char cp[30] = {0};
//   strcpy(cp, email);
//
//   char *ret = NULL;
//   for (ret = strtok(cp, sep); ret != NULL; ret = strtok(NULL, sep)) {
//     cout << ret << endl;
//   }
//
//   return 0;
// }

#include <iostream>

using namespace std;

int main(void) {
  ;
  return 0;
}