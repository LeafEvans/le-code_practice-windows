#include <stdio.h>
#include <string.h>

int main(void) {
  char score[5] = {0};
  scanf("%s", score);

  int len = strlen(score);
 
  printf("%d\n", len);
  for (int i = 0; i < len; ++i) printf("%c ", score[i]);
  printf("\n");
  for (int i = len - 1; i >= 0; --i) printf("%c ", score[i]);
  printf("\n");

  return 0;
}
