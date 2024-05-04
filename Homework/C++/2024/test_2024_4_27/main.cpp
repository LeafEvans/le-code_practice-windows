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
/*#include <iostream>
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

template<typename X>
template<typename Y>
template<typename Z>
class A<X>::B<Y>::C {
 public:
  template<typename T>
  void foo();
};
template<class X>
template<class Y>
template<class Z>
template<class T>
void A<X>::B<Y>::C<Z>::foo() {
  cout << "void foo()" << endl;
}
int main() {
  A<int>::B<double>::C<string> m;
  m.foo<char>();
  return 0;
}*/
/*#include <iostream>
using namespace std;

typedef struct LinkNode {
  int data;
  struct LinkNode *next;
} LinkNode;

void insertionSort(LinkNode *&head) {
  if (head == nullptr || head->next == nullptr) return;

  LinkNode *sorted = nullptr;
  LinkNode *curr = head;

  while (curr != nullptr) {
    LinkNode *next = curr->next;
    if (sorted == nullptr || curr->data < sorted->data) {
      curr->next = sorted;
      sorted = curr;
    } else {
      LinkNode *temp = sorted;
      while (temp->next != nullptr && temp->next->data < curr->data) {
        temp = temp->next;
      }
      curr->next = temp->next;
      temp->next = curr;
    }
    curr = next;
  }

  head = sorted;
}

void printList(LinkNode *head) {
  while (head != nullptr) {
    cout << head->data << " ";
    head = head->next;
  }
  cout << endl;
}

int main(int argc, char *argv[]) {
  LinkNode *head = new LinkNode{5, nullptr};
  head->next = new LinkNode{3, nullptr};
  head->next->next = new LinkNode{8, nullptr};
  head->next->next->next = new LinkNode{2, nullptr};
  head->next->next->next->next = new LinkNode{1, nullptr};

  cout << "Original list: ";
  printList(head);

  insertionSort(head);

  cout << "Sorted list: ";
  printList(head);

  return 0;
}*/
/*#include <iostream>

using namespace std;

int main() {
  int a = 10, b = 11;
  swap(a, b);
  cout << a << ' ' << b << '\n';
  return 0;
}*/
/*#include <iostream>

using namespace std;

// 数组模板类
template<class T, size_t S = 15>
class Array {
 public:
  // 取地址操作符
  T &operator[](size_t i) {
    return m_arr[i];
  }

 private:
  // 以 T 的类型作为数组
  T m_arr[S];
};

// U 是代指那个数组的数据类型
// template<class M> D 是指那个数组类
// 此处数组类使用类模板，以兼容其他的数组类
template<class U, template<class, size_t S = 15> class D, size_t S = 15>
class Sum {
 public:
  // 这里初始化了一个数组类
  Sum(D<U, S> d) : m_s(d) {}

  // add() 函数
  U add() {
    U u = 0;
    for (size_t i = 0; i < S; ++i) {
      u += m_s[i];
    }
    return u;
  }

 private:
  // 数组成员
  D<U> m_s;
};

int main() {
  Array<int> a;
  for (int i = 0; i < 10; ++i) {
    a[i] = i + 1;
  }
  Sum<int, Array> s(a);
  cout << s.add() << endl;
  return 0;
}*/
/*
#include <iostream>
using namespace std;

template<typename T, size_t S = 15>
class Array {
 public:
  T &operator[](size_t i) { return m_arr[i]; }

 private:
  T m_arr[S];
};

template<typename T, template<typename M, size_t S = 15> class U, size_t S = 15>
class Sum {
 public:
  Sum(U<T> u) : m_s(u) {}
  T add() {
    T t = 0;
    for (int i = 0; i < S; ++i) {
      t += m_s[i];
    }
    return t;
  }

 private:
  U<T> m_s;
};

int main() {
  Array<int> arr;

  for (int i = 0; i < 15; ++i) {
    arr[i] = i + 1;
  }

  Sum<int, Array> sum(arr);

  cout << sum.add() << endl;

  return 0;
}*/
/*#include <iostream>

using namespace std;

class A {
 public:
  class B {
   public:
    void foo() { cout << "A::B::foo()" << endl; }
  };
};

template<class T>
void Func() {
  typename T::B b;
  b.foo();
}

int main() {
  Func<A>();
  return 0;
}*/
/*#include <iostream>

using namespace std;

class A {
 public:
  template<class T>
  void foo() {
    cout << "A::foo<T>()" << endl;
  }
};

template<class D>
void Func() {
  D d;
  d.template foo<int>();
}

int main() {
  Func<A>();
  return 0;
}*/
/*
#include <iostream>

using namespace std;

class Integer {
 public:
  Integer() : m_i(0) {}

  friend ostream &operator<<(ostream &os, Integer const &that) {
    return os << that.m_i;
  }
 private:
  int m_i;
};

template<class T>
void Func() {
  T t;
  cout << "t = " << t << endl;
}

int main() {
  // 因为如此，所以调用的时候不好使用
  Func<int>();      // 基本类型不赋初值，初值不确定
  Func<Integer>();  // 类类型赋初值，初值确定
  return 0;
}*/
/*
#include <iostream>
using namespace std;

template<class T>
class Base {
 public:
  virtual void foo() {
    cout << "Base<T>::foo()\n";
  }
};

template<class T, class U>
class Derived : public Base<T> {
 public:
  void foo() {
    cout << "Derived<T, D>::foo()\n";
  }
  template<class D>
  virtual void bar{

  };
};

int main() {
  Derived<int, int> d;
  Base<int> *pBase = &d;
  pBase->foo();
  return 0;
}*/
/*
#include <iostream>

using namespace std;

class A {
 public:
  class B {
   public:
    void foo() {
      cout << "A::B::foo()\n";
    }
  };
};

template<class T>
void Func() {
  typename T::B b;
  b.foo();
}

int main() {
  A::B b;
  b.foo();
  return 0;
}*/
/*
#include <iostream>

using namespace std;

class A {
 public:
  template<class T>
  void foo() {
    cout << "A::foo()\n";
  }
};

template<class T>
void Func() {
  T t;
  t.template foo<int>();
}

int main() {
  Func<A>();
  return 0;
}*/
/*
#include <iostream>

using namespace std;

template<class T>
class Base {
 public:
  int m_i;
  void foo() {
    cout << "Base<T>::foo()\n";
  }
};

template<class T, class U>
class Derived : public Base<T> {
 public:
  void bar() {
    this->m_i = 100;
    this->foo();
  }
};

int main() {
  Derived<int, double> d;
  d.bar();
  return 0;
}*/
/*#include <iostream>

using namespace std;

class Integer {
 public:
  Integer() : m_i(0) {}

  friend ostream &operator<<(ostream &os, const Integer &integer) {
    return os << integer.m_i;
  }

 private:
  int m_i;
};

template<class T>
void Func() {
  T t = T();
  cout << "t = " << t << endl;
}

int main() {
  Func<int>();
  Func<Integer>();
  return 0;
}*/
// #include <iostream>
// #include <exception>
// using namespace std;
///**
// * @brief 链表类
// */
// template<typename T>
// class List {
// public:
//  /**
//   * @brief 缺省构造函数
//   */
//  List() : m_head(nullptr), m_tail(nullptr) {}
//  /**
//   * @brief 拷贝构造函数
//   * @param other
//   */
//  List(const List &other) : m_head(nullptr), m_tail(nullptr) {
//    for (Node *node = other.m_head; node; node = node->next) {
//      // 从头节点取数据
//      // 压到新链表的尾部
//      pushBack(node->m_data);
//    }
//  }
//  /**
//   * @brief 析构函数
//   */
//  ~List() {
//    clear();
//  }
//  /**
//   * @brief 链表判空
//   */
//  bool empty() {
//    return m_head == nullptr && m_tail == nullptr;
//  }
//  /**
//   * @brief 添加头节点
//   * @param data
//   */
//  void pushFront(const T &data) {
//    // 先创造一个新节点，它的 prev 为空，以原来的尾节点为 next
//    // 将 m_head 指向这个新节点
//    m_head = new Node(nullptr, data, m_head);
//    if (m_head->m_next) {
//      // m_head 的下一个节点如果存在
//      // 它的下一个节点的前节点为 m_head
//      m_head->m_next->m_prev = m_head;
//    } else {
//      // m_head 没有下一个节点
//      // 链表只有一个节点，代表尾指针也指向头指针指向的节点
//      m_tail = m_head;
//    }
//  }
//  /**
//   * @brief 删除头节点
//   */
//  void popFront() {
//    // 如果当前链表为空链表则直接跳出函数
//    if (empty()) {
//      return;
//    }
//    // 将新的节点备份
//    Node *temp = m_head->m_next;
//    // 删出旧的节点
//    delete m_head;
//    if (temp) {
//      // 如果头节点存在下一个节点，也即是链表不止一个元素
//      // 将新链表的头节点的前指针置为空
//      temp->m_prev = nullptr;
//    } else {
//      // 否则，删除完后，链表一个节点都没有了
//      // 尾节点也为空
//      m_tail = nullptr;
//    }
//    // 赋值个头节点新的值
//    m_head = temp;
//  }
//  /**
//   * @brief 返回头节点的数据
//   * @return 头节点的数据
//   */
//  T &front() {
//    if (empty()) {
//      // 抛出异常
//      throw underflow_error("Null Node");
//    }
//    return m_head->m_data;
//  }
//  /**
//   * @brief 常函数，常链表才可调用
//   * @return
//   */
//  T const &front() const {
//    // 将类内的非 const 版本的 front() 函数转化为 const 版本的使用
//    return const_cast<List*>(this)->front();
//  }
//  /**
//   * @brief 添加尾节点的数据
//   * @param data
//   */
//  void pushBack(T const &data) {
//    m_tail = new Node(m_tail, data, nullptr);
//    if (m_tail->m_prev) {
//      m_tail->m_prev->m_next = m_tail;
//    } else {
//      m_head = nullptr;
//    }
//  }
//  /**
//   * @brief 删除尾节点的数据
//   */
//  void popBack() {
//    if (empty()) {
//      return;
//    }
//    Node *temp = m_tail->m_prev;
//    delete m_tail;
//    if (temp) {
//      temp->m_next = nullptr;
//    } else {
//      m_head = nullptr;
//    }
//    m_tail = temp;
//  }
//  /**
//   * @brief 获取尾节点数据
//   * @return 尾节点
//   */
//  T &back() {
//    if (empty()) {
//      throw underflow_error("Null Node");
//    }
//
//    return m_tail->m_data;
//  }
//  /**
//   * @brief 常函数，常链表可访问
//   * @return 尾节点
//   */
//  T const &back() const {
//    // 将之前的改成常属性
//    return const_cast<List *>(this)->back();
//  }
//  /**
//   * @brief 清空链表
//   */
//  void clear() {
//    // 链表不为空
//    while (!empty()) {
//      // 直接调用之前实现的删除头节点的函数
//      popFront();
//    }
//  }
//  /**
//   * @brief 获取链表大小
//   * @return 链表节点个数
//   */
//  size_t size() {
//    size_t count = 0;  // 计数器
//    // 从头节点开始
//    // 判断这个节点是否存在
//    // 指向下一个节点
//    // 计数器增加
//    for (Node *node = m_head; node; node = node->m_next) {
//      ++count;
//    }
//    // 返回计数器
//    return count;
//  }
// private:
//  /**
//   * @brief 节点类
//   */
//  class Node {
//   public:
//    Node(Node *prev, const T &data, Node *next) : m_prev(prev), m_data(data),
//    m_next(next) {} Node *m_prev;  // 前指针 T m_data;      // 节点数据 Node
//    *m_next;  // 后指针
//  };
//
//  Node *m_head;  // 链表头
//  Node *m_tail;  // 链表尾
//  friend ostream &operator<<(ostream &os, List<int> &list);
//};
// ostream &operator<<(ostream &os, List<int> &list) {
//   for (List<int>::Node *node = list.m_head; node; node = node->m_next) {
//     os << node->m_data << ' ';
//   }
//   return os;
// }
// int main() {
//   List<int> list;
//   for (int i = 0; i < 5; ++i) {
//     list.pushFront(10 + i);
//   }
//   for (int i = 0; i < 5; ++i) {
//     list.pushBack(100 + i);
//   }
//   cout << list << endl;
//   list.popFront();
//   list.popBack();
//   cout << list << endl;
//   return 0;
// }
/*
#include <exception>
#include <iostream>

using namespace std;

template<typename T>
class List {
 public:
  List() : m_head(nullptr), m_tail(nullptr) {}
  List(const List &other) {}
  ~List() {}
  bool empty() {
    return m_head == nullptr && m_tail == nullptr;
  }
  void push_front(const T &data) {
    m_head = new Node(nullptr, data, m_head);
    if (m_head->m_next) {
      m_head->m_next->m_prev = m_head;
    } else {
      m_tail = m_head;
    }
  }
  void pop_front(const T &data) {
    if (empty()) {
      return;
    }
    Node *new_head = m_head->m_next;
    delete m_head;
    if (new_head) {
      new_head->m_prev = nullptr;
    } else {
      m_tail = nullptr;
    }
    m_head = new_head;
  }
  T &front() {
    if (empty()) {
      throw "Null Node";
    }
    return m_head->data;
  }
  T const &front() const {
    return const_cast<List *>(this)->front();
  }
  void push_back(const T &data) {
    m_tail = new Node(m_tail, data, nullptr);
    if (m_tail->m_prev) {
      m_tail->m_prev->m_next = m_tail;
    } else {
      m_head = m_tail;
    }
  }
  void pop_back() {
    if (empty()) {
      return;
    }
    Node *new_tail = m_tail->m_prev;
    delete m_tail;
    if (new_tail) {
      new_tail->m_next = nullptr;
    } else {
      m_head = nullptr;
    }
    m_tail = new_tail;
  }
  T &tail() {
    if (empty()) {
      throw "Null Node";
    }
    return m_tail->m_data;
  }
  const T &tail() const {
    return const_cast<List *>(this)->front();
  }
  void clear() {
    while (!empty()) {
      pop_front();
    }
  }
  size_t size() {
    size_t count = 0;
    for (Node *node = m_head; node; node = node->m_next) {
      ++count;
    }
    return count;
  }
 private:
  class Node {
   public:
    Node(const Node *prev, const T &data, const Node *next)
        : m_prev(prev), m_data(data), m_next(next) {}
    Node *m_prev;
    Node *m_next;
    T m_data;
  };
  Node *m_head;
  Node *m_tail;
};*/
/*#include <iostream>

using namespace std;

template<class T>
class List {
  public:
    List() : m_head(nullptr), m_tail(nullptr) {}
    List(const List &other) {
      for (Node *node = other.m_head; node; node = node->m_next) {
        push_back(node->m_data);
      }
    }
    ~List() {
      clear();
    }

    bool empty() {
      return m_head == nullptr && m_tail == nullptr;
    }

    void push_front(const T &data) {
      m_head = new Node(nullptr, data, m_head);

      if (m_head->m_next) {
        m_head->m_next->m_prev = m_head;
      } else {
        m_tail = m_head;
      }
    }

    void pop_front() {
      if (empty()) {
        return;
      }

      Node *new_head = m_head->m_next;
      delete m_head;
      if (new_head) {
        new_head->m_prev = nullptr;
      } else {
        m_tail = nullptr;
      }

      m_head = new_head;
    }

    T &front() {
      if (empty()) {
        throw underflow_error("Null Node");
      }

      return m_head->m_data;
    }

    const T &front() const {
      return const_cast<List *>(this)->front();
    }

    void push_back(const T &data) {
      m_tail = new Node(m_tail, data, nullptr);

      if (m_tail->m_prev) {
        m_tail->m_prev->m_next = m_tail;
      } else {
        m_head = m_tail;
      }
    }

    void pop_back() {
      if (empty()) {
        return;
      }

      Node *new_tail = m_tail->m_prev;
      delete m_tail;
      if (new_tail) {
        new_tail->m_next = nullptr;
      } else {
        m_head = nullptr;
      }

      m_tail = new_tail;
    }

    T &back() {
      if (empty()) {
        throw underflow_error("Null Node");
      }

      return m_tail->m_data;
    }

    const T &back() const {
      return const_cast<List *>(this)->front();
    }

    void clear() {
      while (!empty()) {
        pop_front();
      }
    }

    size_t size() {
      size_t count = 0;
      for (Node *node = m_head; node; node = node->m_next) {
        ++count;
      }
      return count;
    }

  private:
    class Node {
      public:
        Node(const Node *prev, const T &data, const Node *next): m_prev(prev), m_data(data), m_next(next) {}
        Node *m_prev;
        T m_data;
        Node *m_next;
    };
    Node *m_head;
    Node *m_tail;
};*/
/*#include <iostream>

using namespace std;

template<class T>
// 链表类
class List {
  public:
    // 节点类
    class Node {
      public:
        // 初始化节点
        // 注意，仅有那个模板的可以用 const 关键字
        Node(Node *prev, const T &data, Node *next)
          : m_prev(prev), m_data(data), m_next(next) {}
        Node *m_prev;
        T m_data;
        Node *m_next;
    };

    // 正向非常迭代器
    class Iterator {
      public:
        // 初始化
        // 不使用 const 关键字，因为不是引用，不会改变
        Iterator(Node *start, Node *cur, Node *end)
          : m_start(start),
            m_cur(cur),
            m_end(end) {}

        // 解引用操作符
        T &operator*() {
          // 如果指向为空的话
          if (!m_cur) {
            // 抛出错误
            throw underflow_error("Null Node");
          }
          return m_cur->m_data;
        }

        // 自增操作符
        Iterator &operator++() {
          if (!m_cur) {
            // 如果指向空的话
            // 进行循环操作
            // 指向头节点
            m_cur = m_start;
          } else {
            // 当前的指向下一个
            m_cur = m_cur->m_next;
          }
          return *this;
        }

        // 类似的
        Iterator &operator--() {
          if (!m_cur) {
            m_cur = m_end;
          } else {
            m_cur = m_cur->m_prev;
          }

          return *this;
        }

        // 进行相等性判断
        bool operator==(const Iterator &other) const {
          return m_start == other.m_start
              && m_cur == other.m_cur
              && m_end == other.m_end;
        }

        bool operator!=(const Iterator &other) const {
          // 利用前面重载的操作符进行不等性判断
          return !(*this == other);
        }

      private:
        Node *m_start;
        Node *m_cur;
        Node *m_end;
        friend class List;
    };

    // 常迭代类
    class ConstIterator {
      public:
        // 进行初始化
        ConstIterator(Node *start, Node *cur, Node *end)
          : m_it(start, cur, end) {}

        // 类似的，利用之前的操作符
        // 加了 const 关键字
        // 均利用了之前的操作符
        const T &operator *() {
          return *m_it;
        }

        ConstIterator &operator++() {
          ++m_it;
          return *this;
        }

        ConstIterator &operator--() {
          --m_it;
          return *this;
        }

        bool operator==(const ConstIterator &other) const {
          return m_it == other.m_it;
        }

        bool operator!=(const ConstIterator &other) const {
          return m_it != other.m_it;
        }

      private:
        Iterator m_it;
    };

    // 反向非常迭代器
    class ReverseIterator {
      public:
        // 初始化
        ReverseIterator(Node *start, Node *cur, Node *end)
          : m_start(start), m_cur(cur), m_end(end) {}

        T &operator*() {
          if (!m_cur) {
            throw underflow_error("Null Node");
          }
          return m_cur->m_data;
        }

        ReverseIterator &operator++() {
          // 从尾节点开始
          if (!m_cur) {
            // 循环指向尾节点
            m_cur = m_end;
          } else {
            // 指向前一个
            m_cur = m_cur->m_prev;
          }

          return *this;
        }
        // 类似的
        ReverseIterator &operator--() {
          if (!m_cur) {
            m_cur = m_start;
          } else {
            m_cur = m_cur->m_next;
          }

          return *this;
        }

        bool operator==(const ReverseIterator &other) const {
          return m_start == other.m_start
              && m_cur == other.m_cur
              && m_end == other.m_end;
        }

        bool operator!=(const ReverseIterator &other) const {
          return !(*this == other);
        }

      private:
        Node *m_start;
        Node *m_cur;
        Node *m_end;
        friend class List;
    };

    class ConstReverseIterator {
      public:
        ConstReverseIterator(Node *start,
                             Node *cur,
                             Node *end): m_rit(start, cur, end) {}

        const T &operator*() {
          return *m_rit;
        }

        ConstReverseIterator &operator++() {
          ++m_rit;
          return *this;
        }

        ConstReverseIterator &operator--() {
          --m_rit;
          return *this;
        }

        bool operator==(const ConstReverseIterator &other) const {
          return m_rit == other.m_rit;
        }

        bool operator!=(const ConstReverseIterator &other) const {
          return m_rit != other.m_rit;
        }

      private:
        ReverseIterator m_rit;
    };

    // 初始化函数
    List(): m_head(nullptr), m_tail(nullptr) {}

    // 拷贝构造函数
    List(const List &other) {
      for (Node *node = other.m_head; node; node = node->m_next) {
        // 不断的进行尾插
        // 直到指向空
        push_back(node->m_data);
      }
    }

    // 析构函数
    ~List() {
      clear();
    }

    // 判断是否为空
    bool empty() const {
      return m_head == nullptr && m_tail == nullptr;
    }

    // 前插
    void push_front(const T &data) {
      // 新定义要插入的节点
      m_head = new Node(nullptr, data, m_head);
      if (m_head->m_next) {
        // 如果头节点下一个存在的话
        // 将下一个的前指针指向头节点
        m_head->m_next->m_prev = m_head;
      } else {
        // 如果没有，说明链表内就一个元素
        // 尾节点同时也是头节点
        m_tail = m_head;
      }
    }

    void pop_front() {
      // 删除头节点
      if (empty()) {
        // 为空，那没什么好删的
        // 退出
        return;
      }

      // 新的头节点为后一个节点
      Node *new_head = m_head->m_next;
      // 删除旧的节点
      delete m_head;

      if (new_head) {
        // 如果新节点不为空的话
        // 将它的前指针指向空
        new_head->m_prev = nullptr;
      } else {
        // 如果新节点为空，说明链表内没有元素了
        // 尾节点也指向空
        m_tail = nullptr;
      }

      // 更新节点指向
      m_head = new_head;
    }

    // 返回头节点数据
    T &front() {
      // 如果为空
      if (empty()) {
        // 报错
        throw underflow_error("Null Node");
      }
      // 如果头节点有数据
      return m_head->m_data;
    }

    // 常链表使用的
    const T &front() const {
      return const_cast<List *>(this)->front();
    }

    // 这是尾节点，类似的
    void push_back(const T &data) {
      m_tail = new Node(m_tail, data, nullptr);

      if (m_tail->m_prev) {
        m_tail->m_prev->m_next = m_tail;
      } else {
        m_head = m_tail;
      }
    }

    void pop_back() {
      if (empty()) {
        return;
      }

      Node *new_tail = m_tail->m_prev;
      delete m_tail;

      if (new_tail) {
        new_tail->m_next = nullptr;
      } else {
        m_head = nullptr;
      }

      m_tail = new_tail;
    }

    // 清空链表
    void clear() {
      // 如果不为空
      while (!empty()) {
        // 就一直进行删除尾部节点操作
        pop_back();
      }
    }

    // 计算节点个数
    size_t size() const {
      // 计数器
      size_t count = 0;
      // 从头节点开始循环
      for (Node *node = m_head; node; node = node->m_next) {
        ++count;
      }
      return count;
    }

    // 返回正向非常起始
    Iterator begin() {
      return Iterator(m_head, m_head, m_tail);
    }

    // 正向非常终止
    Iterator end() {
      return Iterator(m_head, nullptr, m_tail);
    }

    // 方向非常起始
    ReverseIterator rbegin() {
      return ReverseIterator(m_tail, m_tail, m_head);
    }

    // 反向非常终止
    ReverseIterator rend() {
      return ReverseIterator(m_tail, nullptr, m_tail);
    }

    // 插入操作
    void insert(const Iterator &loc, const T &data) {
      // 如果当前位置尾链表尾部i
      if (loc == end()) {
        // 直接进行尾插
        push_back(data);
      } else {
        // 创建个新节点，前指针指向当前位置的前一个，后指针指向当前位置
        Node *node = new Node(loc.m_cur->m_prev, data, loc.m_cur);
        if (node->m_prev) {
          // 前一个结点的后指针指向当前结点
          node->m_prev->m_next = node;
        } else {
          // 说明当前节点前面没有节点
          // 它就是头节点
          m_head = node;
        }
        // 当前位置的存在必然保证了要插入节点的后指针不为空
        // 否则在最上面的 if 就排除了
        // 更新指向
        loc.m_cur->m_prev = node;
      }
    }

    // 删除操作
    void erase(const Iterator &loc) {
      // 当前位置为尾部
      if (loc == end()) {
        return; // 直接返回
      }

      // 将迭代器的值赋给一个新的量，因为迭代器不能直接进行操作
      Node *node = loc.m_cur;
      // 进行前后判断
      if (node->m_next) {
        node->m_next->m_prev = node->m_prev;
      } else {
        m_tail = node->m_prev;
      }

      if (node->m_prev) {
        node->m_prev->m_next = node->m_next;
      } else {
        m_head = node->m_next;
      }

      delete node;
    }

    // 反着插
    void insert(const ReverseIterator &loc, const T &data) {
      if (loc == end()) {
        push_front(data);
      } else {
        Node *node = new Node(loc.m_cur->m_next, data, loc.m_cur);
        if (node->m_next) {
          node->m_next->m_prev = node;
        } else {
          m_tail = node;
        }
        loc.m_cur->m_next = node;
      }
    }

    // 反着删
    void erase(const ReverseIterator &loc) {
      if (loc == end()) {
        return;
      }

      Node *node = loc.m_cur;
      if (node->m_prev) {
        node->m_prev->m_next = node->m_next;
      } else {
        m_head = node->m_next;
      }

      if (node->m_next) {
        node->m_next->m_prev = node->m_prev;
      } else {
        m_tail = node->m_prev;
      }

      delete node;
    }

    // 一些返回开始的
    ConstIterator begin() const {
      return ConstIterator(m_head, m_head, m_tail);
    }

    ConstIterator end() const {
      return ConstIterator(m_head, nullptr, m_tail);
    }

    ConstReverseIterator rbegin() const {
      return ConstReverseIterator(m_tail, m_tail, m_head);
    }

    ConstReverseIterator rend() const {
      return ConstReverseIterator(m_tail, nullptr, m_head);
    }

  private:
    Node *m_head;
    Node *m_tail;
};

// 正向打印
void print(const string &str, const List<int> &list) {
  cout << str << endl;
  typedef List<int>::ConstIterator CIT;
  for (CIT cit = list.begin(); cit != list.end(); ++cit) {
    cout << *cit << ' ';
  }
  cout << '\n' << "----------------------------------\n";
}

// 反向打印
void rprint(const string &str, const List<int> &list) {
  cout << str << endl;
  typedef List<int>::ConstReverseIterator CRIT;
  for (CRIT crit = list.rbegin(); crit != list.rend(); ++crit) {
    cout << *crit << ' ';
  }
  cout << '\n' << "----------------------------------\n";
}

int main() {
  List<int> list;

  for (int i = 0; i < 5; ++i) {
    list.push_front(10 + i);
  }
  for (int i = 0; i < 5; ++i) {
    list.push_back(100 + i);
  }
  print("添加节点后：", list);
  rprint("添加节点后(r)", list);

  list.pop_front();
  list.pop_back();
  print("删除头尾节点后：", list);
  rprint("删除头尾节点后：(r)", list);

  list.insert(++list.begin(), 1000);
  print("在迭代器指向的位置添加节点后：", list);
  rprint("在迭代器指向的位置添加节点后：(r)", list);

  list.erase(list.begin());
  print("删除迭代器指向的节点后：", list);
  rprint("删除迭代器指向的节点后：(r)", list);

  typedef List<int>::Iterator IT;
  IT it = list.begin();
  *it = 800;
  print("更改迭代器指向的节点后：", list);
  rprint("更改迭代器指向的节点后：(r)", list);

  const List<int> const_list(list);
  typedef List<int>::ConstIterator CIT;
  for (CIT cit = const_list.begin(); cit != const_list.end(); ++cit) {
    cout << *cit << ' ';
  }
  cout << '\n' << "----------------------------------\n";

  return 0;
}*/
#include <iostream>

