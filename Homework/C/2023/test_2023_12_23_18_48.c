#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  FILE *pf = fopen("test_1.txt", "r+");
  if (pf == NULL) {
    printf("%s\n", strerror(errno));
    return 1;
  }
  fclose(pf);  // 类似 free
  pf = NULL;
  return 0;
}