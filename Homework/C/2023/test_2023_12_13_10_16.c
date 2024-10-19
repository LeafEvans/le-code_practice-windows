#include <ctype.h>
#include <stdio.h>
#include <string.h>

int isValidIP(const char *ip);  // 函数声明

int main(void) {
  int n = 0;
  char ip[51] = {0};

  scanf("%d\n", &n);
  for (int i = 0; i < n; i++) {
    fgets(ip, sizeof(ip), stdin);
    ip[strcspn(ip, "\n")] = '\0';
    printf("%s\n", isValidIP(ip) ? "yes" : "no");
  }

  return 0;
}

int isValidIP(const char *ip) {
  int num = 0;
  int dots = 0;

  if (ip == NULL || *ip == '.') {
    // 如果第一个字符是 . 或者这个指针指向一个空指针
    return 0;  // 返回 0
  }

  const char *ptr = ip;  // 定义一个遍历用的指针

  while (*ptr) {  // 当这个字符不是 \0 时进入循环
    if (*ptr == '.') {  // 当这个字符是 . 时，说明此时在一个数的末尾
      dots++;           // 有一个点了
      ptr++;            // 指向下一个字符
      continue;  // 跳过下面的过程，因为下面的过程是判断 .xxx. 中的 xxx 的
    }

    if (dots > 3) {  // 如果 . 的个数大于 3 个，返回 0
      return 0;
    }

    if (!isdigit(*ptr)) {  // 如果这 num 的首字符是个非数字字符，返回 0
      return 0;
    }

    num = 0;  // 赋值给这个数为 0
    while (*ptr &&
           isdigit(*ptr)) {  // 当指针不指向末尾并且是个数字字符时，进入循环
      num = num * 10 + (*ptr - '0');  // 计算 num 的大小
      if (num > 255) {                // 大于 255，返回 0
        return 0;
      }
      ptr++;  // 指向下一个字符
    }

    if (*ptr != '.' && *ptr != '\0') {
      return 0;  // 一个数遍历完了，如果它的下一个字符不是 . 或者 \0，返回 0
    }  // 比如 .1a1. 当遍历完 1 后跳出循环，发现下一个不是所要求的字符

    if (*ptr == '.' && (!isdigit(*(ptr + 1)) || *(ptr + 1) == '\0')) {
      return 0;  // 如果现在指向了 .，但它的下一个字符不是数字字符或者字符串终止标志，返回 0
    }
  }

  if (dots != 3) {
    return 0;  // 如果点的个数不是 3，返回 0
  }

  return 1;  // 通过所有情况，返回 1
}