template<class T>
class List {
 public:
  class Node {
   public:
    Node(Node *prev, const T &data, Node *next)
        : m_prev(prev), m_data(data), m_next(next) {}
    Node *m_prev;
    T m_data;
    Node *m_next;
  };

  class Iterator {
   public:
    Iterator(Node *start, Node *cur, Node *end)
        : m_start(start), m_cur(cur), m_end(end) {}

    T &operator*() {
      if (!m_cur) {
        throw std::underflow_error("Null Node");
      }
      return m_cur->m_data;
    }

    Iterator &operator++() {
      if (!m_cur) {
        m_cur = m_start;
      } else {
        m_cur = m_cur->m_next;
      }
      return *this;
    }

    Iterator &operator--() {
      if (!m_cur) {
        m_cur = m_end;
      } else {
        m_cur = m_cur->m_prev;
      }
      return *this;
    }

    bool operator==(const Iterator &other) const {
      return m_start == other.m_start
          && m_cur == other.m_cur
          && m_end == other.m_end;
    }

    bool operator!=(const Iterator &other) const {
      return !(m_start == other.m_start
          && m_cur == other.m_cur
          && m_end == other.m_end);
    }

   private:
    Node *m_start;
    Node *m_cur;
    Node *m_end;
    friend class List;
  };

