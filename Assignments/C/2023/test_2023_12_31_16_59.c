#include <stdio.h>
#include <string.h>

int myStrlen(char *str) {
  char *ptr = str;
  while (*ptr) ++ptr;
  return (int)(ptr - str);
}

int myStrcmp(char *str1, char *str2) {
  while (*str1 == *str2 && *str1 && *str2) {
    ++str1;
    ++str2;
  }

  return *str1 == *str2 ? 0 : (*str1 > *str2 ? 1 : -1);
}

int main(void) {
  char str1[501] = {0};
  char str2[501] = {0};

  fgets(str1, 501, stdin);
  str1[strlen(str1) - 1] = '\0';
  fgets(str2, 501, stdin);
  str2[strlen(str2) - 1] = '\0';

  printf("%d\n", myStrcmp(str1, str2));

  return 0;
}