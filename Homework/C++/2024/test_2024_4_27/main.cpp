/*
#include <iostream>

using namespace std;

template<class T>
void mySwap(T &a, T &b) {
  const T temp = a;
  a = b;
  b = temp;
}

template<class T>
void bubbleSort(T *arr, const int len) {
  for (int i = 0; i < len - 1; ++i) {
    for (int j = 0; j < len - 1 - i; ++j) {
      if (arr[j] > arr[j + 1]) mySwap(arr[j], arr[j + 1]);
    }
  }
}

template<typename T>
void printArr(T *arr, const int len) {
  for (int i = 0; i < len; ++i) {
    cout << arr[i] << ' ';
  }
  cout << endl;
}

template<typename T>
T Max(T x, T y) {
  return x > y ? x : y;
}

int main() {
  int arr[10] = {1, 2, 34, 5, 45, 65, 89, 90, 23, 45};
  printArr<int>(arr, 10);
  bubbleSort<int>(arr, 10);
  printArr<int>(arr, 10);
  return 0;
}
*/
/*
#include <iostream>

using namespace std;

class Integer {
 public:
  Integer(int i) : _i(i) {}

  bool operator>(const Integer &other) {
    return this->_i > other._i;
  }

  friend ostream &operator<<(ostream &os, const Integer &other) {
    os << other.get_i();
    return os;
  }

  int get_i() const { return _i; }

 private:
  int _i;
};

template<class T>
T Max(T x, T y) { return x > y ? x : y; }

int main() {
  int nx = 10, ny = 20;
  cout << Max<int>(nx, ny) << '\n';
  double dx = 12.3, dy = 45.6;
  cout << Max<double>(dx, dy) << '\n';
  string sx = "world", sy = "hello";
  cout << Max<string>(sx, sy) << '\n';
  Integer ix = 10, iy = 30;
  cout << Max<Integer>(ix, iy) << '\n';
  return 0;
}
*/
/*#include <iostream>

using namespace std;

class A {
 public:
  void func() {
    cout << "A::func()\n";
  }
};

template<class T>
void foo() {
  T t;
  t.fun();
}

int main() {
  return 0;
}*/
/*#include <iostream>

using namespace std;

class A {
 public:
  void func() {
    cout << "A::func()\n";
  }
};

template<class T>
void foo() {
  A a;
  a.func();
  T t;
  t.func();
}

template<class T>
void selectionSwap(T *arr, int len) {
  for (int i = 0; i < len - 1; ++i) {
    int max_index = i;
    for (int j = i + 1; j < len; ++j) {
      if (arr[j] > max_index) max_index = j;
    }
    swap(arr[i], arr[max_index]);
  }
}

int main() {
  foo<A>();
  int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 10};
  selectionSwap(arr, 10);
  for (const int item : arr) {
    cout << item << ' ';
  }
  cout << '\n';
  return 0;
}*/
/*#include <iostream>
using namespace std;

template<class T, class U>
U Hum(T x) {
  U u = x;
  return u;
}
int main() {
  int nx = 10;
  cout << Hum<int, int>(nx);
  return 0;
}*/
/*#include <cstring>
#include <iostream>
using namespace std;

int func() {
  int x = 10;
  return x;
}

class Test {
public:
  int data;  // 数据
  char *str; // 字符串

  // 构造函数
  Test() : data(0), str(new char[10]) { cout << "Test()\n"; }

  // 拷贝构造函数
  Test(const Test &other) {
    cout << "Test(const Test &other)\n";
    // 数据段复制进去
    data = other.data;
    // 先判断字符串是否为空
    if (strlen(other.str)) {
      str = new char[strlen(other.str)];
      strcpy(str, other.str);
    } else {
      str = new char[strlen(other.str)];
    }
  }

  Test(int data, const char *src) {
    // 构造函数
    this->data = data;
    if (src && strlen(src)) {
      str = new char[strlen(src) + 1];
      strcpy(str, src);
    }
  }

  // 析构函数
  ~Test() {
    if (str)
      delete[] str;
  }

  // 重载加号运算符
  Test operator+(Test &other) {
    cout << "Test operator+(Test &other)\n";
    Test val;
    val.data = data + other.data;
    val.str = new char[strlen(str) + strlen(other.str) + 1];
    strcpy(val.str, str);
    strcat(val.str, other.str);
    return val;
  }

  bool operator>(const Test &other) {
    cout << "bool operator>(const Test &t)" << endl;
    if (strcmp(str, other.str) > 0) {
      return true;
    } else {
      return false;
    }
  }

  Test &operator++() {
    cout << "Test &operator++()\n";
    ++data;
    return *this;
  }

  Test operator++(int) {
    cout << "Test operator++(int)\n";
    Test temp = *this;
    ++data;
    return temp;
  }

  friend ostream &operator<<(ostream &os, const Test &self) {
    os << self.data << '\n';
    os << self.str << '\n';
    return os;
  }
};*/
/*
#include <iostream>

using namespace std;

template<class T>
class CMath {
 public:
  CMath(T const &t1, T const &t2) : m_t1(t1), m_t2(t2) {}
  T add();
 private:
  T m_t1;
  T m_t2;
};

template<class T>
T CMath<T>::add() {
  return m_t1 + m_t2;
}

int main() {
  int nx = 10, ny = 20;
  CMath<int> m1(nx, ny);
  cout << m1.add() << '\n';

  double dx = 1.23, dy = 4.56;
  CMath<double> m2(dx, dy);
  cout << m2.add() << '\n';

  string sx = "hello", sy = "world";
  CMath<string> m3(sx, sy);
  cout << m3.add() << '\n';

  return 0;

  return 0;
}*/
/*
#include <iostream>

using namespace std;

class Integer {
 public:
  Integer(int i) : m_i(i) {}
  Integer operator+(const Integer &other) const {
    return m_i + other.m_i;
  }
 private:
  int m_i;
};

template<class T>
class Test {
 public:
  Test(const T &t1, const T &t2) : m_t1(t1), m_t2(t2) {}
  T add() {
    return m_t1 + m_t2;
  }
 private:
  T m_t1;
  T m_t2;
};

int main() {
  int nx = 10, ny = 20;
  Test<int> m(nx, ny);

  Integer ix = 100, iy = 200;
  Test<Integer> m2(ix, iy);
  return 0;
}*/
/*#include <iostream>
using namespace std;
template<class T>
class A {
 public:
  static void print() {
    cout << "&m_i: " << &m_i << ',' << " &m_t: " << &m_t << endl;
  }
  static int m_i;
  static T m_t;
};

template<class T>
int A<T>::m_i;

template<class T>
T A<T>::m_t;

int main() {
  A<int> x, y, z;
  x.print();
  y.print();
  z.print();
  A<int>::print();
  cout << "=== === === ===\n";

  A<double> u, v, w;
  u.print();
  v.print();
  w.print();
  A<double>::print();
  return 0;
}*/
/*#include <iostream>

using namespace std;

class Shape {
 public:
  virtual double getPerimeter() = 0;
  virtual double getArea() = 0;
};

class Circle : public Shape {
 private:
  double radius;
 public:
  Circle(double r) : radius(r) {}

  double getPerimeter() {
    return 2 * 3.14 * radius;
  }

  double getArea() {
    return 3.14 * radius * radius;
  }
};

class Rectangle : public Shape {
 private:
  double length;
  double width;
 public:
  Rectangle(double l, double w) : length(l), width(w) {}

  double getPerimeter() {
    return 2 * (length + width);
  }

  double getArea() {
    return length * width;
  }
};

void printInfo(Shape &shape) {
  cout << shape.getPerimeter() << '\n';
  cout << shape.getArea() << '\n';
}

int main() {
  Circle circle(5);
  Rectangle rectangle(4, 6);

  printInfo(circle);
  printInfo(rectangle);
  return 0;
}*/
/*#include <iostream>

using namespace std;

template<class T>
class Array {
 public:
  T &operator[](size_t i) {
    return m_arr[i];
  }
 private:
  T m_arr[10];
};

int main() {
  Array<Array<int>> array;
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      array[i][j] = i + j;
    }
  }
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      cout << array[i][j] << ' ';
    }
    cout << '\n';
  }
  return 0;
}*/
/*#include <iostream>
#include <cstring>

using namespace std;

template<class T>
class CMath {
 public:
  CMath(const T &t1, const T &t2) : m_t1(t1), m_t2(t2) {}
  T add() { return m_t1 + m_t2; }
 private:
  T m_t1;
  T m_t2;
};

template<>
char *const CMath<char *const>::add() {
  return strcat(m_t1, m_t2);
}

int main() {
  char cx[256] = "hello", cy[256] = "world";
  CMath<char *const> mc(cx, cy);
  cout << mc.add() << '\n';
  return 0;
}*/
/*#include <iostream>

using namespace std;

template<class T, class U>
class CMath {
 public:
  static void foo() {
    cout << "1:CMath<T, D>::foo" << endl;
  }
};

// 局部特化
// 只特化一部分类型参数
template<class T>
class CMath<T, short> {
 public:
  static void foo() {
    cout << "2:CMath<T, short>::foo" << endl;
  }
};

// 将原本两个不同的变量变成一个变量
template<class T>
class CMath<T, T> {
 public:
  static void foo() {
    cout << "3:CMath<T, T>::foo" << endl;
  }
};

template<class T, class D>
class CMath<T *, D *> {
 public:
  static void foo() {
    cout << "4:CMath<T*, D*>::foo" << endl;
  }
};

int main() {
  CMath<int, double>::foo();  // 1
  CMath<int, short>::foo();  // 2
  CMath<int *, double *>::foo();
  return 0;
}*/
/*#include <iostream>

using namespace std;

template<class T = short, class D = int>
class CMath {
 public:
  void print() {
    cout << "m_t: " << typeid(m_t).name() << ", "
         << "m_d: " << typeid(m_d).name() << '\n';
  }
 private:
  T m_t;
  D m_d;
};

int main() {
  CMath<float, double> m;
  m.print();
  CMath<int> n;
  n.print();
  CMath<> a;
  a.print();
  return 0;
}*/
/*
#include <iostream>

using namespace std;

template<class T = double, size_t S = 15>
class Array {
 public:
  T &operator[](size_t i) {
    return m_arr[i];
  }

  size_t size() { return S; }

 private:
  // 初始化数组使用数值型
  T m_arr[S];
};

int main() {
  // 二十个大小的数组
  Array<int, 20> a;

  for (int i = 0; i < a.size(); ++i) {
    a[i] = i + 1;
  }

  for (int i = 0; i < a.size(); ++i) {
    cout << a[i] << ' ';
  }

  return 0;
}*/
/*
#include <iostream>

using namespace std;

template<class T>
class Array {
 public:
  T &operator[](size_t i) {
    return m_arr[i];
  }

 private:
  T m_arr[10];
};

template<class U, size_t S = 20>
class Sum {
 public:
  Sum(Array<U> u) : m_s(u) {}
  U add() {
    U u = 0;
    for (int i = 0; i < S; ++i) {
      u += m_s[i];
    }
    return u;
  }
 private:
  Array<U> m_s;
};

int main() {
  Array<int> a;
  for (int i = 0; i < 10; ++i) {
    a[i] = i + 1;
  }
  Sum<int> s(a);
  cout << s.add() << '\n';
  return 0;
}*/
/*#include <iostream>

using namespace std;

template<class T>
class CMath {
 public:
  template<class D>
  void foo();
};

template<class T>
template<class D>
void CMath<T>::foo() {
  cout << "CMath<T>::foo<D>()" << endl;
}

int main() {
  CMath<int> m;
  m.foo<double>();
  return 0;
}*/

#include <iostream>
using namespace std;

template<class X>
class A {
 public:
  template<class Y>
  class B {
   public:
    template<class Z>
    class C;
  };
};

template<class X>
template<class Y>
template<class Z>
class A<X>::B<Y>::C {
 public:
  template<class T>
  void foo() {
    cout << "foo()" << endl;
  }
};

int main() {
  A<int>::B<double>::C<float> c;
  c.foo<string>();
  return 0;
}
