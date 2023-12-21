#include <stdio.h>

int main(void) {
  char *c[] = {"ENTER", "NEW", "POINT", "FIRST"};
  // 将4个字符串首字符的地址存到c数组中
  char **cp[] = {c + 3, c + 2, c + 1, c};
  // cp数组存的是char **，因为c数组是char *的地址，要存指针数组中元素的地址
  // 所以是char **
  char ***cpp = cp;
  // 因为cp是首元素地址，其类型为char **；所以存它的地址就要用char ***
  printf("%s\n", **++cpp);  // cpp指向的是c+3；加加操作后，指向c+2
  // POINT // 解引用操作后得到c+2的内容
  printf(
      "%s\n",
      *--*++cpp +
          3);  // c+2的地址加加后指向c+1，然后c+1再减1就是c，解引用后指向ENTER,再进行+3操作，从第四个字符开始打印
  // ER
  printf(
      "%s\n",
      *cpp[-2] +
          3);  // cpp[-2]==*(cpp-2)，代表此时cpp-2的地址指向c+3，再对c+3进行解引用操作，就是FIRST，然后+3，从第四个字符打印
  // ST
  // 注意cpp--会改变值，而cpp-2不会
  printf(
      "%s\n",
      cpp[-1][-1] +
          1);  // cpp还是指向c+1，cpp-1后指向c+2，然后解引用得到c+2，c+2-1就是c+1,对c+1解引用，指向NEW的首字符，+1后从第二个字符开始打印

  return 0;
}