  class ConstantIterator {
   public:
    ConstantIterator(Node *start, Node *cur, Node *end)
        : m_it(start, cur, end) {}

    const T &operator*() {
      return *m_it;
    }

    const ConstantIterator &operator++() {
      ++m_it;
      return *this;
    }

    const ConstantIterator &operator--() {
      --m_it;
      return *this;
    }

    bool operator==(const ConstantIterator &other) const {
      return m_it == other.m_it;
    }

    bool operator!=(const ConstantIterator &other) const {
      return m_it != other.m_it;
    }

   private:
    Iterator m_it;
  };

  class ReverseIterator {
   public:
    ReverseIterator(Node *start, Node *cur, Node *end)
        : m_start(start), m_cur(cur), m_end(end) {}

    T &operator*() {
      if (!m_cur) {
        throw std::underflow_error("Null Node");
      }
      return m_cur->m_data;
    }

    ReverseIterator &operator++() {
      if (!m_cur) {
        m_cur = m_start;
      } else {
        m_cur = m_cur->m_prev;
      }
      return *this;
    }

    ReverseIterator &operator--() {
      if (!m_cur) {
        m_cur = m_end;
      } else {
        m_cur = m_cur->m_next;
      }
      return *this;
    }

    bool operator==(const ReverseIterator &other) const {
      return m_start == other.m_start
          && m_cur == other.m_cur
          && m_end == other.m_end;
    }

