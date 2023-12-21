#include <stdio.h>
#include <string.h>

void leftRotateA(char *, int);
void leftRotateB(char *, int);
void reverseStr(char *, char *);

int main(void) {
  char str[] = "abcdef";
  int k = 0;
  scanf("%d", &k);
  leftRotateB(str, k);
  printf("%s\n", str);
  return 0;
}

void leftRotateA(char str[], int k) {
  int len = strlen(str);  // 计算长度
  k %= len;               // 减少不必要的循环次数
  for (int i = 0; i < k; i++) {
    char tmp = str[0];                   // 存储首字符
    for (int j = 0; j < len - 1; j++) {  // 只需要循环len - 1次即可
      str[j] = str[j + 1];  // 将后一个字符赋给前一个字符
    }
    str[len - 1] = tmp;  // 将末尾元素赋值为临时的那个变量
  }
}

void reverseStr(char *left, char *right) {
  while (left < right) {
    char tmp = *left;
    *left = *right;
    *right = tmp;
    left++;
    right--;
  }
}

void leftRotateB(char str[], int k) {
  int len = strlen(str);
  k %= len;
  reverseStr(str, str + k - 1);
  reverseStr(str + k, str + len - 1);
  reverseStr(str, str + len - 1);
}
