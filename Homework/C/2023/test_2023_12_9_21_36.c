#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  FILE *pf = fopen("text.txt", "r");
  if (pf == NULL) {
    // errno 是 C 语言设置的一个全局的错误码存放的变量
    printf("%s\n", strerror(errno));
    return 1;
  }
  return 0;
}