    bool operator!=(const ReverseIterator &other) const {
      return !(m_start == other.m_start
          && m_cur == other.m_cur
          && m_end == other.m_end);
    }

   private:
    Node *m_start;
    Node *m_cur;
    Node *m_end;
    friend class List;
  };

  class ConstantReverseIterator {
   public:
    ConstantReverseIterator(Node *start,
                            Node *cur,
                            Node *end)
        : m_rit(start, cur, end) {}

    const T &operator*() {
      return *m_rit;
    }

    ConstantReverseIterator &operator++() {
      ++m_rit;
      return *this;
    }

    ConstantReverseIterator &operator--() {
      --m_rit;
      return *this;
    }

    bool operator==(const ConstantReverseIterator &other) const {
      return m_rit == other.m_rit;
    }

    bool operator!=(const ConstantReverseIterator &other) const {
      return m_rit != other.m_rit;
    }

   private:
    ReverseIterator m_rit;
  };

  List() : m_head(nullptr), m_tail(nullptr) {}

  List(const List &other) {
    for (Node *node = other.m_head; node; node = node->m_next) {
      push_back(node->m_data);
    }
  }

  ~List() {
    clear();
  }

  bool empty() const {
    return m_head == nullptr && m_tail == nullptr;
  }

  void push_front(const T &data) {
    m_head = new Node(nullptr, data, m_head);
    if (m_head->m_next) {
      m_head->m_next->m_prev = m_head;
    } else {
      m_tail = m_head;
    }
  }

