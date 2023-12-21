#include <stdio.h>

int main(void) {
  char *a[] = {"work", "at", "alibaba"};  // 运用指针数组存放常量字符串
  char **pa = a;  // 将首元素地址赋给二级指针pa
  pa++;           // pa进行加1操作，跳过一个一级指针
  printf("%s\n", *pa);  // 对第二个指针进行解引用操作，访问的就是"at"
  return 0;
}