/* class Box {
 public:
  int length;
  int width;
  int height;
  Box(void) { std::cout << "Box()" << std::endl; }
  Box(int x, int y, int z) : length(x), width(y), height(z) {
    std::cout << "Box(int x, int y, int z) : length(x), width(y), height(z)"
              << std::endl;
  }
};
int main(int argc, char** argv) {
  // 在堆上申请以一个 int 类型大小的空间（4 bytes）；
  // 并且将申请的堆空间的内容初始化为 10
  int* p1 = new int(10);
  delete p1;

  // 在堆上申请 4 个类型 int 类型大小的空间；
  // int[4] 也为一种类型
  int* p2 = new int[4];

  for (int i = 0; i < 4; ++i) {
    std::cout << *(p2 + i) << " " << std::endl;
  }
  delete[] p2;

  // 在堆上申请一个 Box 类型大小的空间；
  // 在堆上也会有 Box 对象的实例化
  Box* p3 = new Box;
  delete p3;

  // 在堆上申请四个 Box 类型大小的空间；
  // 调用无参数的构造函数
  Box* p4 = new Box[4];
  delete[] p4;

  // 调用带参数的构造函数
  Box* p5 = new Box(10, 10, 10);
  delete p5;

  return 0;
} */
/* class Box {
 public:
  int length;
  int width;
  int height;
  Box(void) { std::cout << "Box()" << std::endl; }
  Box(int x, int y, int z) : length(x), width(y), height(z) {
    std::cout << "Box(int x, int y, int z) : length(x), width(y), height(z)"
              << std::endl;
  }
  ~Box() { cout << "~Box()" << endl; }
};

int main(void) {
  // 使用 malloc 不会调用构造函数
  Box *p1 = (Box *)malloc(sizeof(Box));

  // 使用 free 不会调用析构函数
  free(p1);

  Box *p2 = new Box;
  delete p2;

  return 0;
} */
/* class ABC {
 public:
  ABC(int a, int b, int c) { cout << "ABC(int a, int b, int c);" << endl; }
  ~ABC() { cout << "~ABC();" << endl; }

 private:
  int a;
  int b;
  int c;
};

class MyD {
 public:
  MyD(void) : abc1(1, 2, 3), abc2(4, 5, 6) { cout << "MyD(void);" << endl; }
  ~MyD() { cout << "~MyD();" << endl; }

 private:
  ABC abc1;
  ABC abc2;
};

int main(void) {
  MyD myD;
  return 0;
} */
/* int main(void) {
  // 调用构造函数：Test(int a, int b);
  Test t1(10, 20);
  t1.sum[0] = 100;
  t1.sum[1] = 101;
  t1.sum[2] = 102;
  t1.sum[3] = 103;

  // 使用已经构造好的对象 t1 来初始化一个新的对象
  Test t2 = t1;
  cout << "t2.x: " << t2.x << endl;
  cout << "t2.y: " << t2.y << endl;

  cout << "t1.sum: " << t1.sum << endl;
  cout << "t2.sum: " << t2.sum << endl;



  return 0;
} */
/* void func(void) {
  Test *t1 = new Test(10, 20);
  t1->sum[0] = 100;
  t1->sum[1] = 101;
  t1->sum[2] = 102;
  t1->sum[3] = 103;

  Test t2 = *t1;

  // 手动释放 t1 所申请的堆空间；
  // 意味着销毁掉 *t1 这个对象，会自动调用析构函数
  // 顺带手动释放成员变量 sum 所申请的堆空间
  delete t1;

  cout << t2.sum[0] << endl;
  cout << t2.sum[1] << endl;
  cout << t2.sum[2] << endl;
  cout << t2.sum[3] << endl;
}

int main(void) {
  func();
  cout << "Hello World!" << endl;
  return 0;
} */
/* class Test {
 public:
  int* sum;
  int x;
  int y;

  Test(void) {
    cout << "Test(void);" << endl;
    x = 0;
    y = 0;
    sum = new int[4];
  }

  Test(int a, int b) : x(a), y(b) {
    cout << "Test(int a, int b);" << endl;
    sum = new int[4];
  }

  Test(const Test& t) {
    cout << "Test(const Test& t);" << endl;
    x = t.x;
    y = t.y;
    // 分配一块新的空间
    sum = new int[4];
    // 把 t.sum 空间中的内容拷贝到新的空间
    for (int i = 0; i < 4; ++i) {
      sum[i] = t.sum[i];
    }
  }

  // t 引用的是右值

  ~Test() {
    cout << "~Test();" << endl;
    delete[] sum;
  }
}; */
/* void func(const Test& t) {} */
/* int main(void) {
  // 调用构造函数：Test(int a, int b) : x(a), y(b);
  Test t1(10, 20);
  t1.sum[0] = 100;
  t1.sum[1] = 101;
  t1.sum[2] = 102;
  t1.sum[3] = 103;

  // 等价于 t2.Test(t1);
  Test t2 = t1;
  cout << t1.sum << endl;
  cout << t2.sum << endl;

  for (int i = 0; i < 4; ++i) {
    cout << t2.sum[i] << endl;
  }

  return 0;
} */
/* int main(void) {
  Test t1(10, 20);
  func(t1);
  return 0;
} */
/* #include <iostream>

using namespace std;

void swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

void bubbleSort(int* arr, int size) {
  for (int i = 0; i < size - 1; ++i) {
    for (int j = 0; j < size - 1 - i; ++j) {
      if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
    }
  }
}

void insertionSort(int* arr, int size) {
  int i, j;
  for (i = 1; i < size; ++i) {
    int key = arr[i];
    for (j = i - 1; j >= 0 && arr[j] > arr[j + 1]; --j) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = key;
  }
}

void selectionSort(int* arr, int size) {
  for (int i = 0; i < size - 1; ++i) {
    int min_index = i;
    for (int j = i + 1; j < size; ++j) {
      if (arr[j] < arr[min_index]) min_index = j;
    }
    swap(arr[min_index], arr[i]);
  }
}

int main(void) {
  int arr[10] = {
      32, 45, 55, 65, 34, 23, 1, 57, 90, 87,
  };

  for (int i = 0; i < 10; ++i) cout << arr[i] << " ";
  cout << endl;

  selectionSort(arr, 10);

  for (int i = 0; i < 10; ++i) cout << arr[i] << " ";
  cout << endl;

  return 0;
}  */
/* int main(void) {
  string s;
  s = "Hello World!";  // char *
  cout << s << endl;
  s = 'A';  // char s = "A";
  // 虽然赋值的是字符，根本上还是字符串
  cout << s << endl;
  return 0;
} */
/* #include <iostream>
#include <string>

using namespace std; */
/*
int main(void) {
  string s1("123"), s2("abc");
  s1.append(s2);             // s1 = "123abc"
  s1.append(s2, 1, 2);       // s1 = "123abcbc"
  s1.append(3, 'K');         // s1 = "123abcbcKKK"
  s1.append("ABCDE", 2, 3);  // s1 = "123abcbcKKKCDE"
  cout << s1 << endl;
  return 0;
} */
/* int main(void) {
  string s = "123abc";

  s.append("Aafaf", 2, 3);
  cout << s << endl;

  return 0;
} */
/* #include <iostream>
#include <string>

using namespace std; */
/* int main(void) {
  string s1 = "hello";
  string s2 = "Hello";
  cout << s1.compare(1, 2, s2, 1, 2) << endl;
  return 0;
} */
/* int main(void) {
  string s1("faf43fdad");
  string s2 = s1.substr(1, 2);
  s2.swap(s1);
  cout << s2 << endl;
  return 0;
} */
/* #include <iostream>
#include <string>

using namespace std;

int main(void) {
  string s1("##temp=32.5;hum=67.6##");
  int pos;

  // 从前往后找下标
  if ((pos = s1.find('x')) != string::npos) {
    cout << pos << endl;
  } else {
    cout << "no x" << endl;
  }

  // 从后往前找下标
  if ((pos = s1.rfind('=') != string::npos)) {
    cout << pos << endl;
  } else {
    cout << "no =" << endl;
  }
  cout << endl;

  string names[4];
  names[0] = "zhanghua";
  names[1] = "lisi";
  names[2] = "lihua";
  names[3] = "zhangsan";

  // 查找出名字中带 hua 的同学（实际举例）
  for (int i = 0; i < 4; ++i) {
    if (names[i].find("hua") != string::npos) {
      cout << names[i] << endl;
    }
  }
  cout << endl;

  // 查找出姓 zhang 的同学（下标为零就是首地址，代表为姓）
  for (int i = 0; i < 4; ++i) {
    if (names[i].find("zhang") == 0) {
      cout << names[i] << endl;
    }
  }

  return 0;
} */
/* #include <iostream>
#include <string>

using namespace std;

int main(void) {
  string s1("Real Steel");
  s1.replace(1, 2, 5, '0');
  cout << s1 << endl;
  return 0;
} */
/* int main(void) {
  string s1("Real Steel");
  int pos = s1.find_first_not_of("aRel");
  cout << pos << endl;
  return 0;
} */
/* int main(void) {
  string s1("Real Steel");
  s1.replace(1, 3, 4, '0');
  int n = s1.find("0000");
  if (n != string::npos) {
    s1.replace(n, 4, "kkk");
  }
  cout << s1 << endl;
  return 0;
} */
/* int main(void) {
  string s1("Real Steel");

  // 删除子串 (1, 3)，此后 s1 = "R Steel"
  s1.erase(1, 3);

  // 删除下标 5 及其后面的所以字符，此后 s1 = "R Ste"
  s1.erase(5);
  cout << s1 << endl;

  return 0;
}
 */
