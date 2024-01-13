#include <stdio.h>
#define MAX 100

int main(void) {
#if !defined(MAX)  // #ifndef MAX 可以替代
  printf("max\n");
#endif
  return 0;
}
