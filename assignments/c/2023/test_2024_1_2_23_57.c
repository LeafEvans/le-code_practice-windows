#include <ctype.h>
#include <stdio.h>
#include <string.h>

int isVaildIP(char *str) {
  int dot = 0;
  int num = 0;

  if (*str == '.') return 0;

  while (*str) {
    if (!isdigit(*str) && *str != '.') return 0;
    if (dot > 3) return 0;

    if (*str == '.') {
      ++dot;
      ++str;
    }

    while (isdigit(*str)) {
      num = num * 10 + *str - '0';
      ++str;
    }

    if (num < 0 || num > 255) {
      return 0;
    }

    num = 0;
  }

  if (!isdigit(*(str - 1))) return 0;

  if (*(str - 1) == '.') return 0;

  if (dot != 3) return 0;

  return 1;
}

int main(void) {
  int n = 0;
  scanf("%d", &n);
  while (getchar() != '\n') {
    ;
  }

  for (int i = 0; i < n; ++i) {
    char str[101] = {0};
    fgets(str, 101, stdin);
    str[strlen(str) - 1] = '\0';
    printf(isVaildIP(str) ? "yes\n" : "no\n");
  }

  return 0;
}