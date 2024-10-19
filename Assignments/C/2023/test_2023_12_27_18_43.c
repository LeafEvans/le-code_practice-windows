#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int c = 0;  // 注意：int，非 char，要求处理 EOF
  FILE *fp = fopen("test.txt", "r");

  if (!fp) {
    perror("File opening failed");
    return EXIT_FAILURE;
  }

  // fgetc 当读取失败或遇到文件结束的时候，都会返回 EOF
  while ((c = fgetc(fp)) != EOF) putchar(c);  // 标准 C I/O 读取文件循环

  // 判断是什么原因结束的
  if (ferror(fp)) {
    puts("I/O error when reading");
  } else if (feof(fp)) {
    puts("End of fiel reached successfully");
  }

  fclose(fp);
  fp = NULL;

  return 0;
}