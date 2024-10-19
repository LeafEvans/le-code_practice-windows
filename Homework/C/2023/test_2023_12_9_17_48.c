#include <assert.h>
#include <stdio.h>
#include <string.h>

char *myStrstr(const char *str1, const char *str2) {
  assert(str1 && str2);     // 警告用的
  const char *ptr1 = str1;  // 将目标字符串的首字符赋给 str1
  const char *ptr2 = str2;  // 将寻找字符串的首字符赋给 str2
  const char *p =
      str1;  // 这个是用来返回查找的字串的地址的,并且用来一个一个检索字符的

  while (*p) {
    ptr1 = p;  // 从那个可能的首地址找
    ptr2 = str2;
    while (*ptr1 != '\0' && *ptr2 != '\0' && *ptr1 == *ptr2) {
      ptr1++;  // 两个指针加 1
      ptr2++;
    }
    if (*ptr2 ==
        '\0')  // 如果当前的 *ptr2 为 '\0'，说明找到了，返回该字串在目标字符串的首字符地址
    {
      return (char *)p;  // 强制类型转换后返回
    }
    p++;  // 如果找不到，那就从下一个字符开始检索
  }
  return NULL;
}

int main(void) {
  char email[] = "yjx@leafalice.com";
  char substr[] = "leafalice";
  char *ret = myStrstr(email, substr);
  if (ret == NULL) {
    printf("子串不存在\n");
  } else {
    printf("%s\n", ret);
  }
  return 0;
}