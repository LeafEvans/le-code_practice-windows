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
