#include <stdio.h>

int main(void) {
  const char *sep = "@.";
  char email[] = "yjx@leafalice.com";
  char cp[30] = {0};
  strcpy(cp, email);

  char *ret = NULL;
  for (ret = strtok(cp, sep);  // 初始化
       ret != NULL;  // 如果返回值不为空指针，就继续循环
       ret = strtok(NULL, sep))  // 将 ret 赋值为新的变量
  {
    printf("%s\n", ret);
  }

  return 0;
}