#include <assert.h>
#include <stdio.h>
#include <string.h>

void swap(char *buf1, char *buf2, int width) {
  for (int i = 0; i < width; i++) {
    char tmp = *buf1;
    *buf1 = *buf2;
    *buf2 = tmp;
    ++buf1;
    ++buf2;
  }
}

void bubbleSort(void *base, int sz, int width,
                int cmp(const void *, const void *)) {
  for (int i = 0; i < sz - 1; ++i) {
    for (int j = 0; j < sz - 1 - i; j++) {
      if (cmp((char *)base + j * width, (char *)base + (j + 1) * width)) {
        swap((char *)base + j * width, (char *)base + (j + 1) * width, width);
      }
    }
  }
}

int main(void) {
  char str1[20] = "hello ";
  char str2[] = "world";
  strncpy(str1, str2, 3);
  printf("%s\n", str1);
  return 0;
}