  void pop_front() {
    if (empty()) {
      return;
    }
    Node *new_head = m_head->m_next;
    delete m_head;
    if (new_head) {
      new_head->m_prev = nullptr;
    } else {
      m_tail = nullptr;
    }
    m_head = new_head;
  }

  T &front() {
    if (m_head) {
      throw std::underflow_error("Null Node");
    }
    return m_head->m_data;
  }

  const T &front() const {
    return const_cast<List *>(this)->front();
  }

  void push_back(const T &data) {
    m_tail = new Node(m_tail, data, nullptr);
    if (m_tail->m_prev) {
      m_tail->m_prev->m_next = m_tail;
    } else {
      m_head = m_tail;
    }
  }

  void pop_back() {
    if (empty()) {
      return;
    }
    Node *new_tail = m_tail->m_prev;
    if (new_tail) {
      new_tail->m_next = nullptr;
    } else {
      m_head = nullptr;
    }
    m_tail = new_tail;
  }

  T &back() {
    if (m_tail) {
      throw std::underflow_error("Null Node");
    }
    return m_tail->m_data;
  }

  const T &back() const {
    return const_cast<List *>(this)->back();
  }

  void clear() {
    while (!empty()) {
      pop_back();
    }
  }

  size_t size() const {
    size_t count = 0;
    for (const Node *node = m_head; node; m_head = m_head->m_next) {
      ++count;
    }
    return count;
  }

