#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 函数：判断给定的字符串是否为有效的IPv4地址
int isValidIP(const char *ip) {
  int num, dots = 0;  // num用来存放点分隔的每个数字，dots用来计数点的数量
  const char *ptr;  // 指针，用于遍历IP字符串

  if (ip == NULL) return 0;  // 如果IP字符串为空，直接返回无效

  ptr = ip;  // 初始化指针为指向IP字符串的开始

  // 遍历字符串直到结束
  while (*ptr) {
    // 如果当前字符是点
    if (*ptr == '.') {
      dots++;    // 增加点的计数
      ptr++;     // 移动到下一个字符
      continue;  // 继续下一次循环
    }

    // 如果点的数量超过3个，则返回无效
    if (dots > 3) {
      return 0;
    }

    // 如果当前字符不是数字，则返回无效
    if (!isdigit(*ptr)) {
      return 0;
    }

    // 将数字字符转换为整数
    num = 0;
    while (*ptr && isdigit(*ptr)) {
      num = num * 10 + (*ptr - '0');
      // 如果数字大于255，则返回无效
      if (num > 255) {
        return 0;
      }
      ptr++;  // 移动到下一个字符
    }

    // 如果遇到的不是点也不是字符串的结束，则返回无效
    if (*ptr != '.' && *ptr != '\0') {
      return 0;
    }

    // 如果点后面紧跟非数字字符或字符串结束，返回无效
    if (*ptr == '.' && (!isdigit(*(ptr + 1)) || *(ptr + 1) == '\0')) {
      return 0;
    }
  }

  // 如果点的数量不是3，则返回无效
  if (dots != 3) {
    return 0;
  }

  // 如果所有检查都通过，则返回有效
  return 1;
}

int main() {
  int n;  // 用来存储用户将要输入的IP地址数
  printf("Enter the number of IP addresses to check: ");
  scanf("%d", &n);  // 读取用户输入的IP地址数

  // 循环读取并检查每个IP地址
  for (int i = 0; i < n; i++) {
    char ip[100];  // 存储IP地址的字符数组
    printf("Enter IP address #%d: ", i + 1);
    scanf("%s", ip);  // 读取用户输入的IP地址

    // 调用isValidIP函数检查IP地址是否有效
    if (isValidIP(ip)) {
      printf("'%s' is a valid IP address.\n", ip);
    } else {
      printf("'%s' is NOT a valid IP address.\n", ip);
    }
  }

  return 0;
}
