#include <stdio.h>
#include <stdlib.h>

int main(void) {
  FILE *pf = fopen("test_12_23.txt", "r");

  if (pf == NULL) {
    perror("fopen");
    return 1;
  }

  fseek(pf, 2, SEEK_SET);
  int ch = fgetc(pf);
  printf("%c\n", ch);
  printf("%d\n", ftell(pf));
  rewind(pf);
  ch = fgetc(pf);
  printf("%c\n", ch);
  fclose(pf);
  pf = NULL;

  return 0;
}