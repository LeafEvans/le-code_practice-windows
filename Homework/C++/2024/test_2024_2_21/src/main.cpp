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
#include <iostream>

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
}