#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  FILE *pf = fopen("text.txt", "r");
  if (pf == NULL) {
    printf("%s\n",
           strerror(errno));  // errno - C语言设置的一个全局的错误码存放的变量
    return 1;
  }
  return 0;
}