/* class Test {
 public:
  Test(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  int x;
  int y;
  int z;
};

int main(void) {
  string s1("Code Force");
  s1.erase(5);
  cout << s1 << endl;
  return 0;
} */
/* int main(void) {
  string s("Real Steel Code");
  int pos = s.find("Steel");
  if (pos != string::npos) {
    s.erase(pos, sizeof("Steel"));
  }
  cout << s << endl;
  return 0;
} */
/* #include <iostream>
#include <string>

using namespace std;

int main(void) {
  string s("Fira Code");
  s.assign(4, 'K');
  cout << s << endl;
  return 0;
} */
/* #include <iostream>
#include <string>

class Person {
 public:
  void print() {
    std::cout << "name: " << _name << std::endl;
    std::cout << "age: " << _age << std::endl;
  }
  void set_age(int age) { _age = age; }
  int get_age() { return _age; }
  void set_name(std::string name) { _name = name; }
  std::string get_name() { return _name; }

 protected:
  std::string _name;
  int _age;
};

// 继承后父类的 Person 的成员（成员函数 + 变量）都会变成子类的一部分，
// 这里体现出了 Student 和 Teacher 复用了 Person 的成员

// Student 派生类
class Student : public Person {
 protected:
  // std::string _stuid;  // 学号
};

// Teacher 派生类
class Teacher : public Person {
 protected:
  // std::string _jobid;  // 工号
};

int main() {
  Student s;
  Teacher t;
  s.set_age(10);
  std::cout << s.get_age() << std::endl;
  s.set_name("lisi");
  std::cout << s.get_name() << std::endl;
  s.print();
  std::cout << sizeof(Person) << std::endl;
  std::cout << sizeof(Student) << std::endl;
  std::cout << sizeof(Teacher) << std::endl;

  return 0;
} */
/* #include <iostream>

using namespace std;

class Test {
 public:
  int b;
  static int a;
};

int Test::a = 18;

// 基类
class A {
 public:
  int x;

 protected:
  int y;

 private:
  int z;
};

// 派生类
class B : private A {
  void func() {
    x = 100;
    // 基类中的 protected 成员在派生类中能被访问到
    y = 100;
    // 基类中的 private 成员在派生类内、外均不能访问到
  }
};

class C : private A {};

class D : protected A {};

int main() {
  cout << "Hello World!" << endl;
  return 0;
} */
/* #include <iostream>

using namespace std;

class A {
 public:
  A() { cout << "A()" << endl; }
  ~A() { cout << "~A()" << endl; }

  A(int a, int b) : y(a), x(b) {
    cout << "A(int a, int b) : y(a), x(b)" << endl;
  }

  int get_x() { return x; }
  int get_y() { return y; }

 private:
  int x;

 protected:
  int y;
};

class B : public A {
 public:
  B() { cout << "B()" << endl; }

  // 在派生类中指定调用基类中某个构造函数
  B(int a, int b, int c) : A(a, b), p(c) {
    cout << "B(int a, int b) : A(a, b)" << endl;
  }
  ~B() { cout << "~B()" << endl; }

  int p;
};

int main() {
  B b(10, 20, 012);

  cout << b.get_x() << endl;
  cout << b.get_y() << endl;

  return 0;
} */
/* #include <iostream>

using namespace std;

// 父类
class A {
 public:
  A() : a_x(10), a_y(10) {}
  int a_x;
  int a_y;
};

// 子类
class B : public A {
 public:
  // 此处的 a_x 是子类中的
  B() : b_x(20), a_x(20) {
    // 在子类内部访问父类中同名的成员变量
    A::a_x = 30;
  }
  int b_x;
  // 和父类中的成员变量名字冲突了
  int a_x;
};

int main() {
  cout << sizeof(A) << endl;  // 8 个字节
  cout << sizeof(B) << endl;  // 16 个字节
  // 子类继承了父类中同名的属性

  B b;
  // b.a_x: 子类中的成员变量
  // cout << b.B::a_x << endl;
  cout << b.a_x << endl;

  // 通过子类对象访问基类中的同名成员变量
  // 应输出 30
  cout << b.A::a_x << endl;

  return 0;
} */
/* #include <iostream>

using namespace std;

class A {
 public:
  void func() { cout << "A::func()" << endl; }
};

class B : public A {
 public:
  void func() { cout << "B::func()" << endl; }
};

int main() {
  B b;
  b.func();
  return 0;
} */
/* #include <iostream>

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
} */
/* #include <iostream>
using namespace std;
// 间接基类
class A {
 public:
  int a_x;
};
// 直接基类
class B : public A {
 public:
  int b_x;
};
// 直接基类
class C : public A {
 public:
  int c_x;
};
class D : public B, public C {
 public:
  // 继承自 B 类
  // int a_x;
  // int b_x;

  // 继承自 C 类
  // int a_x;
  // int c_x;
  int d_x;
};
int main() {
  cout << sizeof(D) << endl;  // 输出 20 个字节代表两份的继承了
  D d;
  // 这是一种访问方式，
  d.B::a_x = 100;
  d.C::a_x = 200;
  cout << d.B::a_x << endl;
  cout << d.C::a_x << endl;
  return 0;
} */
/* #include <iostream>
#include <string>

using namespace std;
class Animal {
 public:
  string name;
  int age;
};
class Chordata : virtual public Animal {};
class Bird : virtual public Animal {};
class Bat : public Chordata, public Bird {};
int main() {
  cout << sizeof(Bat) << endl;
  cout << sizeof(Animal) << endl;
  Bat bat;
  bat.name = "Jacy";
  cout << bat.name << endl;
  return 0;
} */
/* #include <iostream>
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
} */
/* #include <iostream>
#include <string>

using namespace std;

void func() {}

void func(int x) {}

void func(char x) {}

class A {
 public:
  void func() {}
};

class B : public A {
 public:
  void func() {}
  void func(int x) {}
};

int main() {
  B b;
  b.func();
  b.A::func();
  func(100);
  string s1("Hello "), s2("World!");
  string s3;
  s3 = s1 + s2;
  cout << s3 << endl;
  cout << s1[2] << endl;
  return 0;
} */
/* int func() {
  int x = 10;
  return x;
} */
/* #include <cstring>
#include <iostream>
#include <ostream>

using namespace std;

class Test {
 public:
  int data;
  char *ptr;

  Test() : data(0), ptr(new char[10]) { cout << "Test()" << endl; }
  Test(const Test &t) {
    cout << "Test(const Test &t)" << endl;
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
    if (ptr) delete[] ptr;
  }

  // 运算符重载，实现字符串拼接
  // 该运算符重载运算符由左操作数调用，右操作数当做实参
  // 触发：t1.operator+()
  Test operator+(const Test &t) {
    cout << "Test operator+(Test &t)" << endl;
    // 保存最后执行的结果
    Test val;
    val.data = this->data + t.data;
    val.ptr = new char[strlen(this->ptr) + strlen(t.ptr) + 1];
    memset(val.ptr, 0, strlen(this->ptr) + strlen(t.ptr) + 1);
    strcpy(val.ptr, this->ptr);
    strcat(val.ptr, t.ptr);
    return val;
  }

  // > 号运算符的重载
  // 比较字符串版本
  bool operator>(const Test &t) {
    cout << "bool operator>(const Test &t)" << endl;
    if (strcmp(this->ptr, t.ptr) > 0) {
      return true;
    } else {
      return false;
    }
  }

  bool operator>=(const Test &t) {
    cout << "bool operator>=(const Test &t)" << endl;
    if (strcmp(this->ptr, t.ptr) >= 0) {
      return true;
    } else {
      return false;
    }
  }

  bool operator<(const Test &t) {
    cout << "bool operator<(const Test &t)" << endl;
    if (strcmp(this->ptr, t.ptr) < 0) {
      return true;
    } else {
      return false;
    }
  }

  bool operator<=(const Test &t) {
    cout << "bool operator<=(const Test &t)" << endl;
    if (strcmp(this->ptr, t.ptr) <= 0) {
      return true;
    } else {
      return false;
    }
  }

  bool operator==(const Test &t) {
    cout << "bool operator==(const Test &t)" << endl;
    if (strcmp(this->ptr, t.ptr) == 0) {
      return true;
    } else {
      return false;
    }
  }

  char operator[](const int index) {
    cout << "char operator[](const Test &t)" << endl;
    if (index < 0 || index >= strlen(ptr)) return '\0';
    return this->ptr[index];
  }

  Test &operator=(const Test &t) {
    // t1 = t2
    // t3 = t1 = t2
    // 所以返回 *this，使用 Test &返回减少临时对象的产生
    delete[] this->ptr;
    this->ptr = new char[strlen(t.ptr) + 1];
    this->data = t.data;
    strcpy(this->ptr, t.ptr);
    return *this;
  }

  // 前置 ++
  // ++t1
  Test &operator++() {
    cout << "Test &operator++()" << endl;
    ++this->data;
    return *this;
  }

  // 后置++
  // t1++
  // 通过传 int 来区分前置++和后置++
  Test operator++(int) {
    cout << "Test operator++(int)" << endl;
    // 临时变量保存++之前的状态
    Test temp = *this;
    ++data;
    return temp;
  }

  // <<
  // cout << t1
  // 左操作数 cout 不是 Test 对象，无法直接通过它调用
  // 将左操作数和右操作数当作实参来传递
  // cout : ostream
  friend ostream &operator<<(ostream &os, const Test &t) {
    os << t.data << endl;
    os << t.ptr << endl;
    // 返回os以便于链式
    return os;
  }
};

Test func() {
  Test t;
  return t;
}

Test &func(Test &t) {
  // 传入的参数还在
  // 因此引用有效
  return t;
}

int main() {
#if 0
// + 号运算符的重载
  Test t1(10, "Hello ");
  Test t2 = t1;
  cout << t2.data << endl;
  cout << t2.ptr << endl;

  Test t3(10, "World!");

  cout << "****************" << endl;

  Test t4 = t1 + t3;
  // 执行 Test t4 = t1 + t3
  // 会触发 Test operator+(Test &t)
  // 返回一个构造好的对象
  // 调用拷贝构造函数 Test t4 = val 触发拷贝构造函数的调用
  cout << t4.data << endl;
  cout << t4.ptr << endl;

  Test t1(10, "Hello");
  Test t2(20, "heLlo");
  if (t1 > t2) {
    cout << "t1 > t2" << endl;
  } else {
    cout << "t1 <= t2" << endl;
  }

  Test t1(10, "heLlo");
  Test t2(20, "hello");
  cout << t1[4] << endl;

  t1 = t2;
  cout << t1.ptr << endl;
  printf("%p %p\n", t1.ptr, t2.ptr);



  Test t1(10, "hello");
  Test t2;

  t2 = ++t1;
  cout << t2.data << endl;

  Test t3;

  t3 = t1++;
  cout << t3.data << endl;  // 11
  cout << t1.data << endl;  // 12
#endif

  Test t1(10, "Hello World!");
  cout << t1;

  Test t2 = func();

  return 0;
}
 */
