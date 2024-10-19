#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

class Animal {
 public:
  char *name;
  int age;

  Animal(void) {
    name = (char *)malloc(32);
    cout << "Animal(void)" << endl;
  }

  Animal(const char *name1) {
    int len = strlen(name1);
    name = (char *)malloc(len + 1);  // 最后一个为 \0
    strcpy(name, name1);
  }

  // 析构函数
  ~Animal(void) {
    if (name) free(name);
    // 因为系统只会自动回收栈区的内存
    // 所以要手动回收堆区的申请的内存
    cout << "~Animal(void)" << endl;
  }
};

int main(int argc, char **argv) {
  Animal a;
  cout << "Hello World!" << endl;
  return EXIT_SUCCESS;
}
