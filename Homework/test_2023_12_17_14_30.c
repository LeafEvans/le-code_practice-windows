#include <ctype.h>
#include <stdio.h>
#include <string.h>

int isValidEmail(char *email) {
  int dot = 0;
  int at = 0;
  char *ptr = email;

  if (!isalnum(*ptr) && *ptr != '-' && *ptr != '_') return 0;
  while (*ptr) {
    if (at == 0 && dot == 1) return 0;

    if (*ptr == '@') {
      if (*(ptr + 1) == '.') return 0;
      at++;
      ++ptr;
      continue;
    }

    if (*ptr == '.') {
      if (*(ptr - 1) == '@') return 0;
      dot++;
      ++ptr;
      continue;
    }

    if (!isalnum(*ptr) && *ptr != '-' && *ptr != '_') return 0;

    ++ptr;
  }

  if (*(ptr - 1) == '@' || *(ptr - 1) == '.') return 0;

  if ((at == 1 && dot == 1)) {
    return 1;
  } else {
    return 0;
  }
}

int main(void) {
  char email[101] = {0};
  fgets(email, sizeof(email), stdin);
  email[strlen(email) - 1] = '\0';
  printf(isValidEmail(email) ? "yes\n" : "no\n");
  return 0;
}