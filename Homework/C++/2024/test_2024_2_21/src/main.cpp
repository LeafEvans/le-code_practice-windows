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

#include <iostream>
#include <string>

using namespace std;

int main(void) {
  string s1("Real Steel");
  s1.replace(1, 2, 5, '0');
  cout << s1 << endl;
  return 0;
}

/* int main(void) {
  string s1("Real Steel");
  int pos = s1.find_first_not_of("aRel");
  cout << pos << endl;
  return 0;
} */