  Iterator begin() {
    return Iterator(m_head, m_head, m_tail);
  }

  Iterator end() {
    return Iterator(m_head, nullptr, m_tail);
  }

  ConstantIterator begin() const {
    return ConstantIterator(m_head, m_head, m_tail);
  }

  ConstantIterator end() const {
    return ConstantIterator(m_head, nullptr, m_tail);
  }

  ReverseIterator rbegin() {
    return ReverseIterator(m_tail, m_tail, m_head);
  }

  ReverseIterator rend() {
    return ReverseIterator(m_tail, nullptr, m_head);
  }

  ConstantReverseIterator rbegin() const {
    return ConstantReverseIterator(m_tail, m_tail, m_head);
  }

  ConstantReverseIterator rend() const {
    return ConstantReverseIterator(m_tail, nullptr, m_head);
  }

  void insert(const Iterator &loc, const T &data) {
    if (loc == end()) {
      push_back(data);
      return;
    }
    Node *node = new Node(loc.m_cur->m_prev, data, loc.m_cur);
    if (node->m_prev) {
      node->m_prev->m_next = node;
    } else {
      m_head = node;
    }
    loc.m_cur->m_prev = node;
  }

  void erase(const Iterator &loc) {
    if (loc == end()) {
      return;
    }
    Node *node = loc.m_cur;
    if (node->m_prev) {
      node->m_prev->m_next = node->m_next;
    } else {
      m_head = node->m_next;
    }
    if (node->m_next) {
      node->m_next->m_prev = node->m_prev;
    } else {
      m_tail = node->m_prev;
    }
    delete node;
  }

 private :
  Node *m_head;
  Node *m_tail;
};

void print(const List<int> &list) {
  for (const int elem : list) {
    std::cout << elem << ' ';
  }
  std::cout << '\n' << "-----------------------------------------------\n";
}

void rprint(const List<int> &list) {
  for (List<int>::ConstantReverseIterator crit = list.rbegin();
       crit != list.rend();
       ++crit) {
    std::cout << *crit << ' ';
  }
  std::cout << '\n' << "-----------------------------------------------\n";
}

int main() {
  List<int> list;

  for (int i = 0; i < 5; ++i) {
    list.push_back(i + 100);
  }
  for (int i = 0; i < 5; ++i) {
    list.push_front(i + 1000);
  }
  print(list);
  rprint(list);

  list.pop_back();
  list.push_front(43);
  print(list);
  rprint(list);

  List<int>::Iterator it = list.begin();
  list.insert(++it, 14);
  print(list);
  rprint(list);

  list.clear();
  print(list);
  rprint(list);

  return 0;
}
