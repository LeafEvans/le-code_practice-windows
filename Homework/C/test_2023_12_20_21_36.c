#include <stdio.h>

enum Day { Mon = 1, Tues = 3, Wed = 5, Thur, Fri, Sat, Sun };
// 枚举类型将可能的取值列出，这些值叫做枚举常量

int main(void) {
  enum Day d = Fri;
  // 这里面的值只能是枚举常量

  printf("%d\n", Mon);
  printf("%d\n", Tues);
  printf("%d\n", Wed);
  printf("%d\n", Thur);

  return 0;
}