/* #include <iostream>

using namespace std;

// 先声明 class B
// 才可以在 class A 中使用
class B;

class A {
 public:
  int y;

 private:
  int x;

  // 将普通函数 func 声明为该类的友元函数
  // 此时便可以访问该类中的私有成员变量
  friend void func(A &, B &);
};

class B {
 public:
  int y;

 private:
  int x;

  friend void func(A &, B &);
};

// 可以同时访问两个类
void func(A &t1, B &t2) {
  t1.y = 100;
  t2.x = 100;
}

int main() {
  A a;
  B b;
  func(a, b);
  return 0;
} */
/* class CCar;  // 提前声明 CCar 类，以便后面的 CDriver 类使用
class CDriver {
 public:
  void ModifyCar(CCar* pCar);  // 改装汽车
};
class CCar {
 private:
  int price;
  friend int MostExpensiveCar(CCar cars[], int total);  // 声明友元
  friend void CDriver::ModifyCar(CCar* pCar);           // 声明友元
};
void CDriver::ModifyCar(CCar* pCar) {
  pCar->price += 1000;  // 汽车改装后价值增加
}

int MostExpensiveCar(CCar cars[], int total) {
  // 求最贵汽车的价格
  int tmpMax = -1;
  for (int i = 0; i < total; ++i) {
    if (cars[i].price > tmpMax) {
      tmpMax = cars[i].price;
    }
  }
  return tmpMax;
}

int main() { return 0; }
 */
