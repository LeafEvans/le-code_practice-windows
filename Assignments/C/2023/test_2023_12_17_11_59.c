#include <stdio.h>
#include <string.h>
#include <ctype.h>

void crypto(char *str) {
  while (*str) {
    if (isupper(*str)) {
      *str = (*str + 30 - 'A') % 26 + 'A';
    } else if (islower(*str)) {
      *str = (*str + 30 - 'a') % 26 + 'a';
    }
    ++str;
  }
}

int main(void) {
  char str[101] = {0};

  fgets(str, 101, stdin);
  str[strlen(str) - 1] = '\0';
  crypto(str);
  printf("%s\n", str);

  return 0;
}