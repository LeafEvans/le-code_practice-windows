#include <stdio.h>

int main(void) {
  char *c[] = {"ENTER", "NEW", "POINT", "FIRST"};
  // 将 4 个字符串首字符的地址存到 c 数组中
  char **cp[] = {c + 3, c + 2, c + 1, c};
  // cp 数组存的是 char **，因为 c 数组是 char *
  // 的地址，要存指针数组中元素的地址 所以是 char **
  char ***cpp = cp;
  // 因为 cp 是首元素地址，其类型为 char **；所以存它的地址就要用 char ***
  printf("%s\n", **++cpp);  // cpp 指向的是 c + 3；加加操作后，指向 c + 2
  // POINT // 解引用操作后得到 c + 2 的内容
  // c + 2 的地址加加后指向 c + 1，然后 c + 1 再减 1 就是 c，解引用后指向
  // ENTER，再进行 +3 操作，从第四个字符开始打印
  printf("%s\n", *--*++cpp + 3);
  // ER
  // cpp[-2]==*(cpp-2)，代表此时 cpp - 2 的地址指向 c + 3，再对 c + 3
  // 进行解引用操作，就是 FIRST，然后 +3，从第四个字符打印
  printf("%s\n", *cpp[-2] + 3);
  // ST
  // 注意 cpp-- 会改变值，而 cpp - 2 不会
  // cpp 还是指向 c + 1，cpp - 1 后指向 c + 2，然后解引用得到 c + 2，c + 2 - 1
  // 就是 c + 1,对 c + 1 解引用，指向 NEW 的首字符，+1 后从第二个字符开始打印
  printf("%s\n", cpp[-1][-1] + 1);

  return 0;
}