/* #include <iostream>
using namespace std;
class Test {
 public:
  int x;
  friend bool operator>(const Test &, const Test &);
};

bool operator>(const Test &t1, const Test &t2) { return t1.x > t2.x; }


ostream &operator<<(ostream &os, const Test &t) {
  os << t.x;
  return os;
}

int main() {
  Test t;
  // 因为 << 是 Test 的成员函数
  // 所以如果不声明友元
  // 只能由 Test 来调用
  cout << t << endl;
  Test t2;
  t2.x = 1000;
  if (t2 > t) {
  }
  return 0;
} */
/* #include <iostream>

using namespace std;

class B;
class A {
 public:
  void func1(B &t);
  void func2(B &t);
};

class B {
 private:
  int x;
  // friend void A::func1(B &t);
  // friend void A::func2(B &t);
  // 将类 A 声明为友元类
  friend class A;
  friend void func(B &t);
};

class C : public B {
  // class A 不是 class C 的友元类
  // void func() 也不是 class C 的友元函数
};

void func() {}

void A::func1(B &t) { cout << t.x << endl; }
void A::func2(B &t) { cout << t.x << endl; }

int main() {
  B b;
  A a;
  a.func1(b);
  a.func2(b);
  return 0;
} */
/* #include <cstring>
#include <iostream>

using namespace std;

#define DEFAULT_LENGTH 10

class MyString {
 public:
  MyString() : _len(DEFAULT_LENGTH), _str(new char[DEFAULT_LENGTH + 1]) {}

  MyString(int len) : _len(len), _str(new char[len + 1]) {}

  MyString(const MyString& other) {
    this->_len = other._len;
    if (other._len == 0) {
      delete[] this->_str;
      _len = 0;
    } else {
      this->_str = new char[other._len];
      strcpy(this->_str, other._str);
      this->_len = other._len;
    }
  }

  ~MyString() {
    if (_str) delete[] _str;
  }

  size_t length() { return _len; }

  size_t size() { return _len; }

  MyString operator+(const MyString& other) {
    MyString temp(this->_len + other._len);
    strcpy(temp._str, this->_str);
    strcat(temp._str, other._str);
    return temp;
  }

  MyString& operator=(const MyString& other) {
    delete[] _str;
    this->_str = new char[this->_len + other._len + 1];
    strcpy(this->_str, other._str);
    return *this;
  }

  bool operator>(const MyString& other) {
    if (strcmp(this->_str, other._str) > 0) {
      return true;
    } else {
      return false;
    }
  }

  bool operator==(const MyString& other) {
    if (strcmp(this->_str, other._str) == 0) {
      return true;
    } else {
      return false;
    }
  }

  bool operator>=(const MyString& other) {
    if (strcmp(this->_str, other._str) >= 0) {
      return true;
    } else {
      return false;
    }
  }

  bool operator<(const MyString& other) {
    if (strcmp(this->_str, other._str) < 0) {
      return true;
    } else {
      return false;
    }
  }

  bool operator<=(const MyString& other) {
    if (strcmp(this->_str, other._str) <= 0) {
      return true;
    } else {
      return false;
    }
  }

  friend ostream& operator<<(ostream& os, const MyString& str) {
    os << str._str;
    return os;
  }

  friend istream& operator>>(istream& is, MyString& str) {
    char buffer[1000];
    is >> buffer;
    str = MyString(strlen(buffer));
    strcpy(str._str, buffer);
    return is;
  }

 private:
  size_t _len;
  char* _str;
};

int main() { return 0; } */
/* #include <iostream>
#include <string>

using namespace std;

class A {
 public:
  int a;

 private:
  int _a;
};

class B : virtual public A {

};

class C : virtual public A {};

class D : public B, public C {};

int main() {
  D d;
  d.a = 100;
  cout << d.a << endl;
  cout << d.B::a << endl;
  cout << d.C::a << endl;
  cout << d.A::a << endl;
  return 0;
} */
/* #include <cstring>
#include <iostream>

using namespace std;

const unsigned int DEFAULT_LENGTH = 4;

class MyString {
 public:
  MyString() : _length(DEFAULT_LENGTH) { _ptr = new char[DEFAULT_LENGTH + 1]; }
  MyString(const char* str) : _length(strlen(str)) {
    _ptr = new char[_length + 1];
    strcpy(_ptr, str);
  }
  MyString(const unsigned int length) : _length(length) {
    _ptr = new char[length + 1];
  }
  ~MyString() {
    if (_ptr) delete[] _ptr;
  }

  unsigned int length() { return _length; }

  unsigned int size() { return _length; }

  MyString operator+(const MyString& other) {
    MyString temp;
    temp._length = _length + other._length + 1;
    temp._ptr = new char[temp._length + 1];
    strcpy(temp._ptr, _ptr);
    strcat(temp._ptr, other._ptr);
    return temp;
  }

  MyString& operator=(const MyString& other) {
    delete[] _ptr;
    _length = other._length;
    _ptr = new char[_length + 1];
    return *this;
  }

  bool operator>(const MyString& other) {
    if (strcmp(_ptr, other._ptr) > 0) {
      return true;
    } else {
      return false;
    }
  }

  bool operator>=(const MyString& other) {
    if (strcmp(_ptr, other._ptr) >= 0) {
      return true;
    } else {
      return false;
    }
  }

  bool operator==(const MyString& other) {
    if (strcmp(_ptr, other._ptr) == 0) {
      return true;
    } else {
      return false;
    }
  }

  bool operator<(const MyString& other) {
    if (strcmp(_ptr, other._ptr) < 0) {
      return true;
    } else {
      return false;
    }
  }

  bool operator<=(const MyString& other) {
    if (strcmp(_ptr, other._ptr) <= 0) {
      return true;
    } else {
      return false;
    }
  }

  friend ostream& operator<<(ostream& os, const MyString& self) {
    os << self._ptr;
    return os;
  }

  friend istream& operator>>(istream& is, MyString& self) {
    char buffer[1000];
    is >> buffer;
    strcpy(self._ptr, buffer);
    self._length = strlen(buffer);
    return is;
  }

 private:
  unsigned int _length;
  char* _ptr;
};

int main() { return 0; } */
/* #include <iostream>

using namespace std;
#define DEFAULT_X 1
#define DEFAULT_Y 1
class Point {
 private:
  int _x, _y;

 public:
  Point() : _x(DEFAULT_X), _y(DEFAULT_Y) {}
  Point(int x, int y) : _x(x), _y(y) {}
  void printPoint() {
    cout << _x << endl;
    cout << _y << endl;
  }
  void setX(int x) { _x = x; }
  void setY(int y) { _y = y; }
  void move(int x, int y) { _x = x, _y = y; }
};

int main() {
  Point s1(10, 20);
  Point s2;
  s1.printPoint();
  s2.printPoint();
  return 0;
} */
/* #include <iostream>

using namespace std;

class Animal {
 public:
  virtual void eat() { cout << "Animal is eating." << endl; }
};

class Cat : public Animal {
 public:
  void eat() { cout << "Cat is eating." << endl; }
};

class Dog : public Animal {
 public:
  void eat() { cout << "Dog is eating." << endl; }
};

int main() {
  Animal *ptr1 = new Cat();
  Animal *ptr2 = new Dog();

  ptr1->eat();
  ptr2->eat();

  delete ptr1;
  delete ptr2;
  return 0;
} */
/* #include <iostream>

using namespace std;

class Hero {
 public:
  void huicheng() { cout << "Hero::huicheng()" << endl; }

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
void goback(Hero &h) { h.huicheng(); }

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
} */
/* #include <iostream>

using namespace std;

class Animal {
 public:
  virtual void eat() { cout << "Animal is eating." << endl; }
};

class Dog : public Animal {
 public:
  void eat() { cout << "Dog is eating." << endl; }
};

class Cat : public Animal {
 public:
  void eat() { cout << "Cat is eating." << endl; }
};

void eat(Animal &animal) { animal.eat(); }
void eat(Animal *ptr) { ptr->eat(); }

int main() {
  Animal *cat = new Cat;
  Animal *dog = new Dog;

  cat->eat();
  dog->eat();

  return 0;
} */
/* #include <iostream>

using namespace std;

// 6.67e-11 为浮点数表示法之一
// 代表 6.67 * 10^(-11)
const double G = 6.67e-11;

int main() {
  double m1, m2, R, F;
  cout << "2023116204 陈靖盈" << endl;
  cout << "你好, C++" << endl;
  cout << "请输入地球的质量:>" << endl;
  cin >> m1;
  cout << "请输入月球的质量:>" << endl;
  cin >> m2;
  cout << "请输入地月距离:>" << endl;
  cin >> R;
  F = G * m1 * m2 / (R * R);
  cout << "地球与月球之间的万有引力为: " << F << "N" << endl;
  return 0;
}
 */
/* #include <iostream>

using namespace std;

class Animal {
 public:
  void voice() { cout << "Animal is voicing." << endl; }
  virtual void eat() { cout << "Animal is eating." << endl; }
};

class Dog : public Animal {
 public:
  void voice() { cout << "Dog is voicing." << endl; }
  void eat() { cout << "Dog is eating." << endl; }
  void eat(const char* food) {
    cout << "Dog is eating " << food << "." << endl;
  }
};

class Cat : public Animal {
 public:
  void voice() { cout << "Cat is voicing." << endl; }
  void eat() { cout << "Cat is eating." << endl; }
  void eat(const char* food) {
    cout << "Cat is eating " << food << "." << endl;
  }
};

void eat(Animal& animal) { animal.eat(); }

int main() {
  Dog dog;
  Cat cat;
  dog.voice();
  dog.Animal::voice();
  eat(dog);
  eat(cat);
  return 0;
} */
/* #include <iostream>

using namespace std;

class Pupil {
 public:
  // 必须使用参数
  Pupil(const char name[], unsigned int math_score, unsigned int c_score)
      : _math_score(math_score), _c_score(c_score) {
    ++_num;
    _math_total_score += math_score;
    _c_total_score += c_score;
  }

  void showBase() {
    cout << "名字为：" << _name << endl;
    cout << "数学成绩为：" << _math_score << endl;
    cout << "语文成绩为：" << _c_score << endl;
  }

  static void showStatic() {
    cout << "数学总成绩为：" << _math_total_score << endl;
    cout << "语文总成绩为：" << _c_total_score << endl;
    cout << "学生人数为：" << _num << endl;
  }

 private:
  char _name[19];
  unsigned int _math_score;
  unsigned int _c_score;
  static unsigned int _num;
  static unsigned int _math_total_score;
  static unsigned int _c_total_score;
};

unsigned int Pupil::_num = 0;
unsigned int Pupil::_math_total_score = 0;
unsigned int Pupil::_c_total_score = 0;

int main() {
  Pupil Jacy("Jacy", 60, 80);
  Pupil Judy("Judy", 100, 100);
  Pupil Alice("Alice", 50, 60);
  Alice.showBase();
  Pupil Jack("Jack", 75, 90);
  Pupil Cathy("Cathy", 30, 20);
  Pupil::showStatic();
  return 0;
} */
/* int main() {
  int x;
  if (x >= 0 && x < 360) {
    // 具体实现
  } else if (x >= 360 && x < 600) {
    // 具体实现
  } else if (x >= 600) {
    // 具体实现
  }
}
 */
