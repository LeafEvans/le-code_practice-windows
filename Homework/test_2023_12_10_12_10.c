#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  char arr[] = "hello world";
  memset(arr + 6, 'x', 5);
  printf("%s\n", arr);
  return 0;
}