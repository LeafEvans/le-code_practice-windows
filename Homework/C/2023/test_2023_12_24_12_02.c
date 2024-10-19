#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  int i = 0;
  int j = 0;
  int n = 0;
  char str[100][100] = {0};

  while (1) {
    fgets(str[i], sizeof(str[0]), stdin);
    if (strcmp(str[i], "end of input\n") == 0) break;  // 有意思，\n 不是终止符标志
    ++i;
    ++n;
  }

  for (i = 0; i < n; ++i) {
    for (j = 0; str[i][j] != '\0'; ++j) {
      if (islower(str[i][j])) {
        putchar(toupper(str[i][j]));
      } else {
        putchar(str[i][j]);
      }
    }
  }

  return 0;
}