/* #include <iostream>

using namespace std;

// 抽象类
class Hero {
 public:
  virtual void back() = 0;    // 纯虚函数
  virtual void attack() = 0;  // 纯虚函数
};

class LiBai : public Hero {
 public:
  void back() { cout << "LiBai::back()" << endl; }  // 重写
  void attack() { cout << "LiBai::attack()" << endl; }
};

class CaoCao : public Hero {
 public:
  void back() { cout << "CaoCao::back()" << endl; }  // 重写
  void attack() { cout << "CaoCao::attack()" << endl; }
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
} */
/* #include <iostream>

using namespace std;

int main() {
  int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  for (int i = 0; i < 10; ++i) {
    cout << arr[i] << " ";
  }
  cout << endl;
  return 0;
} */
/* #include <iostream>

using namespace std;

int main() {
  int num = 0;     // 要输入的数字
  int count1 = 0;  // 偶数个数
  int count2 = 0;  // 奇数个数

  cout << "请输入一系列整数(输入0或负数表示结束):" << endl;
  do {
    cin >> num;
    // 如果整除2（即为偶数），则偶数数量++
    // 否则反之
    if (num % 2 == 0) {
      ++count1;
    } else {
      ++count2;
    }
  } while (num != 0);  // 不等于 0 时，循环继续
  cout << "奇数个数为：" << count1 << endl;
  cout << "偶数个数为：" << count2 << endl;

  return 0;
} */
/* #include <cmath>
#include <iostream>

using namespace std;

class Shape {
 public:
  virtual double getPermiter() const = 0;
  virtual double getArea() const = 0;
};

class Trangle : public Shape {
 public:
  Trangle(double a = 10, double b = 10, double c = 10) : _a(a), _b(b), _c(c) {}

  double getPermiter() const { return _a + _b + _c; }
  double getArea() const {
    double p = 0.5 * (_a + _b + _c);
    return sqrt(p * (p - _a) * (p - _b) * (p - _c));
  }

 private:
  double _a;
  double _b;
  double _c;

  double _permiter;
  double _area;
};

class Circle : public Shape {
 public:
  Circle() : _r(10) {}
  double getPermiter() const;
  double getArea() const;

 private:
  double _r;
  static double pi;
};

double Circle::pi = 3.1415926;
double Circle::getPermiter() const { return 2 * pi * _r; }
double Circle::getArea() const { return pi * _r * _r; }

int main() {
  Trangle trangle;
  cout << trangle.getPermiter() << endl;
  cout << trangle.getArea() << endl;

  Circle circle;
  cout << circle.getPermiter() << endl;
  cout << circle.getArea() << endl;

  // 用数组来保存一个三角形和一个圆
  Shape *shapes[2] = {&trangle, &circle};

  // 打印这两个的周长和面积
  for (int i = 0; i < 2; ++i) {
    cout << shapes[i]->getArea() << endl;
    cout << shapes[i]->getPermiter() << endl;
  }

  return 0;
} */
/* #include <iostream>

using namespace std;

class A {
 public:
  A() { cout << "A::A()" << endl; }
  virtual ~A() { cout << "A::~A()" << endl; }
};

class B : public A {
 public:
  int *p;
  B() {
    p = new int[4];
    cout << "B::B()" << endl;
  }
  ~B() {
    delete[] p;
    cout << "B::~B()" << endl;
  }
};

int main() {
  // 基类指针指向派生类对象
  // 构造一个派生类对象
  A *p = new B();
  // 通过基类指针，释放一个派生类对象
  delete p;
  return 0;
} */
/* #include <iostream>

using namespace std;

int main() {
  int x = 100;
  // *p 是只读的，不能通过指针 p 不能改变它指向的内存空间的内存
  const int *p1 = &x;
  int const *p2 = &x;  // 等效于 const int *p2 = &x;
  // p3 这个指针一旦初始化后就不能再指向别的内存空间了
  const int *const p3 = &x;  // p3 是只读的，*p3 也是只读的
  int const *const p4 = &x;
  cout << *p4 << endl;

  return 0;
} */
/* class A {
 public:
  const int x;
  A(int x) : x(x) {}
}; */
/* class B {
 public:
  int x;

 public:
  // error C3490: 由于正在通过常量对象访问“x”，因此无法对其进行修改
  void f() const { this->x++; }
}; */
/* class B {
 public:
  int x;
  B();

  int getX() const;
}; */
/* #include <iostream>

using namespace std;

class C {
 public:
  int y;
  int getX() const { return x; }
  C() : x(100), y(1000) {}

 private:
  int x;
};

int main() {
  const C c;
  cout << c.y << endl;
  cout << c.getX() << endl;
  return 0;
} */
/* #include <iostream>
using namespace std;
// error C3892: “t”: 不能给常量赋值
void func(const int& t) { ++t; }
int main() {
  int x = 0;
  func(x);
  cout << x << endl;
  return 0;
} */
/* #include <iostream>
using namespace std;
int main() {
  // 定义三个变量
  // num：西瓜数量
  // day：卖完的天数
  // bnum：在整数除法下的一半
  int num, day, bnum;
  cout << "请输入西瓜总数：";
  cin >> num;
  // 当西瓜总数大于 0 时，循环继续
  while (num > 0) {
    // 计算当前的一半
    bnum = num / 2;
    // 减去一半和多的两颗
    num -= bnum + 2;
    // 如果卖的小于 3 颗，便可能出现这种情况
    if (num < 0) {
      // 此时卖完剩下的
      // 因为不可能小于 0，因此设置为 0
      num = 0;
    }
    // 天数增加
    ++day;
    // 输出剩下的
    cout << "第" << day << "天剩下：" << num << "个" << endl;
  }
  cout << "需要" << day << "天卖完。" << endl;
  return 0;
} */
/* #include <iostream>
#include <string>

using namespace std;

int main() {
  string str = "Hello World!";
  cout << str.rfind("Wor") << endl;
  cout << str.find("Wor") << endl;
  cout << str.find_first_of("eld") << endl;
  cout << str.find_last_of("Wo") << endl;
  cout << str.find_last_not_of("He") << endl;
  cout << str.find_first_not_of("He") << endl;
  return 0;
} */
/* #include <iostream>
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
} */
/* int func1(int a, int b) {
  if (b) {
    return a / b;
  } else {
    // 抛出异常
    throw "division 0";
  }
} */
/* #include <cstring>
#include <iostream>

using namespace std;

bool func2(const char *str) {
  if (!str) {
    throw "NULL pointor";
  }

  int len = strlen(str);
  // 协议：##name=zhangsan;age=18#
  if (!(str[0] == '#' && str[1] == '#')) {
    // 帧头错误
    throw "frame header error";
  }
  if (!(str[len - 1] == '#' && str[len - 2] == '#')) {
    // 帧尾错误
    throw "frame tail error";
  }

  return true;
}

int main() {
  try {
    func2("##Hello World!");
  } catch (const char *msg) {
    // 可以判断是哪个错误
    cout << msg << endl;
  }
  return 0;
} */
/* #include <iostream>
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
} */
/* #include <cstring>
#include <exception>

class FHeaderErr : public std::exception {
 public:
  const char *what() const throw() { return "frame header error"; }
};

class FTailErr : public std::exception {
 public:
  const char *what() const throw() { return "frame tail error"; }
};

bool func(const char *str) {
  if (!str) {
    throw "NULL pointor";
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
} */
/* #include <iostream>

using namespace std;

template <class T>
class Person {
 public:
  Person(T id, T age) : m_id(id), m_age(age) {}
  void show() { cout << "ID: " << m_id << " Age: " << m_age << endl; }
  T m_id;
  T m_age;
};

void test() {
  // 函数模板在调用的时候，可以自动推导类型
  // 类模板必须显式指定类型
  Person<int> person(10, 20);
  person.show();
}

int main() {
  test();
  return 0;
} */
/* #include <iostream>

using namespace std;

template <class T>
void printArray(T *arr, int len) {
  for (int i = 0; i < len; ++i) {
    cout << arr[i] << " ";
  }
  cout << endl;
}

template <class T>
void bubbleSort(T *arr, int len) {
  for (int i = 0; i < len - 1; ++i) {
    for (int j = 0; j < len - 1 - i; ++j) {
      if (arr[j] < arr[j + 1]) {
        T temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

int main() {
  int arr[] = {2, 6, 1, 8, 9, 2};
  int len = sizeof(arr) / sizeof(int);
  printArray(arr, len);
  bubbleSort(arr, len);
  printArray(arr, len);

  char ch_arr[] = {'a', 'c', 'b', 'p', 't'};
  len = sizeof(ch_arr) / sizeof(char);
  printArray(ch_arr, len);
  bubbleSort(ch_arr, len);
  printArray(ch_arr, len);
  return 0;
} */
/* #include <iostream>

using namespace std;

template <class T>
class Person {
 public:
  Person() : m_age(0) {}
  T m_age;
};

// 原因：类去定义对象
// 这个对象需要编译分配内存
// 所有需要指定内存
class SubPerson : public Person<int> {};

int main() {} */
/* #include <iostream>

using namespace std;

template <class T>
class Animal {
 public:
  void cry() { cout << age << "岁动物在叫！" << endl; }
  T age;
};

template <class T>
class Cat : public Animal<T> {};

int main() {
  Cat<int> cat;
  return 0;
} */
/* #include <iostream>
using namespace std;

template <class T>
class Person {
 public:
  friend ostream& operator<<(ostream& os, Person<T>& person);
  Person(T age, T id);
  void show();

 private:
  T _age;
  T _id;
}; */
/* #include <iostream>
using namespace std;

#define Max(x, y) (x > y ? x : y)

int main() {
  int nx = 10, ny = 20;
  cout << Max(nx, ny) << endl;

  double dx = 12.3, dy = 45.6;
  cout << Max(dx, dy) << endl;

  string sx = "world", sy = "hello";
  cout << Max(sx, sy) << endl;

  char cx[256] = "hello", cy[256] = "world";
  cout << Max(cx, cy) << endl;

  return 0;
} */
/* #include <iostream>
using namespace std;

#define MAX(T) \
  T max_##T(T x, T y) { return x > y ? x : y; }

MAX(int)

MAX(double)

MAX(string)

int main() {
  int nx = 20, ny = 10;
  cout << max_int(nx, ny) << endl;

  double da = 1.14, db = 200.2;
  cout << max_double(da, db) << endl;

  string s1 = "dad", s2 = "mom";
  cout << max_string(s1, s2) << endl;

  return 0;
} */
/* #include <cfloat>
#include <iostream>

#define DEFAULT_LENGTH 10

using namespace std;

class ActScoring {
 public:
  // 构造函数
  ActScoring(const int length = DEFAULT_LENGTH)
      : _scores(new double[length]), _size(DEFAULT_LENGTH) {}

  // 析构函数
  ~ActScoring() {
    // 指针没被置为空指针
    if (_scores) {
      delete[] _scores;
      _scores = nullptr;
    }
  }

  // 设置评委数量
  void setSize(const int length) {
    delete[] _scores;
    _scores = new double[length];
    _size = length;
  }

  // 写入成绩
  void readScores() {
    for (int i = 0; i < _size; ++i) {
      cin >> _scores[i];
    }
  }

  // 活得平均成绩
  double getAverageScore() const {
    double max = DBL_MIN;
    double min = DBL_MAX;
    double total = .0;
    double average = .0;

    for (int i = 0; i < _size; ++i) {
      if (_scores[i] > max) {
        max = _scores[i];
      }
      if (_scores[i] < min) {
        min = _scores[i];
      }
      total += _scores[i];
    }
    average = (total - min - max) / (_size - 2);
    return average;
  }

 private:
  double *_scores;
  int _size;
};

int main() {
  ActScoring art_pieces[5];  // 五个作品

  double average_scores[5];  // 平均分数数组

  for (int i = 0; i < 5; ++i) {
    // 设置五个作品的评委数量
    art_pieces[i].setSize(5);
  }

  for (int i = 0; i < 5; ++i) {
    cout << "输入第 " << i + 1 << " 个作品每个评委的分数：\n";
    art_pieces[i].readScores();
    average_scores[i] = art_pieces[i].getAverageScore();
  }

  cout << "平均分分别为：\n";
  for (const double average_score : average_scores) {
    cout << average_score << " ";
  }

  cout << '\n';

  return 0;
} */
/* #include <cfloat>
#include <iostream>

#define DEFAULT_LENGTH 10

using namespace std;

class ActScoring {
 public:
  // 构造函数
  ActScoring(const int length = DEFAULT_LENGTH)
      : _scores(new double[length]), _size(DEFAULT_LENGTH) {}

  // 析构函数
  ~ActScoring() {
    // 指针没被置为空指针
    if (_scores) {
      delete[] _scores;
      _scores = nullptr;
    }
  }

  // 设置评委数量
  void setSize(const int length) {
    delete[] _scores;
    _scores = new double[length];
    _size = length;
  }

  // 写入成绩
  void readScores() {
    for (int i = 0; i < _size; ++i) {
      cin >> _scores[i];
    }
  }

  // 活得平均成绩
  double getAverageScore() const {
    double max = DBL_MIN;
    double min = DBL_MAX;
    double total = .0;
    double average = .0;

    for (int i = 0; i < _size; ++i) {
      if (_scores[i] > max) {
        max = _scores[i];
      }
      if (_scores[i] < min) {
        min = _scores[i];
      }
      total += _scores[i];
    }
    average = (total - min - max) / (_size - 2);
    return average;
  }

 private:
  double *_scores;
  int _size;
};

int main() {
  ActScoring art_pieces[5];  // 五个作品

  double average_scores[5];  // 平均分数数组

  double max_score = DBL_MIN;

  int max_score_index = -1;

  for (int i = 0; i < 5; ++i) {
    // 设置五个作品的评委数量
    art_pieces[i].setSize(5);
  }

  for (int i = 0; i < 5; ++i) {
    cout << "输入第 " << i + 1 << " 个作品每个评委的分数：\n";
    art_pieces[i].readScores();
    average_scores[i] = art_pieces[i].getAverageScore();
    if (average_scores[i] > max_score) {
      max_score = average_scores[i];
      max_score_index = i;
    }
  }

  cout << "平均分分别为：\n";
  for (const double average_score : average_scores) {
    cout << average_score << " ";
  }
  cout << '\n';

  cout << "分数最高的作品编号为：" << max_score_index + 1 << '\n';

  return 0;
} */
/* #include <windows.h>

#include <iostream>

using namespace std;

// 默认大小为 10
#define DEFAULT_CAPACITY 10

// 书籍类
class Book {
 public:
  // 构造函数
  // 初始化成员
  Book(string name, string author, string publishing_company, string isbn,
       string form)
      : _name(name),
        _author(author),
        _publishing_company(publishing_company),
        _form(form) {}

  // 默认构造函数
  Book() {}

  // 获得各个参数
  string getName() const { return _name; }
  string getAuthor() const { return _author; }
  string getPublishingCompany() const { return _publishing_company; }
  string getISBN() const { return _isbn; }
  string getForm() const { return _form; }

  // 设置各个参数
  void setName(string name) { _name = name; }
  void setAuthor(string author) { _author = author; }
  void setPublishingCompany(string publishing_company) {
    _publishing_company = publishing_company;
  }
  void setISBN(string isbn) { _isbn = isbn; }
  void setForm(string form) { _form = form; }

 private:
  string _name;                // 书名
  string _author;              // 作者
  string _publishing_company;  // 出版社
  string _isbn;                // ISBN
  string _form;                // 类别
};

class Librarianship {
 public:
  // 默认构造一个大小固定的图书管理系统
  Librarianship(const int capacity = DEFAULT_CAPACITY)
      : _num(0), _capacity(capacity), _books(new Book[capacity]) {}

  void menu() {
    int option;

    do {
      int add_num;
      int search_option;
      string name, author, isbn, publishing_company, form;
      showMenu();
      cout << "输入你的选择：";
      cin >> option;
      system("cls");
      switch (option) {
        case 1:
          cout << "输入添加书籍的数量：";
          cin >> add_num;
          addBooks(add_num);
          break;
        case 2:
          cout << "1. 书名\n";
          cout << "2. 作者\n";
          cout << "3. 出版社\n";
          cout << "4. ISBN\n";
          cout << "输入要查询方式：\n";
          cin >> search_option;
          system("cls");
          switch (search_option) {
            case 1:
              cout << "输入书名：\n";
              cin >> name;
              searchByName(name);
              break;
            case 2:
              cout << "输入作者：\n";
              cin >> author;
              searchByAuthor(author);
              break;
            case 3:
              cout << "输入出版社：\n";
              cin >> publishing_company;
              searchByPublishingCompany(publishing_company);
              break;
            case 4:
              cout << "输入 ISBN：\n";
              cin >> isbn;
              searchByPublishingCompany(publishing_company);
              break;
          }
          break;
        case 3:
          cout << "输入类别：\n";
          cin >> form;
          classifyByForm(form);
          break;
        case 4:
          cout << "输入指定的 ISBN：\n";
          cin >> isbn;
          eraseByISBN(isbn);
          break;
        case 5:
          break;
        default:
          cout << "输入错误，请重新输入。\n";
          break;
      }
      system("pause");
      system("cls");
    } while (option != 5);
  }

 private:
  int _num;       // 书的数量
  int _capacity;  // 管理系统的大小
  Book *_books;   // 存放书的数组

  void interact(int option) {

  }

  // 展示菜单
  void showMenu() {
    cout << "***=== 图书管理系统 ===***\n";
    cout << "       1. 添加书籍\n";
    cout << "       2. 查询书籍\n";
    cout << "       3. 分类书籍\n";
    cout << "       4. 删除书籍\n";
    cout << "       5. 退出系统\n";
  }

  // 添加书籍
  void addBooks(const int add_num) {
    // 添加书籍的数量大于剩余的数量，进行扩容操作
    if (add_num > _capacity - _num) {
      expandCapacity();
    }
    // 从最新的地方增加
    for (int i = _num; i < _num + add_num; ++i) {
      // 输入相应的信息
      cout << "输入第 " << i + 1 << " 本书的信息：";
      importBookInf(_books[i]);
      system("cls");
    }
    // 更新书的数量
    _num += add_num;
  }

  // 以书名查找
  void searchByName(const string name) const {
    cout << "以书名查找。\n";
    bool flag = false;  // 是否找到
    // 查找书籍
    for (int i = 0; i < _num; ++i) {
      if (_books[i].getName() == name) {
        // 输出书的信息
        exportBookInf(_books[i]);
        flag = true;  // 找到了
      }
    }

    if (!flag) {
      cout << "抱歉，没有找到指定书籍。\n";
    }
  }

  // 以作者查找
  void searchByAuthor(const string author) const {
    cout << "以作者查找。\n";
    bool flag = false;  // 是否找到
    // 查找书籍
    for (int i = 0; i < _num; ++i) {
      if (_books[i].getAuthor() == author) {
        // 输出书的信息
        exportBookInf(_books[i]);
        flag = true;  // 找到了
      }
    }
  }

  // 以出版社查找
  void searchByPublishingCompany(const string publishing_company) const {
    cout << "以出版社查找。\n";
    bool flag = false;  // 是否找到
    // 查找书籍
    for (int i = 0; i < _num; ++i) {
      if (_books[i].getPublishingCompany() == publishing_company) {
        // 输出书的信息
        exportBookInf(_books[i]);
        flag = true;  // 找到了
      }
    }

    if (!flag) {
      cout << "抱歉，没有找到指定书籍。\n";
    }
  }

  // 以 ISBN 查找
  void searchByISBN(const string isbn) const {
    cout << "以 ISBN 查找。\n";
    bool flag = false;  // 是否找到
    // 查找书籍
    for (int i = 0; i < _num; ++i) {
      if (_books[i].getISBN() == isbn) {
        // 输出书的信息
        exportBookInf(_books[i]);
        flag = true;  // 找到了
      }
    }

    if (!flag) {
      cout << "抱歉，没有找到指定书籍。\n";
    }
  }

  // 分类别输出
  void classifyByForm(const string form) {
    bool flag = false;
    for (int i = 0; i < _num; ++i) {
      if (_books[i].getForm() == form) {
        exportBookInf(_books[i]);
        flag = true;
      }
    }

    if (!flag) {
      cout << "抱歉，没有该类别的书籍。\n";
    }
  }

  // 删除书籍
  void eraseByISBN(const string isbn) {
    bool flag = false;
    // 读指针
    int write_index = 0;
    // 写指针
    int read_index = 0;

    while (read_index < _num) {
      // 如果读到了指定的数据
      if (_books[read_index].getISBN() == isbn) {
        flag = true;
        // 读指针指向下一个元素
        ++read_index;
        // 数量减少
        --_num;
        // 跳过写入这个元素
        continue;
      }

      // 将数据写入
      _books[write_index] = _books[read_index];
      ++write_index;
      ++read_index;
    }

    if (!flag) {
      cout << "抱歉，没有找到指定书籍。\n";
    }
  }

  // 扩容函数，为私有
  // 扩大为原来的两倍
  void expandCapacity() {
    // 新的存放地点
    Book *new_books = new Book[_capacity * 2];
    // 拷贝过去
    for (int i = 0; i < _capacity; ++i) {
      new_books[i] = _books[i];
    }
    // 删除原来的
    delete[] _books;
    // 指向新的
    _books = new_books;
    // 置为空指针
    new_books = nullptr;
    // 大小增大
    _capacity *= 2;
  }

  // 输入书的信息的函数
  void importBookInf(Book &book) {
    string name, author, publishing_company, isbn, form;
    cout << "\n书名：";
    cin >> name;
    cout << "作者：";
    cin >> author;
    cout << "出版社：";
    cin >> publishing_company;
    cout << "ISBN：";
    cin >> isbn;
    cout << "类别：";
    cin >> form;
    book.setName(name);
    book.setAuthor(author);
    book.setPublishingCompany(publishing_company);
    book.setISBN(isbn);
    book.setForm(form);
  }

  // 输出书籍信息
  void exportBookInf(const Book &book) const {
    cout << "书名：" << book.getName() << '\n';
    cout << "作者：" << book.getAuthor() << '\n';
    cout << "出版社：" << book.getPublishingCompany() << '\n';
    cout << "ISBN：" << book.getISBN() << '\n';
    cout << "类别：" << book.getForm() << '\n';
    cout << '\n';
  }
};

int main() {
  Librarianship librarianship;
  librarianship.menu();
  return 0;
}
 */
