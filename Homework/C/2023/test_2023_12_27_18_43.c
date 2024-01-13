#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int c = 0;  // 注意：int,非char，要求处理EOF
  FILE *fp = fopen("test.txt", "r");

  if (!fp) {
    perror("File opening failed");
    return EXIT_FAILURE;
  }

  // fgetc当读取失败或遇到文件结束的时候，都会返回EOF
  while ((c = fgetc(fp)) != EOF) putchar(c);  // 标准C I/O读取文件循环

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