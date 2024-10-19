#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertionSort(char arr[], int len) {
  int i = 0;
  int j = 0;

  for (i = 1; i < len; ++i) {
    int key = arr[i];
    for (j = i - 1; j >= 0 && key < arr[j]; --j) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = key;
  }
}

int main(void) {
  char a[1000] = {0};
  char b[1000] = {0};
  char c[2000] = {0};

  FILE *fa = fopen("a.txt", "r");
  FILE *fb = fopen("b.txt", "r");
  FILE *fc = fopen("c.txt", "w");

  fgets(a, 10000, fa);
  a[strlen(a)] = '\0';
  fgets(b, 10000, fb);
  b[strlen(b)] = '\0';

  strcat(c, a);
  strcat(c, b);

  insertionSort(c, strlen(c));
  printf("%s\n", c);
  fputs(c, fc);

  fclose(fa);
  fclose(fb);
  fclose(fc);
  fa = NULL;
  fb = NULL;
  fc = NULL;

  return 0;
}