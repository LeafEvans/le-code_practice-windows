#include <assert.h>
#include <stdio.h>
#include <string.h>

int myStrcmp(const char *str1, const char *str2) {
  assert(str1 || str2);
  while (*str1 == *str2)  // 两个字符指针指向的字符相等再进入
  {
    if (*str1 == '\0') {
      return 0;  // 如果其中一个解引用操作后等于 '\0'，返回 0
    }

    ++str1;
    ++str2;
  }

  return (*str1 - *str2);
}

int main(void) {
  char str1[20] = "zhangsan";
  char str2[] = "zhangsanfeng";
  int ret = strcmp(str1, str2);

  if (ret > 0) {
    printf(">\n");
  } else if (ret < 0) {
    printf("<\n");
  } else {
    printf("=\n");
  }

  return 0;
}