#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  FILE *pf = fopen("file.txt", "w");

  if (pf == NULL) {
    perror("fopen");
    return 1;
  }

  char text[1000001] = {0};

  while (1) {
    fgets(text, 1000001, stdin);
    if (strcmp(text, "end of input\n") == 0) break;
    fputs(text, pf);
  }

  fclose(pf);
  pf = NULL;

  pf = fopen("file.txt", "r");

  int ch = 0;

  while ((ch = fgetc(pf)) != EOF) {
    if (islower(ch)) ch = toupper(ch);
    putchar(ch);
  }

  fclose(pf);
  pf = NULL;

  return 0;
}