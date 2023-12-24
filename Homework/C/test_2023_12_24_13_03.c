#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int cmpStr(const void* e1, const void* e2) {
  return strcmp((char*)e1, (char*)e2);
}

int main(void) {
  char str[100] = {0};
  char str_arr[100][100] = {0};

  scanf("%s", str);
  int len = strlen(str);
  for (int i = 0; str[i] != 0; ++i) {
    strcpy(str_arr[i], str + i);
  }
  qsort(str_arr, len, sizeof(str_arr[0]), cmpStr);
  for (int i = 0; i < len; ++i) {
    printf("%s\n", str_arr[i]);
  }

  return 0;
}