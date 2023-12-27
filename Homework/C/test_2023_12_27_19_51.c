#include <stdio.h>
#include <windows.h>

int main(void) {
  FILE *pf = fopen("test_12_27.txt", "w");
  fputs("abcded", pf);
  printf("睡眠10秒-已经写数据了,打开test.txt文件发现文件没有内容\n");
  Sleep(10000);
  printf("刷新缓冲区\n");
  fflush(pf);  // 刷新缓冲区时，才将输入缓冲区的数据写到文件（磁盘）
  fclose(pf);  // 注：fclose在关闭文件的时候，也会刷新缓冲区
  pf = NULL;
  return 0;
}