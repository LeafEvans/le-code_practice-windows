#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) { return (*(char *)a - *(char *)b); }

int main() {
  FILE *fileA, *fileB, *fileC;
  char strA[100], strB[100], sortedStr[200];

  fileA = fopen("C:\\a.txt", "r");
  fileB = fopen("C:\\b.txt", "r");

  if (fileA == NULL || fileB == NULL) {
    printf("无法打开文件\n");
    return 1;
  }

  fgets(strA, sizeof(strA), fileA);
  fgets(strB, sizeof(strB), fileB);

  fclose(fileA);
  fclose(fileB);

  strcpy(sortedStr, strA);
  strcat(sortedStr, strB);

  qsort(sortedStr, strlen(sortedStr), sizeof(char), compare);

  fileC = fopen("C:\\c.txt", "w");

  if (fileC == NULL) {
    printf("无法创建文件\n");
    return 1;
  }

  fputs(sortedStr, fileC);

  fclose(fileC);

  printf("%s\n", sortedStr);

  return 0;
}
