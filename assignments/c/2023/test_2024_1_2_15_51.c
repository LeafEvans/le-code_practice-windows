#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  int digit = 0;
  int upper = 0;
  int lower = 0;
  int other = 0;
  char str[1001] = {0};

  fgets(str, 1001, stdin);
  str[strlen(str) - 1] = '\0';

  for (int i = 0; str[i]; ++i) {
    if (isdigit(str[i])) {
      digit++;
    } else if (isupper(str[i])) {
      upper++;
    } else if (islower(str[i])) {
      lower++;
    } else {
      other++;
    }
  }

  printf("%d %d %d %d\n", digit, upper, lower, other);

  return 0;
}