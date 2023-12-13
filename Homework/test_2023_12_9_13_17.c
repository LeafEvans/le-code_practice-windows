#include <stdio.h>
#include <string.h>

int myStrncmp(const char *str1, const char *str2, size_t num) {
  while (*str1 != '\0' && *str2 != '\0' && num) {
    if (*str1 != *str2) {
      return (*str1 > *str2) ? 1 : -1;
    }
    str1++;
    str2++;
    num--;
  }

  return 0;
}

int main(void) {
  char arr1[] = "abcdef";
  char arr2[] = "abc";

  int ret = strncmp(arr1, arr2, 4);
  printf("%d\n", ret);

  return 0;
}