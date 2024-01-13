#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  FILE *pf = fopen("test_12_23.txt", "a");
  if (pf == NULL) {
    printf("%s\n", strerror(errno));
    return 1;
  }
  fputs("\nhello world", pf);
  fclose(pf);
  pf = NULL;
  return 0;
}