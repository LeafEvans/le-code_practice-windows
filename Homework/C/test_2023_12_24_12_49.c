#include <stdio.h>
#include <string.h>

int main(void) {
  char str1[1001] = {0};
  char str2[1001] = {0};
  int count = 0;

  scanf("%s", str1);
  scanf("%s", str2);

  char *ptr = strstr(str1, str2);
  while (ptr != NULL) {
    ++count;
    ptr = strstr(ptr + 1, str2);
  }

  printf("%d\n", count);

  return 0;
}