/* #include <iostream>

using namespace std;

// 每个学生的成绩
class Score {
 public:
  Score(const string name, const double score) : _name(name), _score(score) {}

  Score() {}

  string getName() const { return _name; }
  double getScore() const { return _score; }

  void setName(string name) { _name = name; }
  void setScore(double score) { _score = score; }

 private:
  string _name;   // 学生名字
  double _score;  // 学生成绩
};

class Management {
 public:
  Management(int num) : _scores(new Score[num]), _num(num) {}

  Management() {}

  void setNum(int num) {
    _scores = new Score[num];
    _num = num;
  }

  void importInf() {
    string name;
    double score;
    double total_score = .0;
    for (int i = 0; i < _num; ++i) {
      cout << "输入第 " << i + 1 << " 个同学的试卷信息：\n";
      cout << "姓名：";
      cin >> name;
      cout << "成绩：";
      cin >> score;
      _scores[i].setName(name);
      _scores[i].setScore(score);
      total_score += score;
    }
    _average_score = total_score / _num;  // 计算平均成绩
  }

  void exportRankInf() {
    int excellent_num = 0;
    int good_num = 0;
    int medium_num = 0;
    int pass_num = 0;
    int fail_num = 0;

    analyzeScore(excellent_num, medium_num, good_num, pass_num, fail_num);

    cout << "优秀人数为：" << excellent_num << "；比例为：" << _excellent_rate
         << '\n';
    cout << "良好人数为：" << good_num << "；比例为：" << _good_rate << '\n';
    cout << "中人数为：" << medium_num << "；比例为：" << _medium_rate << '\n';
    cout << "合格人数为：" << pass_num << "；比例为：" << _pass_rate << '\n';
    cout << "不合格人数为：" << fail_num << "；比例为：" << _fail_rate << '\n';
  }

  void analyzeScore(int &excellent_num, int &medium_num, int &good_num,
                    int &pass_num, int &fail_num) {
    for (int i = 0; i < _num; ++i) {
      if (_scores[i].getScore() >= _average_score + 10) {
        ++excellent_num;
      } else if (_scores[i].getScore() >= _average_score &&
                 _scores[i].getScore() < _average_score + 10) {
        ++good_num;
      } else if (_scores[i].getScore() >= _average_score - 10 &&
                 _scores[i].getScore() < _average_score) {
        ++medium_num;
      } else if (_scores[i].getScore() >= _average_score - 20 &&
                 _scores[i].getScore() < _average_score - 10) {
        ++pass_num;
      } else {
        ++fail_num;
      }
    }

    _excellent_rate = (double)excellent_num / _num;
    _good_rate = (double)good_num / _num;
    _medium_rate = (double)medium_num / _num;
    _pass_rate = (double)pass_num / _num;
    _fail_rate = (double)fail_num / _num;
  }

  void analyzeProblem() {
    if (_excellent_rate >= 0.5) {
      _problem = "优";
    } else if (_good_rate >= 0.4 && _good_rate <= 0.6) {
      _problem = "适中";
    } else if (_pass_rate >= 0.4 && _pass_rate <= 0.6) {
      _problem = "较难";
    } else if (_fail_rate >= 0.3) {
      _problem = "难";
    }
  }

  void exportProblemInf() { cout << "试卷难度为：" << _problem << '\n'; }
  string getProblem() const { return _problem; }
  double getAverageScore() const { return _average_score; }
  int getNum() const { return _num; }
  double getExcellentRate() const { return _excellent_rate; }
  double getGoodRate() const { return _good_rate; }
  double getMediumRate() const { return _medium_rate; }
  double getPassRate() const { return _pass_rate; }
  double getFailRate() const { return _fail_rate; }

 private:
  string _problem;        // 试卷难度
  double _average_score;  // 平均成绩
  int _num;               // 学生人数
  Score *_scores;         // 成绩数组
  // 各个比例
  double _excellent_rate;
  double _good_rate;
  double _medium_rate;
  double _pass_rate;
  double _fail_rate;
};

class AnalysisReport {
 public:
  static void analyzeProblemTrend(Management *managements, int num) {
    bool smooth_flag = true;
    bool rising_flag = true;
    bool falling_flag = true;
    int *problems = new int[num];
    for (int i = 0; i < num; ++i) {
      if (managements[i].getProblem() == "难") {
        problems[i] = 4;
      } else if (managements[i].getProblem() == "较难") {
        problems[i] = 3;
      } else if (managements[i].getProblem() == "适中") {
        problems[i] = 2;
      } else if (managements[i].getProblem() == "易") {
        problems[i] = 1;
      }
    }
    for (int i = 1; i < num; ++i) {
      if (problems[i] > problems[i - 1]) {
        smooth_flag = false;
        falling_flag = false;
      } else if (problems[i] < problems[i - 1]) {
        smooth_flag = false;
        rising_flag = false;
      }
    }

    cout << "难度变化状态为：";
    if (smooth_flag) {
      cout << "相当\n";
    } else if (rising_flag) {
      cout << "上升\n";
    } else if (falling_flag) {
      cout << "下降\n";
    }
  }

  static void analyzeAverageScoreTrend(Management *managements, int num) {
    bool smooth_flag = true;
    bool rising_flag = true;
    bool falling_flag = true;
    int *problem = new int[num];
    for (int i = 1; i < num; ++i) {
      if (managements[i].getAverageScore() >
          managements[i - 1].getAverageScore()) {
        smooth_flag = false;
        falling_flag = false;
      } else if (managements[i].getAverageScore() <
                 managements[i - 1].getAverageScore()) {
        smooth_flag = false;
        rising_flag = false;
      }
    }

    cout << "平均成绩变化状态为：";
    if (smooth_flag) {
      cout << "相当\n";
    } else if (rising_flag) {
      cout << "上升\n";
    } else if (falling_flag) {
      cout << "下降\n";
    }
  }

  static void analyzeExcellentRate(Management *managements, int num) {
    bool smooth_flag = true;
    bool rising_flag = true;
    bool falling_flag = true;
    int *problem = new int[num];
    for (int i = 1; i < num; ++i) {
      if (managements[i].getExcellentRate() >
          managements[i - 1].getExcellentRate()) {
        smooth_flag = false;
        falling_flag = false;
      } else if (managements[i].getExcellentRate() <
                 managements[i - 1].getExcellentRate()) {
        smooth_flag = false;
        rising_flag = false;
      }
    }

    cout << "优档变化状态为：";
    if (smooth_flag) {
      cout << "相当\n";
    } else if (rising_flag) {
      cout << "上升\n";
    } else if (falling_flag) {
      cout << "下降\n";
    }
  }

  static void analyzeFailRate(Management *managements, int num) {
    bool smooth_flag = true;
    bool rising_flag = true;
    bool falling_flag = true;
    int *problem = new int[num];
    for (int i = 1; i < num; ++i) {
      if (managements[i].getFailRate() > managements[i - 1].getFailRate()) {
        smooth_flag = false;
        falling_flag = false;
      } else if (managements[i].getFailRate() <
                 managements[i - 1].getFailRate()) {
        smooth_flag = false;
        rising_flag = false;
      }
    }

    cout << "不合格档变化状态为：";
    if (smooth_flag) {
      cout << "相当\n";
    } else if (rising_flag) {
      cout << "上升\n";
    } else if (falling_flag) {
      cout << "下降\n";
    }
  }
};

int main() {
  Management managements[4];
  for (int i = 0; i < 4; ++i) {
    cout << "输入第 " << i + 1 << " 场考试的信息：\n";
    managements[i].importInf();
  }
  for (int i = 0; i < 4; ++i) {
    cout << "输出第 " << i + 1 << " 场考试的信息：\n";

    managements[i].exportRankInf();
    managements[i].exportProblemInf();
  }
  AnalysisReport::analyzeProblemTrend(managements, 4);
  AnalysisReport::analyzeAverageScoreTrend(managements, 4);
  AnalysisReport::analyzeExcellentRate(managements, 4);
  AnalysisReport::analyzeFailRate(managements, 4);
  return 0;
} */
/* #include <iostream>

int main() {
  int a = 0;
  std::cout << "Hello World!\n";
  return 0;
} */
/* #include <iostream>

template <class T>
class A {
 public:
  int a;
};

int main() {
  for (int i = 0; i < 10; ++i) {
    std::cout << i << ' ';
  }
  int a = 0;
  return 0;
} */
#include <iostream>

