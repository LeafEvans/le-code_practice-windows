#include <stdio.h>
#define MAX 1000
#define STR "hello world"
#define print printf("hehe\n")
#define DEBUG_PRINT                                                            \
  printf("file:%s\tline:%d\tdate:%s\ttime:%s\n", __FILE__, __LINE__, __DATE__, \
         __TIME__)

int main(void) {
  int m = MAX;
  print;
  printf("%d\n", MAX);
  puts(STR);
  return 0;
}