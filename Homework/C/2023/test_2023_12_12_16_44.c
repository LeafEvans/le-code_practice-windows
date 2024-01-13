#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  int i = 0;
  char str[10001] = {0};

  while (1) {
    int digit = 0;
    int up_alpha = 0;
    int low_alpha = 0;
    int other = 0;

    fgets(str, 10001, stdin);
    str[strlen(str) - 1] = '\0';

    if (strcmp(str, "exit") == 0) {
      printf("End Of Input\n");
      break;
    }

    for (i = 0; str[i] != '\0'; i++) {
      if (isupper(str[i])) {
        up_alpha++;
      } else if (islower(str[i])) {
        low_alpha++;
      } else if (isdigit(str[i])) {
        digit++;
      } else {
        other++;
      }
    }

    printf("%d,%d,%d,%d,\n", digit, up_alpha, low_alpha, other);
  }

  return 0;
}