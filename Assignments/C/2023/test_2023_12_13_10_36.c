#include <stdio.h>
#include <string.h>

int main(void) {
  char str[100] = ".fafa.afaff...fafaf";
  char buf[100] = ".";
  char *ret = NULL;

  for (ret = strtok(str, buf); ret != NULL; ret = strtok(NULL, buf)) {
    printf("%s\n", ret);
  }

  return 0;
}