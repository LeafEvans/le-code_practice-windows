#include <stdio.h>

typedef struct Stu {
  char arr[10];
  int age;
  float score;
} Stu;

int main(void) {
  Stu s = {0};
  FILE* pf = fopen("test_12_23.txt", "rb");
  if (pf == NULL) {
    perror("fopen");
    return 1;
  }
  fwrite(&s, sizeof(Stu), 1, pf);
  fclose(pf);
  pf = NULL;
  return 0;
}