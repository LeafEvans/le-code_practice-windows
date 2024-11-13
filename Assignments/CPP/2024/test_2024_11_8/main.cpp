/* #include <fmt/core.h>

#include <Eigen/Dense>
#include <iostream>

using namespace std;

int main() {
  Eigen::Matrix2d mat;
  mat(0, 0) = 1;
  mat(0, 1) = 2;
  mat(1, 0) = 3;
  mat(1, 1) = 4;

  cout << "Matrix:\n" << mat << endl;

  Eigen::Matrix2d result = mat * mat;
  cout << "Matrix squared:\n" << result << endl;

  return 0;
} */
/* #include <iostream>

using namespace std;

int main() {
  return 0;
} */
/* #include <iostream>


using namespace std;

namespace name_a {
int x;
void fun() { cout << "name_a" << endl; }
}  // namespace name_a

namespace name_b {
int x;
void func() { cout << "name_b" << endl; }
}  // namespace name_b

int main() {
  name_a::x = 100;
  name_b::x = 1000;
  cout << name_a::x << endl;
  cout << name_b::x << endl;
  return 0;
} */
/* #include <iostream>

using namespace std;

namespace A {
int a = 10;
namespace B {
int a = 20;
}  // namespace B

}  // namespace A

void test() {
  cout << "A::a : " << A::a << endl;
  cout << "A::B::a : " << A::B::a << endl;
}

int main() {
  test();
  return 0;
} */
/* #include <iostream>

using namespace std;

namespace A {
int a = 10;
void func() { cout << "A" << endl; }
}  // namespace A

int main() {
  namespace a = A;
  a::func();
  return 0;
} */
/* #include <iostream>

using namespace std;

int main() {
  int a = 10;
  int& b = a;
  cout << "a: " << a << endl;
  cout << "b: " << b << endl;

  b = 100;
  cout << "a: " << a << endl;
  cout << "b: " << b << endl;

  return 0;
} */
/* #include <iostream>

using namespace std;

struct test {
  int &a;
  int &b;
};

int main() {
  cout << sizeof(test) << endl;
  return 0;
} */
/* #include <iostream>

using namespace std;

struct Teacher {
  char name[32];
  int age;
};

void printTeacher(Teacher& t) {
  cout << t.age << endl;
  t.age = 32;
}

inline int add(int a, int b) {
  return a + b;
}

void testFunc(int a = 10, int b = 20) {
  cout << "a + b = " << a + b << endl;
}

int main() {
  testFunc();
  testFunc(100);
  testFunc(100, 200);
  return 0;
} */
/* #include <iostream>

using namespace std;

class CAnimal {
 public:
  char name[32];
  int age;

  void cry(const char* voice) { cout << name << ": " << voice << endl; }
}; */
/* #include <iostream>
#include <string>

using namespace std;

class Person {
 public:
  void print() {
    cout << "name: " << _name << endl;
    cout << "age: " << _age << endl;
  }

  void set_age(int age) { _age = age; }
  int get_age() { return _age; }
  void set_name(string name) { _name = name; }
  string get_name() { return _name; }

 protected:
  string _name;
  int _age;
};

class Student : public Person {
 protected:
};

class Teacher : public Person {
 protected:
};

int main() {
  Student s;
  Teacher t;
  s.set_age(10);
  cout << s.get_age() << endl;
  s.set_name("lisi");
  cout << s.get_name() << endl;
  s.print();

  cout << sizeof(Person) << endl;
  cout << sizeof(Student) << endl;
  cout << sizeof(Teacher) << endl;

  return 0;
} */
#include <iostream>

using namespace std;

class A {
 public:
  A() { cout << "A()" << endl; }
  ~A() { cout << "~A()" << endl; }

  A(int a, int b) { cout << "A(int a, int b)" << endl; }

  int getX() { return x; }
  int getY() {return y;}

 protected:
  int x;

 protected:
  int y;
};

class B : public A {
 public:
  B() { cout << "B()" << endl; }
  ~B() { cout << "~B()" << endl; }
};

int main() {
  B b;
  return 0;
}