using namespace std;

int insert(int arr[], int len, int x) {
  int index = 0;  // 指定元素的索引

  // 寻找插入的位置，即第一个要插入的数小的数
  while (index < len && x < arr[index]) {
    ++index;
  }

  // 将后一个数据用前一个覆盖
  for (int i = len - 1; i >= index; --i) {
    arr[i + 1] = arr[i];
  }
  arr[index] = x;

  // 因为数组下标使从零开始的，索引加一
  return index + 1;
}

int main() {
  int arr[100] = {0};  // 一个超级大的数组，并初始化为 0
  int n = 0;           // 实际数组长度
  int p = 0;           // 指定坐标索引
  int count = 0;       // 计数器，记录插入的第几个数
  int num = 0;         // 要插入的数

  cout << "请输入原降序数列的数据个数（<20):";
  cin >> n;
  cout << "请输入" << n << "个数（降序）:\n";
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }

  // 死循环，题中未给插入多少个数
  while (true) {
    // 开始计数
    ++count;
    cout << "*************************************\n";
    cout << "请输入欲插入的第" << count << "个数：";
    cin >> num;
    p = insert(arr, n, num);
    cout << "插入在第" << p << "个位置\n";
    cout << "插入第" << count << "个数后的数据序列为：\n";
    for (int i = 0; i <= n; i++) {
      cout << arr[i] << " ";
    }
    cout << '\n';
    ++n;
  }
}