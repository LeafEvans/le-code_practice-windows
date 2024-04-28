// #include <iostream>
// #include <vector>
//
// using namespace std;
//
// static int func(int a, int b) {
//   if (b) {
//     return a / b;
//   } else {
//     cout << "division 0" << endl;
//     throw "error, hello world";
//   }
// }
//
// int main() {
//   try {
//     int ret = func(10, 0);
//     cout << "end..." << endl;
//   } catch (const char *msg) {
//     cout << "err!" << endl;
//     cout << msg << endl;
//   }
//
//   return 0;
// }
// #include <cstring>
// #include <iostream>
//
// using namespace std;
//
// bool func(const char* str) {
//  if (!str) {
//    throw "NULL pointer!";
//  }
//
//  int len = strlen(str);
//
//  if (!(str[0] == '#' && str[1] == '#')) {
//    throw "Frame header error.";
//  }
//  if (!(str[len - 1] == '#' && str[len - 2] == '#')) {
//    throw "Frame tail error.";
//  }
//
//  return true;
//}
//
// int main() {
//  try {
//    func("Hello World!");
//  } catch (const char* msg) {
//    cout << msg << endl;
//  }
//  return 0;
//}
// #include <iostream>
// #include <vector>
//
// using namespace std;
//
// int main() {
//  try {
//    vector<int> arr(3, 10);
//    for (int i = 0; i < 3; ++i) {
//      cout << arr.at(i) << endl;
//    }
//  } catch (out_of_range &err) {
//    cout << err.what() << endl;
//  }
//}
// #include <cstring>
// #include <exception>
// #include <iostream>
//
// class FHeaderErr : public std::exception {
// public:
//  const char* what() const throw() { return "frame header error"; }
//};
//
// class FTailErr : public std::exception {
// public:
//  const char* what() const throw() { return "frame tail error"; }
//};
//
// bool func(const char* str) {
//  if (!str) {
//    throw "NULL pointer";
//  }
//
//  int len = strlen(str);
//
//  if (!(str[0] == '#' && str[1] == '#')) {
//    FHeaderErr err;
//    throw(err);
//  }
//
//  if (!(str[len - 1] == '#' && str[len - 2] == '#')) {
//    FTailErr err;
//    throw(err);
//  }
//
//  return true;
//}
//
// int main() {
//  try {
//    func("Hello World!");
//  } catch (FHeaderErr& err) {
//    std::cout << err.what() << std::endl;
//  }
//  return 0;
//}
// #include <iostream>
//
// #include "test.h"
//
// using namespace std;
//
// int main() {
//  cout << add(2, 3) << endl;
//  return 0;
//}
// #include <cmath>
// #include <ctime>
// #include <iostream>
//
// using namespace std;
//// 函数声明
// bool prime(int x);
// int inverse(int m);
//
// int main() {
//   int n, z;
//   cout << "2023116204 陈靖盈" << endl;
//   cout << "你好，C++" << endl;
//   cout << "请输入数据个数: ";
//   cin >> n;
//   cout << "随机产生的" << n << "个数中的可逆素数有: " << endl;
//   // 以时间戳作为种子，传入空指针，便于随机数的生成
//   srand(time(nullptr));
//   for (int i = 0; i < n; i++) {
//     // 随机生成 [10, 500]
//     z = 10 + rand() % 491;
//     // 如果为素数，判断逆序数是否为素数
//     if (prime(z) && prime(inverse(z))) {
//       cout << z << endl;
//     }
//   }
//   return 0;
// }
//
//// 反序数
// int inverse(int m) {
//   // 返回的新的反序数
//   int t = 0;
//   // 当这个 m 大于 0 时，进行循环
//   while (m > 0) {
//     /*
//      * example:
//      * 求 124 的反序数；
//      * loop 1
//      * (t = t * 10 + m % 10) -> (t = 0 * 10 + 124 % 10) -> (t = 4)
//      * (m /= 10) -> (m = 124 / 10) -> (m = 12)
//      * loop 2
//      * (t = 4 * 10 + 12 % 10) -> (t = 42)
//      * m = 1
//      * loop 3
//      * (t = 42 * 10 + 1 % 10) -> (t = 421)
//      * m = 0 (跳出循环)
//      */
//     t = t * 10 + m % 10;
//     m /= 10;
//   }
//   // 返回
//   return t;
// }
//
//// 判断是否为素数
// bool prime(int x) {
//   // 从二开始遍历
//   // 如果在 √x 之前都没找到，那之后肯定找不到除数
//   // 如 8 = 2 * 4，而 √8 = 2√2
//   // 必有一个因子小于平方根
//   for (int i = 2; i < sqrt(x); ++i) {
//     // 如果余数为 0，说明整除
//     // 不为素数
//     if (x % i == 0) {
//       return false;
//     }
//   }
//   // 没找到因子，说明为素数
//   return true;
// }
// #define _CRT_SECURE_NO_WARNINGS
//
// #include <cstring>
// #include <iostream>
//
// using namespace std;
//
// class Staff {
// public:
//  Staff(int num, const char* name, double rate_of_attend, double basic_sal,
//        double prize)
//      : _num(num),
//        _rate_of_attend(rate_of_attend),
//        _basic_sal(basic_sal),
//        _prize(prize) {
//    strcpy(_name, name);
//  }
//
//  void output() const {
//    cout << "Num: " << _num << endl;
//    cout << "Name: " << _name << endl;
//    cout << "Rate of Attend :" << _rate_of_attend << endl;
//    cout << "Basic Sal: " << _basic_sal << endl;
//    cout << "Prize: " << _prize << endl;
//  }
//
//  void outputWage() const {
//    cout << "Wage: " << _basic_sal + _prize * _rate_of_attend << endl;
//  }
//
//  double getRateOfAttend() const { return _rate_of_attend; }
//
//  double getBasicSal() const { return _basic_sal; }
//
//  double getPrize() const { return _prize; }
//
// private:
//  int _num;
//  char _name[50];
//  double _rate_of_attend;
//  double _basic_sal;
//  double _prize;
//};
//
// class Saleman : virtual public Staff {
// public:
//  Saleman(int num, const char* name, double rate_of_attend, double basic_sal,
//          double prize, double person_amount, double deduct_rate)
//      : Staff(num, name, rate_of_attend, basic_sal, prize),
//        _person_amount(person_amount),
//        _deduct_rate(deduct_rate) {}
//
//  void output() const {
//    Staff::output();
//    cout << "Person Amount: " << _person_amount << endl;
//    cout << "Deduct Rate: " << _deduct_rate << endl;
//  }
//
//  void outputWage() const {
//    cout << "Wage: "
//         << getBasicSal() + getPrize() * getRateOfAttend() +
//                _deduct_rate * _person_amount
//         << endl;
//  }
//
//  double getPersonAmount() const { return _person_amount; }
//
//  double getDeductRate() const { return _deduct_rate; }
//
// private:
//  double _person_amount;
//  double _deduct_rate;
//};
//
// class Manager : virtual public Staff {
// public:
//  Manager(int num, const char* name, double rate_of_attend, double basic_sal,
//          double prize, double total_amount, double total_deduct_rate)
//      : Staff(num, name, rate_of_attend, basic_sal, prize),
//        _total_amount(total_amount),
//        _total_deduct_rate(total_deduct_rate) {}
//
//  void output() const {
//    Staff::output();
//    cout << "Total Amount: " << _total_amount << endl;
//    cout << "Total Deduct Rate: " << _total_deduct_rate << endl;
//  }
//
//  void outputWage() const {
//    cout << "Wage: "
//         << getBasicSal() + getPrize() * getRateOfAttend() +
//                _total_deduct_rate * _total_amount
//         << endl;
//  }
//
//  double getTotalAmount() const { return _total_amount; }
//
//  double getTotalDeductRate() const { return _total_deduct_rate; }
//
// private:
//  double _total_amount;
//  double _total_deduct_rate;
//};
//
// class SaleManager : public Saleman, public Manager {
// public:
//  SaleManager(int num, const char* name, double rate_of_attend,
//              double basic_sal, double prize, double person_amount,
//              double deduct_rate, double total_amount, double
//              total_deduct_rate)
//      : Saleman(num, name, rate_of_attend, basic_sal, prize, person_amount,
//                deduct_rate),
//        Manager(num, name, rate_of_attend, basic_sal, prize, total_amount,
//                total_deduct_rate),
//        Staff(num, name, rate_of_attend, basic_sal, prize) {}
//
//  void output() const {
//    Saleman::output();
//    cout << "Total Amount: " << getTotalAmount() << endl;
//    cout << "Total Deduct Rate: " << getTotalDeductRate() << endl;
//  }
//
//  void outputWage() const {
//    cout << "Wage: "
//         << getBasicSal() + getDeductRate() * getPersonAmount() +
//                getTotalDeductRate() * getTotalAmount()
//         << endl;
//  }
//};
//
// int main() {
//  SaleManager sale_manager(1, "John Doe", 0.95, 1000, 500, 10, 0.1, 10000,
//                           0.05);
//  sale_manager.output();
//  sale_manager.outputWage();
//  return 0;
//}
// #define _CRT_SECURE_NO_WARNINGS
// #include <iostream>
//
// using namespace std;
//
// template <typename T>
// void mySwap(T& a, T& b) {
//  T temp = a;
//  a = b;
//  b = temp;
//}
//
// void test01() {
//  int a = 10;
//  int b = 20;
//
//  // 1. 自动类型推导
//  cout << "a: " << a << " b: " << b << endl;
//  mySwap(a, b);
//  cout << "a: " << a << " b: " << b << endl;
//
//  double da = 1.2;
//  double db = .343;
//
//  cout << "da: " << da << " db: " << db << endl;
//  mySwap(da, db);
//  cout << "da: " << da << " db: " << db << endl;
//
//  // 2. 显示指定类型
//  mySwap<int>(a, b);
//}
//
// int main() {
//  test01();
//  return 0;
//}
// #include <iostream>
//
// using namespace std;
//
//// 模板函数不行
// template <class T>
// int myAdd(T a, T b) {
//   return a + b;
// }
//
//// 普通函数可以进行自动类型转换
// int myAdd(int a, char c) { return a + c; }
//
// void test02() {
//   int a = 10;
//   int b = 20;
//   char c1 = 'a';
//   char c2 = 'b';
//
//   // 优先执行下面的那个函数
//   // 因为优先使用普通的
//   myAdd(a, c1);
//   // 执行上面的那个函数
//   myAdd(a, b);
//
//   // 调用下面的
//   // 因为模板不会对类型进行自动类型转换
//   myAdd(c1, b);
// }
//
// template <typename T>
// void print(T a) {
//   cout << a << endl;
// }
//
// template <typename T>
// void print(T a, T b) {
//   cout << a << endl;
//   cout << b << endl;
// }
//
// int main() {
//   test02();
//   return 0;
// }
// using namespace std;
// #d efine MAX(T) \
//  T max_##T(T x, T y) { return x > y ? x : y; }
//
//// int max_int(int x, int y) { return x > y ? x : y; }
// MAX(int)
//// double max_double(double x, double y) { ... }
// MAX(double)
//// string max_string(string x, string y) { ... }
// MAX(string)
//
// #define Max(T) max_##T
//
// int main() {
//   int nx = 10, ny = 20;
//   cout << Max(int)(nx, ny) << endl;
//   double dx = 12.3, dy = 45.6;
//   cout << Max(double)(dx, dy) << endl;
//   string sx = "world", sy = "hello";
//   cout << Max(string)(sx, sy) << endl;
//
//   char cx[256] = "world", cy[256] = "hello";
//   cout << Max(string)(cx, cy);
//   return 0;
// }
// #include <iomanip>
// #include <iostream>
// using namespace std;
// int main() {
//  cout << "你好，C++" << endl;
//  cout << "2023116204陈靖盈" << endl;
//  int b, sum1 = 0, n, i;
//  int a[50];
//  double c, d, sum3 = 0.0, sum4 = 0.0, sum2 = 0.0;
//  srand(time(NULL));
//  cout << "请输入一维数组元素的个数（n<=50）：";
//  cin >> n;
//  for (i = 0; i < n; i++) {
//    a[i] = 1 + rand() % 100;
//    cout << setw(5) << a[i];
//    cout << endl;
//  }
//  for (i = 0; i < n; i++) {
//    if (a[i] % 2 == 0) {
//      sum1++;
//      sum2 = sum2 + a[i];
//    } else {
//      sum3++;
//      sum4 = sum4 + a[i];
//    }
//  }
//  c = sum2 / sum1;
//  d = sum4 / sum3;
//  cout << "偶数个数为" << setw(4) << sum1 << "个,其平均数为" << c << endl;
//  cout << "奇数个数为" << setw(4) << sum3 << "个,其平均数为" << d << endl;
//  return 0;
//}
#include <iostream>

using namespace std;

template <class T>
void my_swap(T &a, T &b) {
  const T temp = a;
  a = b;
  b = temp;
}

template <class T>
void bubble_sort(T *arr, const int len) {
  for (int i = 0; i < len - 1; ++i) {
    for (int j = 0; j < len - 1 - i; ++j) {
      if (arr[j] > arr[j + 1]) {
        my_swap(arr[j], arr[j + 1]);
      }
    }
  }
}

template <class T>
void print_arr(const T* arr, const int len) {
  for (int i = 0; i < len; ++i) {
    cout << arr[i] << " ";
  }
}

int main() {
  constexpr int sa = 10;
  cout << sa << '\n';
  int arr2[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  cout << "Hello World!\n";
  int arr1[10] = {231, 23, 3321, 23, 32, 11, 23, 231, 32, 23};
  print_arr(arr1, sizeof(arr1) / sizeof(int));
  cout << "\n";
  bubble_sort(arr1, sizeof(arr1) / sizeof(int));
  print_arr(arr1, sizeof(arr1) / sizeof(int));
  cout << "\n";
  return 0;
}