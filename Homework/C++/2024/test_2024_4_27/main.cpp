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
/*#include <iostream>

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
}*/
/*
#include <iostream>

using namespace std;

template<class T>
void print(T *arr, size_t len) {
  for (size_t i = 0; i < len; ++i) {
    cout << arr[i] << ' ';
  }
  cout << '\n';
}

int main() {
  int arr[10] = {1, 2, 3, 4, 5,
                 6, 7, 8, 9, 10};
  print(arr, 10);
  return 0;
}*/
/*
#include <iostream>

using namespace std;

template<class T>
void insertionSort(T *arr, size_t len) {
  size_t i, j;
  T key;
  for (i = 1; i < len; ++i) {
    key = arr[i];
    for (j = i - 1; j >= 0 && arr[j] > key; --j) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = key;
  }
}

template<class T>
void printArray(T *arr, size_t len) {
  for (size_t i = 0; i < len; ++i) {
    cout << arr[i] << ' ';
  }
  cout << '\n';
}

int main() {
  int arr[10] = {1, 23, 434, 545, 34,
                 2, 45, 21332, 323, 232};
  printArray(arr, 10);
  insertionSort(arr, 10);
  printArray(arr, 10);
  return 0;
}*/
/*
#include <iostream>

using namespace std;

class Time {
 public:
  Time(size_t hour,
       size_t minute,
       size_t second) : m_hour(hour),
                        m_minute(minute),
                        m_second(second) {}

  Time operator+(const Time &other) {
    size_t hour = m_hour + other.m_hour;
    size_t minute = m_minute + other.m_minute;
    size_t second = m_second + other.m_second;

    if (second >= 60) {
      second -= 60;
      ++minute;
    }

    if (minute >= 60) {
      minute -= 60;
      ++hour;
    }

    return Time(hour, minute, second);
  }

  Time operator-(const Time &other) {
    size_t hour = m_hour - other.m_hour;
    size_t minute = m_minute - other.m_minute;
    size_t second = m_second - other.m_second;

    if (second < 0) {
      second += 60;
      --minute;
    }

    if (minute < 0) {
      minute += 60;
      --hour;
    }

    if (hour < 0) {
      throw "Invalid Data";
    }

    return Time(hour, minute, second);
  }

  friend ostream &operator<<(ostream &os, const Time &time) {

    os << time.m_hour << ':' << time.m_minute << ':' << time.m_second;
    return os;
  }

  friend istream &operator>>(istream &is, Time &time) {
    is >> time.m_hour >> time.m_minute >> time.m_second;
    return is;
  }

 private:
  size_t m_hour;
  size_t m_minute;
  size_t m_second;
};

int main() {
  Time time1(10, 20, 30);
  Time time2(20, 30, 40);
  cout << time1 << ' ' << time2 << endl;
  cin >> time1;
  cout << time1 << endl;
  cout << time1 + time2 << endl;
  cout << time1 - time2 << endl;

  return 0;
}*/
/*
#include <iostream>
#include <cstdio>

using namespace std;

class Matrix {
 public:
  Matrix(size_t row, size_t col) : m_matrix(new double[row * col]), m_row(row), m_col(col) {
    for (size_t i = 0; i < m_row; ++i) {
      for (size_t j = 0; j < m_col; ++j) {
        *(m_matrix + i * m_col + j) = 0;
      }
    }
  }

  bool operator==(const Matrix &other) {
    if (m_row != other.m_row || m_col != other.m_col) {
      throw "InValid Data";
    }

    bool flag = true;

    for (size_t i = 0; i < m_row; ++i) {
      for (size_t j = 0; j < m_col; ++j) {
        if (*(m_matrix + i * m_col + j) != *(other.m_matrix + i * m_col + j)) {
          flag = false;
        }
      }
    }

    return flag;
  }

  Matrix operator+(const Matrix &other) {
    if (m_row != other.m_row || m_col != other.m_col) {
      throw "InValid Data";
    }

    Matrix matrix(m_row, m_col);
    for (size_t i = 0; i < m_row; ++i) {
      for (size_t j = 0; j < m_col; ++j) {
        *(matrix.m_matrix + i * m_col + j) =
            *(m_matrix + i * m_col + j)
                + *(other.m_matrix + i * m_col + j);
      }
    }

    return matrix;
  }

  Matrix operator-(const Matrix &other) {
    if (m_row != other.m_row || m_col != other.m_col) {
      throw "InValid Data";
    }

    Matrix matrix(m_row, m_col);
    for (size_t i = 0; i < m_row; ++i) {
      for (size_t j = 0; j < m_col; ++j) {
        *(matrix.m_matrix + i * m_col + j) =
            *(m_matrix + i * m_col + j)
                - *(other.m_matrix + i * m_col + j);
      }
    }

    return matrix;
  }

 private:
  double *m_matrix;
  size_t m_row;
  size_t m_col;

  friend ostream &operator<<(ostream &os, const Matrix &other) {
    for (size_t i = 0; i < other.m_row; ++i) {
      for (size_t j = 0; j < other.m_col; ++j) {
        cout << *(other.m_matrix + i * other.m_col + j) << ' ';
      }
      cout << '\n';
    }
    return os;
  }

  friend istream &operator>>(istream &is, Matrix &other) {
    for (size_t i = 0; i < other.m_row; ++i) {
      cout << i << ": ";
      for (size_t j = 0; j < other.m_col; ++j) {
        cin >> *(other.m_matrix + i * other.m_col + j);
      }
    }
    return is;
  }
};

int main() {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 3);
  cin >> matrix1;
  cin >> matrix2;
  cout << matrix1 + matrix2;
  cout << matrix1 - matrix2;
  return 0;
}*/
/*#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

class Student {
 public:
  Student(const string &name = "") : m_name(name) {
    cout << "缺省构造了:" << m_name << '(' << this << ')' << endl;
  }

  Student(const Student &other) : m_name(other.m_name) {
    cout << "用:" << other.m_name << '(' << &other << ')'
         << "拷贝构造了:" << m_name << '(' << this << ')' << endl;
  }

  ~Student() {
    cout << "析构了:" << m_name << '(' << this << ')' << endl;
  }

 private:
  string m_name;
};

int main() {
  vector<Student> vs(10);
  vs.reserve(10);
  vs.push_back(Student("张三"));
  vs.push_back(Student("李四"));
  getchar();
  return 0;
}*/
/*#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Student {
 public:
  Student(const string &name = " ", int age = 0)
      : m_name(name), m_age(age) {}

  bool operator==(const Student &other) const {
    return m_name == other.m_name && m_age == other.m_age;
  }

  bool operator<(const Student &other) const {
    // 如果要降序排序，则改为 m_age > other.m_age
    return m_age < other.m_age;
  }

  bool operator>(const Student &other) const {
    return m_age > other.m_age;
  }

  friend ostream &operator<<(ostream &os, const Student &other) {
    return os << other.m_name << ": " << other.m_age;
  }

 private:
  string m_name;
  int m_age;
};

void print(const string &str, vector<Student> &v) {
  cout << str << endl;
  typedef vector<Student>::iterator IT;

  for (IT it = v.begin(); it != v.end(); it++) {
    cout << *it << ' ';
  }

  cout << endl << "--------------------------------" << endl;
}

class CMP {
 public:
  bool operator()(const Student &a, const Student &b) {
    return a > b;
  }
};

int main() {
  vector<Student> vs(10);

  vs.push_back(Student("曹操", 22));
  vs.push_back(Student("刘备", 20));
  vs.push_back(Student("孙权", 18));
  vs.push_back(Student("马超", 10));
  vs.push_back(Student("司马懿", 20));
  print("添加节点后: ", vs);

  vs.insert(vs.begin() + 4, Student("关羽", 21));
  print("在迭代器指向的位置，添加节点后: ", vs);

  vs.erase(vs.begin());
  print("删除迭代器指向的节点后: ", vs);

  typedef vector<Student>::iterator IT;
  IT it = vs.begin();
  *it = Student("诸葛亮", 11);
  print("更改迭代器指向的节点后: ", vs);

  IT fit = find(vs.begin(),
                vs.end(),
                Student("刘备", 20));
  if (fit != vs.end()) {
    vs.erase(fit);
  }
  print("找到刘备并删除后: ", vs);

  sort(vs.begin(), vs.end());
  print("升序排序后: ", vs);

  CMP cmp;
  sort(vs.begin(), vs.end(), cmp);
  print("降序排序后: ", vs);

  return 0;
}*/
/*#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  vector<vector<int>> vi = {{1, 2, 3}, {6, 5, 4}};

  vi.push_back({7, 8, 9});

  sort(vi[1].begin(), vi[1].end());

  vi[2].erase(find(vi[2].begin(), vi[2].end(), 9));

  for (const vector<int> _vi : vi) {
    for (const int i : _vi) {
      cout << i << ' ';
    }
    cout << '\n';
  }

  cout << "Row: " << vi.size() << ", Col: " << vi[0].size() << endl;

  if (!vi.empty()) {
    cout << "不为空！" << endl;
  }

  return 0;
}*/
/*#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  vector<vector<int>> vi = {{1, 2, 3}, {6, 5, 4}};
  cout << "Array: \n";
  for (int i = 0; i < vi.size(); ++i) {
    for (int j = 0; j < vi[i].size(); ++j) {
      cout << vi[i][j] << ' ';
    }
    cout << '\n';
  }

  cout << "Capacity: " << vi.capacity() << endl;
  cout << "Size: " << vi.size() << endl;

  vi.reserve(3);
  vi.insert(vi.end(), {7, 8, 9});

  cout << "Array(new): \n";
  for (int i = 0; i < vi.size(); ++i) {
    for (int j = 0; j < vi[i].size(); ++j) {
      cout << vi[i][j] << ' ';
    }
    cout << '\n';
  }

  cout << "Capacity: " << vi.capacity() << endl;
  cout << "Size: " << vi.size() << endl;

  cout << "Find: " << *find(vi[1].begin(), vi[1].end(), 5);

  return 0;
}*/
/*#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

class Student {
 public:
  Student(const string &name = " ",
          int age = 0) : m_name(name), m_age(age) {}

  friend ostream &operator<<(ostream &os, const Student &other) {
    return os << other.m_name << ": " << other.m_age;
  }

  bool operator==(const Student &other) const {
    return m_name == other.m_name && m_age == other.m_age;
  }

  bool operator<(const Student &other) const {
    return m_age < other.m_age;
  }

 private:
  string m_name;
  int m_age;
};

void print(const string &str, deque<Student> &d) {
  cout << str << '\n';
  typedef deque<Student>::iterator IT;
  for (IT it = d.begin(); it != d.end(); ++it) {
    cout << *it << ' ';
  }
  cout << endl << "---------------------------\n";
}

int main() {
  deque<Student> ds;
  ds.push_front(Student("张飞", 20));
  ds.push_front(Student("赵云", 18));
  ds.push_front(Student("马超", 19));
  ds.push_back(Student("关羽", 24));
  ds.push_back(Student("黄忠", 44));
  print("添加节点后: ", ds);

  typedef deque<Student>::iterator IT;

  ds.insert(ds.begin(), Student("刘备", 24));
  print("在迭代器指定的位置添加节点后: ", ds);

  ds.erase(ds.begin());
  print("删除迭代器指向的节点后: ", ds);

  IT it = ds.begin();

  *it = Student("吕布", 34);
  print("更改迭代器指向的节点后: ", ds);

  IT fit = find(ds.begin(), ds.end(), Student("黄忠", 44));
  if (fit != ds.end()) {
    ds.erase(fit);
  }
  print("找到黄忠并删除后: ", ds);

  sort(ds.begin(), ds.end());
  print("排序后: ", ds);



  return 0;
}*/
/*#include <deque>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<vector<int>> vi = {{1, 2, 3}, {2, 3, 4}};
  for (const vector<int> row : vi) {
    for (const int element : row) {
      cout << element << ' ';
    }
    cout << '\n';
  }
  return 0;
}*/
/*
#include <iostream>
#include <algorithm>
#include <deque>

using namespace std;

int main() {
  deque<int> di = {1, 2, 3};
  di.insert(find(di.begin(), di.end(), 2), 4);
  sort(di.rbegin(), di.rend());
  di.erase(di.begin());
  di.push_back(0);
  di.push_front(-1);
  for (const int element : di) {
    cout << element << ' ';
  }

  cout << '\n';
  return 0;
}*/
/*
#include <list>
#include <iostream>

using namespace std;

void print(const string &str, list<int> &l) {
  cout << str << endl;
  typedef list<int>::iterator IT;
  for (IT it = l.begin(); it != l.end(); ++it) {
    cout << *it << ' ';
  }
  cout << "\n--------------------\n";
}

template<class T>
class CMP {
 public:
  bool operator()(const T &a, const T &b) {
    return a > b;
  }
};

int main() {
  list<int> ls;
  for (int i = 0; i < 5; ++i) {
    ls.push_front(10 + i);
  }
  for (int i = 0; i < 5; ++i) {
    ls.push_back(10 - i);
  }

  print("添加结点后：", ls);
  ls.unique();
  print("唯一化后：", ls);

  ls.sort();  // 链表类的自带排序
  print("升序排序后：", ls);

  CMP<int> cmp;
  ls.sort(cmp);
  print("降序排序后：", ls);

  list<int> lst;
  lst.push_back(1000);
  lst.push_back(2000);
  lst.push_back(3000);
  lst.push_back(4000);

  // ls.splice(ls.begin(), lst);
  // ls.splice(ls.begin(), lst, lst.begin());
  ls.splice(ls.begin(), lst, ++lst.begin(), --lst.end());
  print("ls：", ls);
  print("lst：", lst);
  return 0;
}*/
/*
#include <stack>
#include <vector>
#include <deque>
#include <list>
#include <iostream>

using namespace std;

int main() {
  stack<int, list<int>> s;
  s.push(1);
  s.push(2);
  s.push(3);
  s.push(4);
  s.push(5);
  s.push(6);
  while (!s.empty()) {
    cout << s.top() << ' ';
    s.pop();
  }
  return 0;
}*/
/*
#include <queue>
#include <list>
#include <iostream>

using namespace std;

int main() {
  queue<int, list<int>> s;
  s.push(1);
  s.push(2);
  s.push(3);
  s.push(4);
  s.push(5);
  s.push(6);
  while (!s.empty()) {
    cout << s.front() << ' ';
    s.pop();
  }
  cout << '\n';
  return 0;
}*/
/*
#include <iostream>
#include <map>

using namespace std;

class Candidate {
 public:
  Candidate(string name = "") : m_name(name), m_vote(0) {}
  string m_name;
  int m_vote;
};

void print(map<char, Candidate> &m) {
  typedef map<char, Candidate>::iterator IT;
  for (IT it = m.begin(); it != m.end(); ++it) {
    cout << '(' << (*it).first << ')'
         << (*it).second.m_name << ' ';
  }
  cout << '\n';
}

int main() {
  map<char, Candidate> m;  // 键的类型为字符，值的类型是类型
  m.insert(pair<char, Candidate>('A', Candidate("张飞")));
  m.insert(make_pair('B', Candidate("关羽")));
  m['C'] = Candidate("赵云");  // 因为 'C' 不存在，因此会新创建一个，使用这个方法创建最简单
  m['D'] = Candidate("马超");
  m['E'] = Candidate("黄忠");

  print(m);
  typedef map<char, Candidate>::iterator IT;
  for (int i = 0; i < 10; ++i) {
    print(m);
    char ch;
    cin >> ch;
    m.find(ch);
    IT fit = m.find(ch);
    if (fit == m.end()) {

    }
  }
  return 0;
}*/
/*#include <iostream>
#include <set>

using namespace std;

int main() {
  typedef set<int>::iterator IT;
  typedef set<int>::reverse_iterator RIT;
  set<int> s1;
  s1.insert(3);
  s1.insert(1);
  s1.insert(7);
  s1.insert(5);

  set<int> s2(s1);
  set<int> s3;

  s3 = s2;

  IT it = s3.begin();
  s3.erase(it);  // 删去 set 中的最小值
  it = --s3.end();  // 不能使用反向迭代器进行删除
  it = s3.erase(it);
  cout << s3.erase(5) << '\n';
  for (it = s3.begin(); it != s3.end(); ++it) {
    cout << *it << ' ';
  }
  cout << '\n';
  cout << s3.erase(100) << '\n';
  return 0;
}*/
/*#include <iostream>
#include <ctime>
#include <cstdlib>
#include <set>
#include <queue>

using namespace std;

int main() {
  srand(time(nullptr));

  priority_queue<int, vector<int>, less<int>> pq;

  for (int i = 0; i < 10; ++i) {
    pq.push(rand());
  }

  while (!pq.empty()) {
    cout << pq.top() << ' ';
    pq.pop();
  }
  cout << '\n';

  return 0;
}*/
/*#include <iostream>
#include <set>

using namespace std;

int main() {
  set<int, less<int>> s1;  // 升序排列
  set<int, greater<int>> s2;  // 降序排列

  s1.insert(1);
  s1.insert(5);
  s1.insert(3);

  s2.insert(1);
  s2.insert(5);
  s2.insert(3);

  typedef set<int>::iterator IT;

  cout << "s1: ";
  for (IT it = s1.begin(); it != s1.end(); ++it) {
    cout << *it << ' ';
  }
  cout << '\n';

  cout << "s2: ";
  for (IT it = s2.begin(); it != s2.end(); ++it) {
    cout << *it << ' ';
  }

  return 0;
}*/
/*#include <iostream>

using namespace std;

int fun1(int x, int y) {
  return x + y;
}

int fun2(int x, int y) {
  return x - y;
}

int fun3(int x, int y) {
  return x * y;
}

int fun4(int x, int y) {
  return x / y;
}

int func(int x, int y, int fun(int, int)) {
  return fun(x, y);
}

int main() {
  cout << func(4, 2, fun4);
  return 0;
}*/
/*#include <iostream>
#include <set>

using namespace std;

class CStudent {
 public:
  CStudent(int iID, string strName)
      : m_iID(iID), m_strName(strName) {}
  int m_iID;
  string m_strName;
};

// 伪函数类
class StuFunctor {
 public:
  bool operator()(const CStudent &left, const CStudent &right) const {
    return left.m_iID > right.m_iID;
  }
};

int main() {
  set<CStudent, StuFunctor> stu;

  stu.insert(CStudent(10, "xiaoming"));
  stu.insert(CStudent(8, "xiaowang"));
  stu.insert(CStudent(6, "xiaoma"));
  stu.insert(CStudent(12, "xiaozhou"));

  typedef set<CStudent, StuFunctor>::iterator IT;;

  for (IT it = stu.begin(); it != stu.end(); ++it) {
    cout << it->m_iID << ' ';
  }
  cout << '\n';

  return 0;
}*/
/*#include <iostream>

using namespace std;

const int SIZE = 101;

int main() {
  int n, m, q;

  scanf("%d%d%d", &n, &m, &q);

  int arr[SIZE][SIZE] = {0}, sum[SIZE][SIZE] = {0};

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &arr[i][j]);
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
    }
  }

  while (q--) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    printf("%d\n", sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] +
        sum[x1 - 1][y1 - 1]);
  }

  return 0;
}*/
/*#include <iostream>

using namespace std;

const int SIZE = 1010;

int n, m, q;
int arr[SIZE][SIZE], diff[SIZE][SIZE];

void insert(int x1, int y1, int x2, int y2, int value) {
  diff[x1][y1] += value;
  diff[x2 + 1][y1] -= value;
  diff[x1][y2 + 1] -= value;
  diff[x2 + 1][y2 + 1] += value;
}

int main() {
  scanf("%d%d%d", &n, &m, &q);

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &arr[i][j]);
      insert(i, j, i, j, arr[i][j]);
    }
  }

  while (q--) {
    int x1, y1, x2, y2, value;
    scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &value);
    insert(x1, y1, x2, y2, value);
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
      printf("%d ", diff[i][j]);
    }
    putchar('\n');
  }

  return 0;
}*/
/*#include <iostream>

using namespace std;

const int SIZE = 1010;

int arr[SIZE][SIZE], diff[SIZE][SIZE];

int n, m, q;

void insert(int x1, int y1, int x2, int y2, int value) {
  diff[x1][y1] += value;
  diff[x2 + 1][y1] -= value;
  diff[x1][y2 + 1] -= value;
  diff[x2 + 1][y2 + 1] += value;
}

int main() {
  scanf("%d%d%d", &n, &m, &q);

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &arr[i][j]);
      insert(i, j, i, j, arr[i][j]);
    }
  }

  while (q--) {
    int x1, y1, x2, y2, value;
    scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &value);
    insert(x1, y1, x2, y2, value);
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      diff[i][j] += diff[i][j - 1] + diff[i - 1][j] - diff[i - 1][j - 1];
      printf("%d ", diff[i][j]);
    }
    putchar('\n');
  }

  return 0;
}*/
/*#include <iostream>
#include <string>

using namespace std;

int main() {
  string s1(3,'a');
  string s2;
  cout << s1 << endl;
  s2.assign("as", 3);
  cout << s2 << endl;
  return 0;
}*/
/*#include <iostream>

using namespace std;

int main() {
  string s1("hello"), s2("hello world");
  int n = s1.compare(s2);
  n = s1.compare(1, 2, s2, 0, 3);
  n = s1.compare(0, 2, s2);
  n = s1.compare("Hello");
  n = s1.compare(1, 2, "Hello");
  n = s1.compare(1, 2, "Hello", 1, 2);
  return 0;
}*/
/*#include <iostream>

using namespace std;

int main() {
  string s1 = "this is ok";
  string s2 = s1.substr(1, 2);
  s2 = s1.substr(3);
  cout << s2 << endl;
  return 0;
}*/
/*#include <iostream>
#include <string>

using namespace std;

int main() {
  string s1("Hello World");
  cout << s1.find_first_of('e') << endl;
  cout << s1.find_last_of("W") << endl;
  cout << s1.find_first_not_of("o") << endl;
  cout << s1.find_last_not_of('r') << endl;
  cout << s1.rfind("ello") << endl;
  return 0;
}*/
/*#include <iostream>

using namespace std;

int main() {
  string s1("Real Steel");
  s1.replace(1, 3, "123456", 2, 4);

  string s2("Harry Potter");
  s2.replace(2, 3, 5, '0');

  int n = s2.find("00000");
  s2.replace(n, 5, "XXX");
  cout << s2 << endl;

  return 0;
}*/
/*#include <iostream>

using namespace std;

int main() {
  string s1("Real Steel");
  s1.erase(1, 3);
  cout << s1 << endl;
  s1.erase(5);
  cout << s1 << endl;
  return 0;
}*/
/*#include <iostream>
#include <string>

using namespace std;

int main() {
  string s1("Hello World"), s2("Hello World", 1, 3);
  string s3 = s1.substr(1, 2);
  s3 += s2;

  return 0;
}*/
/*#include <iostream>

using namespace std;

class A {
 public:
  A() { cout << "A()" << endl; }
  ~A() { cout << "~A()" << endl; }

  A(int a, int b) : x(a), y(b) {}

  int get_x() {
    return x;
  }
  int get_y() { return y; }
 private:
  int x;

 protected:
  int y;
};

class B : public A {
 public:
  B() {
    cout << "B()" << endl;
  }
  B(int a, int b) : A(a, b) {
    cout << "B(int a, int b) : A(a, b)" << endl;
  }
  ~B() {
    cout << "~B()" << endl;
  }
};

int main() {
  B b(10, 20);

  cout << b.get_x() << endl;
  cout << b.get_y() << endl;
  return 0;
}*/
/*#include <iostream>

using namespace std;

class A {
 public:
  void func() { cout << "A::func()" << endl; }
};

class B : public A {
 public:
  // 和基类中的成员函数名字相同，参数也相同，隐藏
  void func() { cout << "B::func()" << endl; }
  void func(int x) { cout << "B::func(int x)" << endl; }
};

int main() {
  B b;
  b.func();
  b.A::func();
  // 实现下面这个有参的函数，
  // 即使父类中有形参不一样但同名的函数，
  // 也不可以 b.func() 这样调用父类
  b.func(10);
  return 0;
}*/
/*#include <iostream>

using namespace std;

class A {
 public:
  int a_x;
};

class B : public A {
 public:
  int b_x;
};

class C : public A {
 public:
  int c_x;
};

class D : public B, public C {
 public:
  int d_x;
};

int main() {
  cout << sizeof(D) << endl;
  D d;
  d.B::a_x = 100;
  d.C::a_x = 200;
  cout << d.B::a_x << endl;
  cout << d.C::a_x << endl;
  return 0;
}*/
/*#include <iostream>
using namespace std;
class A {
 public:
  static int num;  // 声明
  static int func(int a) { return num; };
};
int A::num = 100;  // 定义
class B : public A {
 public:
  // 当派生类中有与基类同名的变量
  // 就会隐藏原来的
  static int num;
};
int B::num = 1000;
int main() {
  A a;
  a.num = 200;
  a.func(10);

  B b;
  b.num = 300;
  // 派生类能继承并且共享静态成员变量
  // 静态成员函数类似
  cout << A::num << endl;
  cout << B::num << endl;
  return 0;
}*/
/*#include <iostream>
#include <cstring>

using namespace std;

int func() {
  int x = 10;
  return x;
}

class Test {
 public:
  int data;
  char *ptr;

  Test() : data(0), ptr(new char[10]) {
    cout << "Test()" << endl;
  }

  Test(const Test &t) {
    data = t.data;
    if (strlen(t.ptr)) {
      ptr = new char[strlen(t.ptr)];
      strcpy(ptr, t.ptr);
    } else {
      ptr = new char[10];
    }
  }
  Test(int data, const char *src) {
    this->data = data;
    if (src && strlen(src)) {
      this->ptr = new char[strlen(src) + 1];
      strcpy(this->ptr, src);
    }
  }

  ~Test() {
    if (ptr) {
      delete[] ptr;
    }
  }

  Test operator+(const Test &t) {
    Test val;
    val.data = data + t.data;
    val.ptr = new char[strlen(ptr) + strlen(t.ptr) + 1];
    memset(val.ptr, 0, strlen(ptr) + strlen(t.ptr) + 1);
    strcat(val.ptr, ptr);
    strcat(val.ptr, t.ptr);
    return val;
  }

  Test &operator=(const Test &t) {
    delete[] ptr;
    ptr = new char[strlen(t.ptr) + 1];
    data = t.data;
    strcpy(ptr, t.ptr);
    return *this;
  }

  Test &operator++() {
    ++data;
    return *this;
  }

  Test operator++(int) {
    Test temp = *this;
    ++data;
    return temp;
  }

  friend ostream &operator<<(ostream &os, const Test &t) {
    return os << t.data << endl << t.ptr << endl;
  }
};*/
/*#include <iostream>

using namespace std;

class Hero {
 public:
  virtual void huicheng() { cout << "Hero::huicheng()" << endl; }

  void func() { cout << "Hero::func()" << endl; }
};

class Libai : public Hero {
 public:
  // 隐藏基类中的 func2 函数
  void func() { cout << "Libai::func()" << endl; }
  // 对基类中虚函数的重写（override）
  void huicheng() { cout << "Libai::huicheng()" << endl; }
};

class Caocao : public Hero {
 public:
  void func() { cout << "Caocao::func()" << endl; }
  void huicheng() { cout << "Caocao::huicheng()" << endl; }
};

class Houyi : public Hero {};

// 使用基类没有重写的 huicheng() 函数
void goback(Hero &h) {
  h.huicheng();
  h.func();
}

int main() {
  Libai libai;
  Caocao caocao;
  Houyi houyi;

  // libai 回城
  // 因为是虚函数，所以打印的是派生类对象
  goback(libai);
  goback(caocao);
  goback(houyi);

  return 0;
}*/
/*#include <iostream>
#include "test.h"

using namespace std;

class Hero {
 public:
  virtual void back() = 0;  // 纯虚函数
};

class LiBai : public Hero {
 public:
  void back() { cout << "LiBai::back()" << endl; }  // 重写
};

class CaoCao : public Hero {
 public:
  void back() { cout << "CaoCao::back()" << endl; }  // 重写
};

int main() {
  LiBai h1;
  CaoCao h2;
  Hero *p;

  p = &h1;
  p->back();

  p = &h2;
  p->back();

  return 0;
}*/
/*#include "test.h"

int main() {
  test();
  return 0;
}*/
/*#include <iostream>
#include <vector>

using namespace std;

int main() {
  try {
    vector<int> arr(3, 10);
    for (int i = 0; i < 3; ++i) {
      cout << arr.at(i) << endl;
    }
    arr.at(3) = 100;
  } catch (...) {
    cout << "Hello" << endl;
  }
  return 0;
}*/
/*#include <iostream>
#include <exception>
using namespace std;

int func(int a, int b) {
  if (b) {
    return a / b;
  } else {
    // 如果除数为 0，则打印调试语句
    cout << "division 0" << endl;
    // 抛出异常
    throw "error, hello world";
  }
}

int main() {
  try {
    func(10, 0);
  } catch (const char *msg) {
    cout << msg << endl;
  }
  return 0;
}*/
/*#include <iostream>
#include <vector>

using namespace std;

int main() {
  try {
    vector<int> arr(3, 10);
    for (int i = 0; i < 3; ++i) {
      cout << arr.at(i) << endl;
    }
    arr.at(3) = 100;
  } catch (out_of_range &err) {
    cout << err.what() << endl;
  }
}*/
/*#include <cstring>
#include <exception>

class FHeaderErr : public std::exception {
 public:
  const char *what() const throw() {
    return "frame header error";
  }
};

class FTailErr : public std::exception {
 public:
  const char *what() const throw() {
    return "frame tail error";
  }
};

bool func(const char *str) {
  if (!str) {
    throw "null pointer";
  }

  int len = strlen(str);

  if (!(str[0] == '#' && str[1] == '#')) {
    FHeaderErr err;
    throw(err);
  }

  if (!(str[len - 1] == '#' && str[len - 2] == '#')) {
    FTailErr err;
    throw(err);
  }

  return true;
}*/
/*#include <exception>

using namespace std;

class Err : public exception {
 public:
  const char *what() throw() {}
};*/
/*
template<class T>
class CMath {
 public:
  CMath(const T &t1, const T &t2)
      : m_t1(t1), m_t2(t2) {}
  T add();

 private:
  T m_t1;
  T m_t2;
};

template<class T>
T CMath<T>::add() {
  return m_t2 + m_t1;
}*/
/*
#include <iostream>

using namespace std;

template <class T>
class A {
 public:
  static void print() {
    cout << "&m_i" << &m_i <<',' << " &m_t: " << &m_t << endl;
  }
  static int m_i;
  static T m_t;
};

template <class T>
int A<T>::m_i;

template <class T>
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
/*
#include <iostream>
#include <iomanip>

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
      cout << setw(4) << left << array[i][j];
    }
    cout << '\n';
  }
  return 0;
}*/
/*#include <cstring>
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
}*/
/*#include <iostream>

using namespace std;

template<class T = short, class U = int>
class CMath {
 public:
  static void foo() {
    cout << "1:CMath<T, D>::foo" << endl;
  }
};

// 局部特化
// 只特化一部分类型参数
template<class T>
class CMath<short, T> {
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

int main() {
  CMath<int, double>::foo();  // 1
  CMath<int, short>::foo();  // 2
  return 0;
}*/
/*#include <iostream>

using namespace std;

template<class T = int, class U =short>
class CMath {
 public:
  void foo() {

  }
};

template<class T>
class CMath<short, T> {
 public:
  void foo() {

  }
};

template<>
class CMath<short, int> {
 public:
  void foo() {

  }
};

template<class T, size_t S = 20>
class Array {
 public:
  T &operator[](size_t i) {
    return m_arr[i];
  }
  size_t size() { return S; }

 private:
  T m_arr[S];
};

int main() {
  Array<int, 20> a;

  for (int i = 0; i < a.size(); ++i) {
    a[i] = i + 1;
  }
}*/
/*
template<class T>
class Array {
 public:
  T &operator[](int i) {
    return m_arr[i];
  }

 private:
  T m_arr[10];
};

template<class T>
class Sum {
 public:
  Sum(Array<T> &s) : m_s(s) {}
  T add() {
    T t = 0;
    for (int i = 0; i < 10; ++i) {
      t += m_s[i];
    }
    return t;
  }
 private:
  Array<T> m_s;
};*/
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

