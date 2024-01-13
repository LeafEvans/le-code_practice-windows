#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  FILE *pf = fopen("test_12_23.txt", "r");
  if (pf == NULL) perror("fopen");
  char arr[20] = {0};
  fgets(arr, 20, pf);
  printf("%s\n", arr);
  fclose(pf);
  pf = NULL;
  return 0;
}