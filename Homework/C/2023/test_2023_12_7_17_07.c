#include <assert.h>
#include <stdio.h>
#include <string.h>

char *myStrcat(char *dest, const char *src) {
  char *original_dest = dest;

  assert(dest || src);
  while (*dest) {
    ++dest;
  }

  while (*dest++ = *src++) {
    ;
  }

  return original_dest;
}

int main(void) {
  char arr1[20] = "hello ";
  myStrcat(arr1, arr1);
  printf("%s\n", arr1);
  return 0;
}