template<class X>
template<class Y>
template<class Z>
class A<X>::B<Y>::C {
 public:
  template<class D>
  void foo() {
    cout << "foo()" << endl;
  }
};

int main() {
  A<int>::B<double>::C<char> c;
  c.foo<int>();
  return 0;
}*/
/*
#include <iostream>

using namespace std;

template <class T, size_t S = 15>
class Array {
 public:
  T &operator[](size_t i) {
    return m_arr[i];
  }

 private:
  T m_arr[S];
};

template<class T, template<class, size_t S = 15> class D, size_t S = 15>
class Sum{
 public:
  Sum(D<T, S> d):m_s(d) {}

  T add() {
    T t = 0;
    for (int i = 0; i < S; ++i) {
      t += m_s[i];
    }
    return t;
  }

 private:
  D<T> m_s;
};*/
/*
#include <iostream>

using namespace std;

class A {
 public:
  class B {
   public:
    void foo() {
      cout << "A::B::foo()" << endl;
    }
  };
};

template<class T>
void Func() {
  typename T::B b;
  b.foo();
}*/
/*#include <iostream>

using namespace std;

template<class D>
void foo() {
  D d;
  d.template func<int>();
}*/
/*#include <iostream>

using namespace std;

int main() {
  int arr[10] = {1, 2, 2, 3, 3, 3, 4, 4, 5, 5};
  int x = 0;
  cin >> x;

  int left = 0, right = 9;

  while (left < right) {
    int mid = left + (right - left) / 2;

    if (arr[mid] >= x) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }

  cout << left << ' ';

  left = 0, right = 9;

  while (left < right) {
    int mid = left + (right - left + 1) / 2;

    if (arr[mid] <= x) {
      left = mid;
    } else {
      right = mid - 1;
    }
  }

  cout << left << endl;

  return 0;
}*/
/*#include <iostream>

using namespace std;

int main() {
  int arr[10] = {1, 1, 1, 2, 2, 3, 3, 3, 3, 4};
  int x;
  cin >> x;

  int left = 0, right = 9;

  while (left < right) {
    int mid = left + (right - left) / 2;

    if (arr[mid] >= x) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  cout << left << ' ';

  left = 0, right = 9;
  while (left < right) {
    int mid = left + (right - left + 1) / 2;

    if (arr[mid] <= x) {
      left = mid;
    } else {
      right = mid - 1;
    }
  }
  cout << right << endl;

  return 0;
}*/
/*#include <iostream>

using namespace std;

int main() {
  double x;
  cin >> x;

  double l = 0, r = x;

  while (r - l > 1e-8) {
    double mid = (l + r) / 2;

    if (mid * mid >= x) {
      r = mid;
    } else {
      l = mid;
    }
  }

  cout << l << endl;

  return 0;
}*/
/*#include <iostream>
#include <vector>

using namespace std;

vector<int> add(const vector<int> &v1, const vector<int> &v2) {
  vector<int> sum;

  int carry = 0;

  int max_size = max(v1.size(), v2.size());

  for (int i = 0; i < max_size; ++i) {
    if (i < v1.size()) {
      carry += v1[i];
    }

    if (i < v2.size()) {
      carry += v2[i];
    }

    sum.push_back(carry % 10);

    carry /= 10;
  }

  if (carry) {
    sum.push_back(1);
  }

  return sum;
}*/
/*#include <vector>

using namespace std;

vector<int> add(vector<int> &v1, vector<int> &v2) {
  vector<int> sum;

  int carry = 0;

  int max_size = max(v1.size(), v2.size());

  for (int i = 0; i < max_size; ++i) {
    if (i < v1.size()) {
      carry += v1[i];
    }

    if (i < v2.size()) {
      carry += v2[i];
    }

    sum.push_back(carry % 10);

    carry /= 10;
  }

  if (carry) {
    sum.push_back(1);
  }

  return sum;
}*/
/*#include <vector>

using namespace std;

vector<int> add(vector<int> &v1, vector<int> &v2) {
  vector<int> sum;

  int carry = 0;

  int max_size = max(v1.size(), v2.size());

  for (int i = 0; i < max_size; ++i) {
    if (i < v1.size()) {
      carry += v1[i];
    }

    if (i < v2.size()) {
      carry += v2[i];
    }

    sum.push_back(carry % 10);

    carry /= 10;
  }

  if (carry) {
    sum.push_back(1);
  }

  return sum;
}*/
/*#include <vector>

using namespace std;

vector<int> add(const vector<int> &v1, const vector<int> &v2) {
  vector<int> sum;

  int carry = 0;

  int max_size = max(v1.size(), v2.size());

  for (int i = 0; i < max_size; ++i) {
    if (i < v1.size()) {
      carry += v1[i];
    }

    if (i < v2.size()) {
      carry += v2[i];
    }

    sum.push_back(carry % 10);

    carry /= 10;
  }

  if (carry) {
    sum.push_back(1);
  }

  return sum;
}*/
/*#include <vector>

using namespace std;

vector<int> add(const vector<int> &v1, const vector<int> &v2) {
  vector<int> sum;

  int carry = 0;

  int max_size = max(v1.size(), v2.size());

  for (int i = 0; i < max_size; ++i) {
    if (i < v1.size()) {
      carry += v1[i];
    }

    if (i < v2.size()) {
      carry += v2[i];
    }

    sum.push_back(carry % 10);

    carry /= 10;
  }

  if (carry) {
    sum.push_back(1);
  }

  return sum;
}*/
/*#include <vector>

using namespace std;

vector<int> add(const vector<int> &v1, const vector<int> &v2) {
  vector<int> sum;

  int max_size = max(v1.size(), v2.size());

  int carry = 0;

  for (int i = 0; i < max_size; ++i) {
    if (i < v1.size()) {
      carry += v1[i];
    }

    if (i < v2.size()) {
      carry += v2[i];
    }

    sum.push_back(carry % 10);

    carry /= 10;
  }

  if (carry) {
    sum.push_back(1);
  }

  return sum;
}

bool cmp(const vector<int> &v1, const vector<int> &v2) {
  if (v1.size() != v2.size()) {
    return v1.size() > v2.size();
  }

  for (int i = v1.size() - 1; i >= 0; --i) {
    if (v1[i] != v2[i]) {
      return v1[i] > v2[i];
    }
  }

  return true;
}

vector<int> sub(const vector<int> &v1, const vector<int> &v2) {
  vector<int> res;
  int carry = 0;

  for (int i = 0; i < v1.size(); ++i) {
    int diff = v1[i] - carry;

    if (i < v2.size()) {
      diff -= v2[i];
    }

    res.push_back((diff + 10) % 10);

    carry = diff < 0 ? 1 : 0;
  }

  while (res.size() > 1 && res.back() == 0) {
    res.pop_back();
  }

  return res;
}*/
/*#include <vector>

using namespace std;

bool cmp(const vector<int> &v1, const vector<int> &v2) {
  if (v1.size() != v2.size()) {
    return v1.size() > v2.size();
  }

  for (int i = v1.size() - 1; i >= 0; --i) {
    if (v1[i] != v2[i]) {
      return v1[i] > v2[i];
    }
  }

  return true;
}

vector<int> sub(const vector<int> &v1, const vector<int> &v2) {
  vector<int> res;

  int carry = 0;

  for (int i = 0; i < v1.size(); ++i) {
    int diff = v1[i] - carry;

    if (i < v2.size()) {
      diff -= v2[i];
    }

    res.push_back((diff + 10) % 10);

    carry = diff < 0 ? 1 : 0;
  }

  while (res.size() > 1 && res.back() == 0) {
    res.pop_back();
  }

  return res;
}

vector<int> mul(const vector<int> &n, int m) {
  vector<int> prod;

  int carry = 0;

  for (int i = 0; i < n.size() || carry; ++i) {
    if (i < n.size()) {
      carry += n[i] * m;
    }

    prod.push_back(carry % 10);

    carry /= 10;
  }

  return prod;
}*/
/*#include <vector>

using namespace std;

vector<int> mul(const vector<int> &n, int m) {
  vector<int> prod;

  int carry = 0;

  for (int i = 0; i < n.size() || carry; ++i) {
    if (i < n.size()) {
      carry += n[i] * m;
    }

    prod.push_back(carry % 10);

    carry /= 10;
  }

  return prod;
}*/
/*#include <vector>

using namespace std;

vector<int> mul(const vector<int> &n, int m) {
  vector<int> prod;

  int carry = 0;

  for (int i = 0; i < n.size() || carry; ++i) {
    if (i < n.size()) {
      carry += n[i] * m;
    }

    prod.push_back(carry % 10);

    carry /= 10;
  }

  return prod;
}*/
/*#include <vector>

using namespace std;

vector<int> mul(const vector<int> &n, int m) {
  vector<int> prod;

  int carry = 0;

  for (int i = 0; i < n.size() || carry; ++i) {
    if (i < n.size()) {
      carry += n[i] * m;
    }

    prod.push_back(carry % 10);

    carry /= 10;
  }

  return prod;
}*/
/*#include <vector>

using namespace std;

vector<int> mul(const vector<int> &n, int m) {
  vector<int> prod;

  int carry = 0;

  for (int i = 0; i < n.size() || carry; ++i) {
    if (i < n.size()) {
      carry += n[i] * m;
    }

    prod.push_back(carry % 10);

    carry /= 10;
  }

  return prod;
}*/
/*#include <vector>

using namespace std;

vector<int> mul(const vector<int> &n, int m) {
  vector<int> prod;

  int carry = 0;

  for (int i = 0; i < n.size() || carry; ++i) {
    if (i < n.size()) {
      carry = n[i] * m;
    }

    prod.push_back(carry % 10);

    carry /= 10;
  }

  return prod;
}*/
/*#include <vector>

using namespace std;

vector<int> mul(const vector<int> &n, int m) {
  vector<int> prod;

  int carry = 0;

  for (int i = 0; i < n.size() || carry; ++i) {
    if (i < n.size()) {
      carry += n[i] * m;
    }

    prod.push_back(carry % 10);

    carry /= 10;
  }

  return prod;
}

vector<int> add(const vector<int> &v1, const vector<int> &v2) {
  vector<int> sum;

  int carry = 0;

  int max_size = max(v1.size(), v2.size());

  for (int i = 0; i < max_size || carry; ++i) {
    if (i < v1.size()) {
      carry += v1[i];
    }

    if (i < v2.size()) {
      carry += v2[i];
    }

    sum.push_back(carry % 10);

    carry /= 10;
  }

  return sum;
}

vector<int> div(const vector<int> &num, int d, int &rem) {
  vector<int> quot;

  int carry = 0;

  for (int i = num.size() - 1; i >= 0; --i) {
    rem = rem * 10 + num[i];
    quot.push_back(rem / d);
    rem %= 10;
  }

  reverse(quot.begin(), quot.end());

  while (quot.size() > 1 && quot.back() == 0) {
    quot.pop_back();
  }

  return quot;
}*/
/*#include <vector>

using namespace std;

vector<int> div(const vector<int> &num, int d, int &rem) {
  vector<int> quot;

  int carry = 0;

  for (int i = num.size() - 1; i >= 0; --i) {
    rem = rem * 10 + num[i];
    quot.push_back(rem / d);
    rem %= 10;
  }

  reverse(quot.begin(), quot.end());

  while (quot.size() > 1 && quot.back()) {
    quot.pop_back();
  }

  return quot;
}*/
/*#include <vector>

using namespace std;

vector<int> div(const vector<int> &num, int d, int &rem) {
  vector<int> quot;

  int carry = 0;

  for (int i = num.size() - 1; i >= 0; --i) {
    rem = rem * 10 + num[i];
    quot.push_back(rem / d);
    rem %= 10;
  }

  reverse(quot.begin(), quot.end());

  while (quot.size() > 1 && quot.back() == 0) {
    quot.pop_back();
  }

  return quot;
}*/
/*#include <vector>

using namespace std;

vector<int> div(const vector<int> &num, int d, int &rem) {
  vector<int> quot;

  int carry = 0;

  for (int i = num.size() - 1; i >= 0; --i) {
    rem = rem * 10 + num[i];
    quot.push_back(rem / d);
    rem %= 10;
  }

  reverse(quot.begin(), quot.end());

  while (quot.size() > 1 && quot.back() == 0) {
    quot.pop_back();
  }

  return quot;
}*/
/*#include <vector>

using namespace std;

vector<int> div(const vector<int> &num, int d, int &rem) {
  vector<int> quot;

  int carry = 0;

  for (int i = num.size() - 1; i >= 0; --i) {
    rem = rem * 10 + num[i];
    quot.push_back(rem / d);
    rem %= 10;
  }

  reverse(quot.begin(), quot.end());

  while (quot.size() > 1 && quot.back() == 0) {
    quot.pop_back();
  }

  return quot;
}*/
/*#include <vector>

using namespace std;

vector<int> div(const vector<int> &num, int d, int &rem) {
  vector<int> quot;

  int carry = 0;

  for (int i = num.size() - 1; i >= 0; --i) {
    rem = rem * 10 + num[i];
    quot.push_back(rem / d);
    rem %= 10;
  }

  reverse(quot.begin(), quot.end());

  while (quot.size() > 1 && quot.back() == 0) {
    quot.pop_back();
  }

  return quot;
}*/
/*
#include <vector>

using namespace std;

vector<int> div(const vector<int> &num, int d, int &rem) {
  vector<int> quot;

  int carry = 0;

  for (int i = num.size() - 1; i >= 0; --i) {
    rem = rem * 10 + num[i];
    quot.push_back(rem / d);
    rem %= 10;
  }

  reverse(quot.begin(), quot.end());

  while (quot.size() > 1 && quot.back() == 0) {
    quot.pop_back();
  }

  return quot;
}*/
/*#include <vector>

using namespace std;

vector<int> div(const vector<int> &num, int d, int &rem) {
  vector<int> quot;
  int carry = 0;
  for (int i = num.size() - 1; i >= 0; --i) {
    rem = rem * 10 + num[i];
    quot.push_back(rem / d);
    rem %= 10;
  }

  reverse(quot.begin(), quot.end());

  while (quot.size() > 1 && quot.back() == 0) {
    quot.pop_back();
  }

  return quot;
}*/
/*#include <vector>

using namespace std;

vector<int> div(const vector<int> num, int d, int &rem) {
  vector<int> quot;

  int carry = 0;

  for (int i = num.size() - 1; i >= 0; --i) {
    rem = rem * 10 + num[i];
    quot.push_back(rem / d);
    rem %= 10;
  }

  reverse(quot.begin(), quot.end());

  while (quot.size() > 1 && quot.back() == 0) {
    quot.pop_back();
  }

  return quot;
}*/
/*#include <vector>

using namespace std;

vector<int> div(const vector<int> &num, int d, int &rem) {
  vector<int> quot;
  int carry = 0;
  for (int i = num.size() - 1; i >= 0; --i) {
    rem = rem * 10 + num[i];
    quot.push_back(rem / d);
    rem %= 10;
  }
  reverse(quot.begin(), quot.end());
  while (quot.size() > 1 && quot.back() == 0) {
    quot.pop_back();
  }
  return quot;
}*/
/*#include <vector>

using namespace std;

vector<int> div(const vector<int> &num, int d, int &rem) {
  vector<int> quot;
  int carry = 0;
  for (int i = num.size() - 1; i >= 0; --i) {
    rem = rem * 10 + num[i];
    quot.push_back(rem / d);
    rem %= 10;
  }
  reverse(quot.begin(), quot.end());
  while (quot.size() > 1 && quot.back() == 0) {
    quot.pop_back();
  }
  return quot;
}*/
/*#include <vector>
using namespace std;
vector<int> div(const vector<int> &num, int d, int &rem) {
  vector<int> quot;
  for (int i = num.size() - 1; i >= 0; --i) {
    rem = rem * 10 + num[i];
    quot.push_back(rem / d);
    rem %= 10;
  }
  reverse(quot.begin(), quot.end());
  while (quot.size() > 1 && quot.back() == 0) {
    quot.pop_back();
  }
  return quot;
}*/
/*#include <iostream>
#include <vector>

using namespace std;

const int LEN = 100010;

int main() {
  int n, m;
  vector<int> arr(LEN), sum(LEN);
  scanf("%d%d", &n, &m);
  for (int i = 0; i <= n; ++i) {
    scanf("%d", &arr[i]);
  }
  for (int i = 1; i <= n; ++i) {
    sum[i] = sum[i - 1] + arr[i];
  }
  while (m--) {
    int left, right;
    scanf("%d%d", &left, &right);
    printf("%d\n", sum[right] - sum[left - 1]);
  }
  return 0;
}*/
/*#include <iostream>
#include <vector>

using namespace std;

const int LEN = 100010;

int main() {
  int n, m;
  vector<int> arr(LEN), sum(LEN);
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    cin >> arr[i];
    sum[i] = sum[i - 1] + arr[i];
  }
  while (m--) {
    int left, right;
    cin >> left >> right;
    cout << sum[right] - sum[left - 1] << endl;
  }
  return 0;
}*/
/*#include <iostream>
#include <vector>

using namespace std;

const int LEN = 100010;

int main() {
  int n, m;
  vector<int> arr(LEN), sum(LEN);

  scanf("%d%d", &n, &m);

  for (int i = 1; i <= n; ++i) {
    scanf("%d", &arr[i]);
  }

  for (int i = 1; i <= n; ++i) {
    sum[i] = sum[i - 1] + arr[i];
  }

  while (m--) {
    int left, right;
    scanf("%d%d", &left, &right);
    printf("%d\n", sum[right] - sum[left - 1]);
  }

  return 0;
}*/
/*#include <iostream>
#include <vector>

using namespace std;

const int LEN = 100010;

int main() {
  int n, m;
  vector<int> arr(LEN), sum(LEN);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> arr[i];
  }
  for (int i = 1; i <= n; ++i) {
    sum[i] = sum[i - 1] + arr[i];
  }
  while (m--) {
    int left, right;
    cin >> left >> right;
    cout << sum[right] - sum[left - 1] << endl;
  }

  return 0;
}*/
/*#include <iostream>
#include <vector>

using namespace std;

const int LEN =100010;

int main() {
  int n, m;
  vector<int> arr(LEN), sum(LEN);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> arr[i];
    sum[i] = sum[i - 1] + arr[i];
  }
  while (m--) {
    int left, right;
    cin >> left >> right;
    cout << sum[right] - sum[left - 1] << endl;
  }
  return 0;
}*/
/*#include <iostream>
#include <vector>

using namespace std;

const int LEN = 100010;

int main() {
  int n, m;
  vector<int> arr(LEN), sum(LEN);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> arr[i];
    sum[i] = sum[i - 1] + arr[i];
  }
  while (m--) {
    int left, right;
    cin >> left >> right;
    cout << sum[right] - sum[left - 1] << endl;
  }
  return 0;
}*/
/*#include <iostream>
#include <vector>

using namespace std;

const int LEN = 100010;

int main() {
  int n, m;
  vector<int> arr(LEN), sum(LEN);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> arr[i];
    sum[i] = sum[i - 1] + arr[i];
  }
  while (m--) {
    int left, right;
    cin >> left >> right;
    cout << sum[right] - sum[left - 1] << endl;
  }
  return 0;
}*/
/*#include <iostream>
#include <vector>
using namespace std;
const int SIZE = 10001;
int main() {
  vector<vector<int>> arr(SIZE, vector<int>(SIZE)), sum(SIZE, vector<int>(SIZE));

  int n, m, q;

  cin >> n >> m >> q;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> arr[i][j];
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
    }
  }

  while (q--) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    cout << sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] + sum[x1 - 1][y1 - 1];
  }

  return 0;
}*/
/*#include <iostream>
#include <vector>
using namespace std;
const int SIZE = 10001;
int main() {
  vector<vector<int>> arr(SIZE, vector<int>(SIZE)), sum(SIZE, vector<int>(SIZE));
  int n, m, q;
  cin >> n >> m >> q;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      cin >> arr[i][j];
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
    }
  }
  while (q--) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    cout << sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] + sum[x1 - 1][y1 - 1];
  }
  return 0;
}*/
/*#include <iostream>
#include <vector>
using namespace std;
const int SIZE = 10001;
int main() {
  vector<vector<int>> arr(SIZE, vector<int>(SIZE)), sum(SIZE, vector<int>(SIZE));
  int n, m, q;
  cin >> n >> m >> q;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> arr[i][j];
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
    }
  }
  while (q--) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    cout << sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] + sum[x1 - 1][y1 - 1] << endl;
  }
  return 0;
}*/
/*#include <iostream>
#include <vector>
using namespace std;
const int SIZE = 10001;
int main() {
  vector<vector<int>> arr(SIZE, vector<int>(SIZE)), sum(SIZE, vector<int>(SIZE));
  int n, m, q;
  cin >> n>> m>> q;
  for (int i = 1;i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> arr[i][j];
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
    }
  }
  while (q--) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    cout << sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] + arr[x1 - 1][y1 - 1] << endl;
  }
  return 0;
}*/
/*#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 10001;

int main() {
  vector<vector<int>> arr(SIZE, vector<int>(SIZE)),
      sum(SIZE, vector<int>(SIZE));

  int n, m, q;

  scanf("%d%d%d", &n, &m, &q);

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &arr[i][j]);
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
    }
  }

  while (q--) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    printf("%d\n", sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] +
        sum[x1 - 1][y1 - 1]);
  }

  return 0;
}*/
/*#include <iostream>
#include <vector>
using namespace std;
const int SIZE = 10010;
int main() {
  vector<vector<int>> arr(SIZE, vector<int>(SIZE)), sum(SIZE, vector<int>(SIZE));
  int n, m, q;
  cin >> n >> m >> q;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> arr[i][j];
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
    }
  }
  while (q--) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    cout << sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1] << endl;
  }
  return 0;
}*/
/*#include <iostream>
#include <vector>

using namespace std;

const int LEN = 100010;

int main() {
  int n, m;
  vector<int> arr(LEN), sum(LEN);

  cin >> n >> m;

  for (int i = 1; i <= n; ++i) {
    cin >> arr[i];
    sum[i] = sum[i - 1] + arr[i];
  }

  while (m--) {
    int left, right;
    cin >> left >> right;
    cout << sum[right] - sum[left - 1] << endl;
  }

  return 0;
}*/
/*#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 10001;

int main() {
  vector<vector<int>> arr(SIZE, vector<int>(SIZE)), sum(SIZE, vector<int>(SIZE));

  int n, m, q;

  cin >> n >> m >> q;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> arr[i][j];
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
    }
  }

  while (q--) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    cout << sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] + sum[x1 - 1][y1 - 1] << endl;
  }

  return 0;
}*/
/*#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 10001;

int main() {
  int n, m, q;
  vector<vector<int>> arr(SIZE, vector<int>(SIZE)), sum(SIZE, vector<int>(SIZE));

  cin >> n >> m >> q;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> arr[i][j];
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
    }
  }

  while (q--) {
    int x1, x2, y1, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    cout << sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1] << endl;
  }

  return 0;
}*/
/*#include <iostream>

using namespace std;

const int SIZE = 100010;

int n, m;
int arr[SIZE], diff[SIZE];

void insert(int left, int right, int value) {
  diff[left] += value;
  diff[right + 1] -= value;
}

int main() {
  cin >> n >> m;

  for (int i = 1; i <= n; ++i) {
    cin >> arr[i];
    insert(i, i, arr[i]);
  }

  while (m--) {
    int left, right, value;
    cin >> left >> right >> value;
    insert(left, right, value);
  }

  for (int i = 1; i <= n; ++i) {
    diff[i] += diff[i - 1];
    cout << diff[i] << ' ';
  }

  return 0;
}*/
/*#include <iostream>

using namespace std;

const int SIZE = 100010;

int n, m;
int arr[SIZE], diff[SIZE];

void insert(int left, int right, int value) {
  diff[left] += value;
  diff[right + 1] -= value;
}

int main() {
  cin >> n >> m;

  for (int i = 1; i <= n; ++i) {
    cin >> arr[i];
    insert(i, i, arr[i]);
  }

  while (m--) {
    int left, right, value;
    cin >> left >> right >> value;
    insert(left, right, value);
  }

  for (int i = 1; i <= n; ++i) {
    diff[i] += diff[i - 1];
    cout << diff[i];
  }

  return 0;
}*/
/*#include <iostream>

using namespace std;

const int SIZE = 100010;

int n, m;

int arr[SIZE], diff[SIZE];

void insert(int left, int right, int value) {
  diff[left] += value;
  diff[right + 1] -= value;
}

int main() {
  cin >> n >> m;

  for (int i = 1; i <= n; ++i) {
    cin >> arr[i];
    insert(i, i, arr[i]);
  }

  while (m--) {
    int left, right, value;
    cin >> left >> right >> value;
    insert(left, right, value);
  }

  for (int i = 1; i <= n; ++i) {
    diff[i] += diff[i - 1];
    cout << diff[i] << ' ';
  }

  return 0;
}*/
/*#include <iostream>

using namespace std;

const int SIZE = 100010;

int n, m;
int arr[SIZE], diff[SIZE];

void insert(int left, int right, int value) {
  diff[left] += value;
  diff[right + 1] -= value;
}

int main() {
  cin >> n >> m;

  for (int i = 1; i<= n; ++i) {
    cin >> arr[i];
    insert(i, i, arr[i]);
  }

  while (m--) {
    int left, right, value;
    cin >> left >> right >> value;
    insert(left, right, value);
  }

  for (int i = 1; i <= n; ++i) {
    diff[i] += diff[i - 1];
    cout << diff[i] << ' ';
  }

  return 0;
}*/
/*#include <iostream>

using namespace std;

const int SIZE = 100010;

int arr[SIZE], diff[SIZE];
int n, m;

void insert(int left, int right, int value) {
  diff[left] += value;
  diff[right + 1] -= value;
}

int main() {
  cin >> n >> m;

  for (int i = 1; i <= n; ++i) {
    cin >> arr[i];
    insert(i, i, arr[i]);
  }

  while (m--) {
    int left, right, value;
    cin >> left >> right >> value;
    insert(left, right, value);
  }

  for (int i = 1; i <= n; ++i) {
    diff[i] += diff[i - 1];
    cout << diff[i] << ' ';
  }

  return 0;
}*/
/*#include <iostream>

using namespace std;

const int SIZE = 100010;

int arr[SIZE], diff[SIZE], n, m;

void insert(int left, int right, int value) {
  diff[left] += value;
  diff[right + 1] -= value;
}

int main() {
  cin >> n >> m;

  for (int i = 1; i <= n; ++i) {
    cin >> arr[i];
    insert(i, i, arr[i]);
  }

  while (m--) {
    int left, right, value;
    cin >> left >> right >> value;
    insert(left, right, value);
  }

  for (int i = 1; i <= m; ++i) {
    diff[i] += diff[i - 1];
    cout << diff[i] << ' ';
  }

  return 0;
}*/
/*#include <iostream>

using namespace std;

const int SIZE = 1010;

int n, m, q;
int arr[SIZE][SIZE], diff[SIZE][SIZE];

void insert(int x1, int y1, int x2, int y2, int value) {
  diff[x1][y1] += value;
  diff[x2 + 1][y1] -= value;
  diff[x1][y2 + 1] -= value;
  diff[x2 + 1][y2 + 1] += value;
}

int main() {
  cin >> n >> m >> q;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> arr[i][j];
      insert(i, j, i, j, arr[i][j]);
    }
  }

  while (q--) {
    int x1, y1, x2, y2, value;
    cin >> x1 >> y1 >> x2 >> y2 >> value;
    insert(x1, y1, x2, y2, value);
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
      cout << diff[i][j] << ' ';
    }
    cout << endl;
  }

  return 0;
}*/
/*#include <iostream>

using namespace std;

const int SIZE = 1010;

int n, m, q;
int arr[SIZE][SIZE], diff[SIZE][SIZE];

void insert(int x1, int y1, int x2, int y2, int value) {
  diff[x1][y1] += value;
  diff[x2 + 1][y1] -= value;
  diff[x1][y2 + 1] -= value;
  diff[x2 + 1][y2 + 1] += value;
}

int main() {
  cin >> n >> m >> q;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> arr[i][j];
      insert(i, j, i, j, arr[i][j]);
    }
  }

  while (q--) {
    int x1, y1, x2, y2, value;
    cin >> x1 >> y1 >> x2 >> y2 >> value;
    insert(x1, y1, x2, y2, value);
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
      cout << diff[i][j] << ' ';
    }
    cout << endl;
  }

  return 0;
}*/
/*#include <iostream>

using namespace std;

const int SIZE = 1010;

int n, m, q;
int arr[SIZE][SIZE], diff[SIZE][SIZE];

void insert(int x1, int y1, int x2, int y2, int value) {
  diff[x1][y1] += value;
  diff[x2 + 1][y1] -= value;
  diff[x1][y2 + 1] -= value;
  diff[x2 + 1][y2 + 1] += value;
}

int main() {
  cin >> n >> m >> q;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> arr[i][j];
      insert(i, j, i, j, arr[i][j]);
    }
  }

  while (q--) {
    int x1, y1, x2, y2, value;
    cin >> x1 >> y1 >> x2 >> y2 >> value;
    insert(x1, y1, x2, y2, value);
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
      cout << diff[i][j] << ' ';
    }
    cout << endl;
  }

  return 0;
}*/
/*#include <iostream>

using namespace std;

const int SIZE = 1010;

int n, m, q;
int arr[SIZE][SIZE], diff[SIZE][SIZE];

void insert(int x1, int y1, int x2, int y2, int value) {
  diff[x1][y1] += value;
  diff[x2 + 1][y1] -= value;
  diff[x1][y2 + 1] -= value;
  diff[x2 + 1][y2 + 1] += value;
}

int main() {
  cin >> n >> m >> q;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> arr[i][j];
      insert(i, j, i, j, arr[i][j]);
    }
  }

  while (q--) {
    int x1, y1, x2, y2, value;
    cin >> x1 >> y1 >> x2 >> y2 >> value;
    insert(x1, y1, x2, y2, value);
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
      cout << diff[i][j] << ' ';
    }
    cout << endl;
  }

  return 0;
}*/
/*#include <iostream>

using namespace std;

const int SIZE = 1010;

int n, m, q;
int arr[SIZE][SIZE], diff[SIZE][SIZE];

void insert(int x1, int y1, int x2, int y2, int value) {
  diff[x1][y1] += value;
  diff[x2 + 1][y1] -= value;
  diff[x1][y2 + 1] -= value;
  diff[x2 + 1][y2 + 1] += value;
}

int main() {
  cin >> n >> m >> q;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> arr[i][j];
      insert(i, j, i, j, arr[i][j]);
    }
  }

  while (q--) {
    int x1, y1, x2, y2, value;
    cin >> x1 >> y1 >> x2 >> y2 >> value;
    insert(x1, y1, x2, y2, value);
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
      cout << diff[i][j] << ' ';
    }
    cout << endl;
  }

  return 0;
}*/
/*#include <iostream>

using namespace std;

const int SIZE = 1010;

int n, m, q;

int arr[SIZE][SIZE], diff[SIZE][SIZE];

void insert(int x1, int y1, int x2, int y2, int value) {
  diff[x1][y1] += value;
  diff[x2 + 1][y1] -= value;
  diff[x1][y2 + 1] -= value;
  diff[x2 + 1][y2 + 1] += value;
}



int main() {
  cin >> n >> m >> q;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> arr[i][j];
      insert(i, j, i, j, arr[i][j]);
    }
  }

  while (q--) {
    int x1, y1, x2, y2, value;
    cin >> x1 >> y1 >> x2 >> y2 >> value;
    insert(x1, y1, x2, y2, value);
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      diff[i][j] += diff[i][j - 1] + diff[i - 1][j] - diff[i - 1][j - 1];
      cout << diff[i][j] << ' ';
    }
    cout << endl;
  }

  return 0;
}*/
/*
#include <iostream>

using namespace std;

const int SIZE = 1010;

int n, m, q;
int arr[SIZE][SIZE], diff[SIZE][SIZE];

void insert(int x1, int y1, int x2, int y2, int value) {
  diff[x1][y1] += value;
  diff[x2 + 1][y1] -= value;
  diff[x1][y2 + 1] -= value;
  diff[x2 + 1][y2 + 1] += value;
}

template<class T>
void quickSort(T *arr, int left, int right) {
  if (left >= right) {
    return;
  }

  T x = arr[left];
  int i = left - 1, j = right + 1;

  while (i < j) {
    do {
      ++i;
    } while (arr[i] < x);

    do {
      --j;
    } while (arr[j] > x);

    if (i < j) {
      swap(arr[i], arr[j]);
    }
  }

  quickSort(arr, left, j);
  quickSort(arr, j + 1, right);
}

template <class T>
void mergeSort(T *arr, int left, int right) {
  if (left >= right) {
    return;
  }
}

int main() {
  cin >> n >> m >> q;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> arr[i][j];
      insert(i, j, i, j, arr[i][j]);
    }
  }

  while (q--) {
    int x1, y1, x2, y2, value;
    cin >> x1 >> y1 >> x2 >> y2 >> value;
    insert(x1, y1, x2, y2, value);
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
      cout << diff[i][j] << ' ';
    }
    cout << endl;
  }

  return 0;
}*/
/*
template<class T>
void mergeSort(T *arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;

  mergeSort(arr, left, mid);
  mergeSort(arr, mid + 1, right);

  int i = left, j = mid + 1, k = 0;

  T *temp = new T[right - left + 1];

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j]) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
    }
  }

  while (i <= mid) {
    temp[k++] = arr[i++];
  }

  while (j <= right) {
    temp[k++] = arr[j++];
  }

  for (i = left, j = 0; i <= right; ++i, ++j) {
    arr[i] = temp[j];
  }

  delete[]temp;
}*/
/*template<class T>
void mergeSort(T *arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;

  mergeSort(arr, left, mid);
  mergeSort(arr, mid + 1, right);

  T *temp = new T[right - left + 1];

  int i = left, j = mid + 1, k = 0;

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j]) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
    }
  }

  while (i <= mid) {
    temp[k++] = arr[i++];
  }

  while (j <= right) {
    temp[k++] = arr[j++];
  }

  for (i = left, j = 0; i <= right; ++i, ++j) {
    arr[i] = temp[j];
  }

  delete[] temp;
}*/
/*#include <iostream>

using namespace std;

int main() {
  int arr[10] = {1, 1, 2, 2, 2, 3, 3, 3, 3, 4};
  int x;
  cin >> x;

  int left = 0, right = 10;

  while (left < right) {
    int mid = left + (right - left) / 2;
    if (arr[mid] >= x) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  cout << left << ' ';

  left = 0, right = 10;
  while (left < right) {
    int mid = left + (right - left + 1) / 2;
    if (arr[mid] <= x) {
      left = mid;
    } else {
      right = mid - 1;
    }
  }
  cout << left << endl;

  return 0;
}*/
/*#include <iostream>

using namespace std;

int main() {
  int arr[10] = {1, 1, 2, 2, 2, 3, 3, 3, 4, 4};
  int x;
  cin >> x;

  int left = 0, right = 10;
  while (left < right) {
    int mid = left + (right - left) /2 ;
    if (arr[mid] >= x) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  cout << left << ' ';

  left = 0, right = 10;
  while (left < right) {
    int mid = left + (right - left + 1) / 2;
    if (arr[mid] <= x) {
      left = mid;
    } else {
      right = mid - 1;
    }
  }
  cout << left << endl;

  return 0;
}*/
/*#include <iostream>

using namespace std;

int main() {
  double x;
  cin >> x;

  double l = 0, r = x;

  while (r - l > 1e-8) {
    double mid = l + (r - l) / 2;

    if (mid * mid >= x) {
      r = mid;
    } else {
      l = mid;
    }
  }

  cout << l << endl;

  return 0;
}*/
/*#include <vector>

using namespace std;

vector<int> add(const vector<int> &v1, const vector<int> &v2) {
  vector<int> sum;

  int carry = 0;

  int max_size = max(v1.size(), v2.size());

  for (int i = 0; i < max_size || carry; ++i) {
    if (i < v1.size()) {
      carry += v1[i];
    }

    if (i < v2.size()) {
      carry += v2[i];
    }

    sum.push_back(carry % 10);
    carry /= 10;
  }

  return sum;
}*/
/*#include <vector>

using namespace std;

vector<int> add(const vector<int> &v1, const vector<int> &v2) {
  vector<int> sum;

  int carry = 0;
  int max_size = max(v1.size(), v2.size());

  for (int i = 0; i < max_size || carry; ++i) {
    if (i < v1.size()) {
      carry += v1[i];
    }

    if (i < v2.size()) {
      carry += v2[i];
    }

    sum.push_back(carry % 10);

    carry /= 10;
  }

  return sum;
}

bool cmp(const vector<int> &v1, const vector<int> &v2) {
  if (v1.size() != v2.size()) {
    return v1.size() > v2.size();
  }

  for (int i = v1.size() - 1; i >= 0; --i) {
    if (v1[i] != v2[i]) {
      return v1[i] > v2[i];
    }
  }

  return true;
}

vector<int> sub(const vector<int> &v1, const vector<int> &v2) {
  vector<int> res;

  int carry = 0;

  for (int i = 0; i < v1.size(); ++i) {
    int diff = v1[i] - carry;
    if (i < v2.size()) {
      diff -= v2[i];
    }
    res.push_back((diff + 10) % 10);
    carry = diff < 0 ? 1 : 0;
  }

  while (res.back() == 0 && res.size() > 1) {
    res.pop_back();
  }

  return res;
}*/
/*#include <vector>

using namespace std;

bool cmp(const vector<int> &v1, const vector<int> &v2) {
  if (v1.size() != v2.size()) {
    return v1.size() > v2.size();
  }

  for (int i = v1.size() - 1; i >= 0; --i) {
    if (v1[i] != v2[i]) {
      return v1[i] > v2[i];
    }
  }

  return true;
}

vector<int> sub(const vector<int> &v1, const vector<int> &v2) {
  vector<int> res;
  int carry = 0;

  for (int i = 0; i < v1.size(); ++i) {
    int diff = v1[i] - carry;
    if (i < v2.size()) {
      diff -= v2[i];
    }
    res.push_back((diff + 10) % 10);
    carry = diff < 0 ? 1 : 0;
  }

  while (res.size() > 1 && res.back() == 0) {
    res.pop_back();
  }

  return res;
}

vector<int> mul(const vector<int> &n, int m) {
  vector<int> prod;

  int carry = 0;

  for (int i = 0; i < n.size() || carry; ++i) {
    if (i < n.size()) {
      carry += n[i] * m;
    }

    prod.push_back(carry % 10);

    carry /= 10;
  }

  return prod;
}

vector<int> div(const vector<int> &num, int d, int &rem) {
  vector<int> quot;

  int carry = 0;
  for (int i = num.size() - 1; i >= 0; --i) {
    rem = rem * 10 + num[i];
    quot.push_back(rem / d);
    rem %= 10;
  }

  reverse(quot.begin(), quot.end());

  while (quot.size() > 1 && quot.back() == 0) {
    quot.pop_back();
  }

  return quot;
}*/
/*#include <vector>

using namespace std;

vector<int> div(const vector<int> &num, int d, int &rem) {
  vector<int> quot;

  int carry = 0;
  for (int i = num.size() - 1; i >= 0; ++i) {
    rem = rem * 10 + num[i];
    quot.push_back(rem / d);
  }

  reverse(quot.begin(), quot.end());

  while (quot.size() > 1 && quot.back() == 0) {
    quot.pop_back();
  }

  return quot;
}*/
/*#include <iostream>
#include <vector>

using namespace std;

const int LEN = 1010;

int main() {
  int n, m;
  cin >> n >> m;

  vector<int> arr(LEN), sum(LEN);

  for (int i = 1; i <= n; ++i) {
    cin >> arr[i];
    sum[i] = sum[i - 1] + arr[i];
  }

  while (m--) {
    int left, right;
    cin >> left >> right;
    cout << sum[right] - sum[left - 1] << endl;
  }

  return 0;
}*/
/*#include <iostream>

using namespace std;

const int LEN = 1000010;

int main() {
  int n, m;
  cin >> n >> m;

  int arr[LEN], sum[LEN];

  for (int i = 1; i <= n; ++i) {
    cin >> arr[i];
    sum[i] = sum[i - 1] + arr[i];
  }

  while (m--) {
    int left, right;
    cin >> left >> right;
    cout << sum[right] - sum[left - 1] << endl;
  }

  return 0;
}*/
/*
#include <iostream>

using  namespace std;

const int SIZE = 1010;

int main() {
  int n, m, q;

  int arr[SIZE][SIZE], sum[SIZE][SIZE];

  cin >> n >> m >> q;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> arr[i][j];
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
    }
  }


}*/
/*#include <iostream>

using namespace std;

const int SIZE = 1010;

int main() {
  int n, m;
  cin >> n >> m;

  int arr[SIZE] = {0}, sum[SIZE] = {0};

  for (int i = 1; i <= n; ++i) {
    cin >> arr[i];
    sum[i] = sum[i - 1] + arr[i];
  }

  while (m--) {
    int left, right;
    cin >> left >> right;
    cout << sum[right] - sum[left - 1] << endl;
  }

  return 0;
}*/
/*#include <iostream>

using namespace std;

const int SIZE = 1010;

int main() {
  int n, m, q;
  int arr[SIZE][SIZE], sum[SIZE][SIZE];

  cin >> n >> m >> q;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> arr[i][j];
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
    }
  }

  while (q--) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    cout << sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 -1][y2] + sum[x1 - 1][y1 - 1] << endl;
  }

  return 0;
}*/
/*#include <iostream>

using namespace std;

const int LEN = 100010;

int n, m;

int arr[LEN], diff[LEN];

void insert(int left, int right, int value) {
  diff[left] += value;
  diff[right] -= value;
}

int main() {
  cin >> n >> m;

  for (int i = 1; i <= n; ++i) {
    cin >> arr[i];
    insert(i, i, arr[i]);
  }

  while (m--) {
    int left, right, value;
    cin >> left >> right >> value;
    insert(left, right, value);
  }

  for (int i = 1; i <= n; ++i) {
    diff[i] += diff[i - 1];
    cout << diff[i] << ' ';
  }
  cout << endl;

  return 0;
}*/
/*#include <iostream>

using namespace std;

const int SIZE = 1010;

int n, m, q;
int arr[SIZE][SIZE], diff[SIZE][SIZE];

void insert(int x1, int y1, int x2, int y2, int value) {
  diff[x1][y1] += value;
  diff[x2 + 1][y1] -= value;
  diff[x1][y2 + 1] -= value;
  diff[x2 + 1][y2 + 1] += value;
}

int main() {
  cin >> n >> m >> q;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> arr[i][j];
      insert(i, j, i, j, arr[i][j]);
    }
  }

  while (q--) {
    int x1, y1, x2, y2, value;
    cin >> x1 >> y1 >> x2 >> y2 >> value;
    insert(x1, y1, x2, y2, value);
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
       diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
       cout << diff[i][j];
    }
  }

  return 0;
}*/
/*#include <iostream>

using namespace std;

int main() {
  char str[1000];
  gets(str);
  int n = strlen(str);

  int i = 0;

  while (str[i]) {
    if (str[i] != ' ') {
      cout << str[i];
    } else {
      cout << endl;
    }
    ++i;
  }
}*/
/*#include <iostream>

using namespace std;

const int N = 100010;  // 固定大小

// n 是整数，表示输入数组 a 的长度
// a[N] 是输入数组的整数数组
// s[N] 是辅助数组，记录 a 中每个元素在窗口中出现的次数
int n, a[N], s[N] = {0};

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  int res = 0;                  // 最长子数组的长度
  for (int i = 0, j = 0; i < n; ++i) {
    ++s[a[i]];                  // 增加 a[i] 在辅助数组 s 中的出现次数
    while (s[a[i]] > 1) {       // 如果重复
      --s[a[j]];                // 减少窗口左侧的元素的计数
      ++j;                      // 移动左边界
    }
    res = max(res, i - j + 1);  // 比较这个大小
  }

  cout << res << endl;          // 输出答案

  return 0;
}*/
/*#include <iostream>

using namespace std;

const int N = 100010;

int n, a[N], s[N];

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  int res = 0;
  for (int i = 0, j = 0; i < n; ++i) {
    ++s[a[i]];
    while (s[a[i]] > 1) {
      --s[a[j]];
      ++j;
    }
    res = max(res, i - j + 1);
  }
  cout << res << endl;

  return 0;
}*/
/*#include <iostream>

using namespace std;

const int N = 100010;

int n, a[N], s[N] = {0};

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  int res = 0;
  for (int i = 0, j = 0; i < n; ++i) {
    ++s[a[i]];
    while (s[a[i]] > 1) {
      --s[a[j]];
      ++j;
    }
    res = max(res, i - j + 1);
  }
  cout << res << endl;

  return 0;
}*/
/*#include <iostream>

using namespace std;

const int N = 100010;

int n, a[N], s[N];

int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  int res = 0;
  for (int i = 0, j = 0; i < n; ++i) {
    ++s[a[i]];
    while (s[a[i]] > 1) {
      --s[a[j]];
      ++j;
    }
    res = max(res, i - j + 1);
  }
  cout << res << endl;
  return 0;
}*/
/*#include <iostream>

using namespace std;

int main() {
  int x = 15;

  for (int i = 3; i >= 0; --i) {
    cout << (x >> i & 1);
  }

  return 0;
}*/
/*#include <iostream>

using namespace std;

int lowbit(int x) {
  return x & -x;  // 保留最低位的 1
}

int main() {
  int n;  // 次数
  cin >> n;

  while (n--) {
    int x;  // 对应的数字
    cin >> x;

    int res = 0;  // 答案
    while (x) {   // 非 0 则循环继续
      // 减去一个 lowbit()
      // 就会更新一个新的 lowbit()
      x -= lowbit(x);
      // 数量增加
      res++;
    }

    cout << res << ' ';
  }

  return 0;
}*/
/*#include <iostream>

using namespace std;

int lowbit(int x) {
  return x & -x;
}

int main() {
  int n;
  cin >> n;

  while (n--) {
    int x;
    cin >> x;

    int res = 0;
    while (x) {
      x -= lowbit(x);
      ++res;
    }

    cout << res << ' ';
  }

  return 0;
}*/
/*#include <iostream>

using namespace std;

int lowbit(int x) {
  return x & -x;
}

int main() {
  int n;
  cin >> n;

  while (n--) {
    int x;
    cin >> x;

    int res = 0;
    while (x) {
      x -= lowbit(x);
      ++res;
    }
    cout << res << ' ';
  }

  return 0;
}*/
/*#include <iostream>

using namespace std;

int lowbit(int x) {
  return x & -x;
}

int main() {
  int n;
  cin >> n;

  while (n--) {
    int x;
    cin >> x;

    int res = 0;
    while (x) {
      x -= lowbit(x);
      ++res;
    }

    cout << res << ' ';
  }

  return 0;
}*/
#include <iostream>

using namespace std;

template <class T>
void quickSort(T *arr, int left, int right) {
  
}

int main() {

  return 0;
}
