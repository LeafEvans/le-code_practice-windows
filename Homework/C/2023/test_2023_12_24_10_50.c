#include <stdio.h>
#include <stdlib.h>

typedef struct Stu {
  char name[20];
  int score;
} Stu;

int main(void) {
  FILE* pf = fopen("info.dat", "wb");
  if (pf == NULL) {
    perror("fopen:");
    return 1;
  }

  int n = 0;
  scanf("%d", &n);

  Stu* s = (Stu*)malloc(sizeof(Stu) * n);
  Stu* t = (Stu*)malloc(sizeof(Stu) * n);

  if (s == NULL || t == NULL) {
    perror("malloc");
    return 1;
  }

  for (int i = 0; i < n; ++i) {
    scanf("%s %d", s[i].name, &(s[i].score));
    fwrite(&s[i], sizeof(Stu), 1, pf);
  }

  fclose(pf);
  pf = NULL;

  pf = fopen("info.dat", "rb");
  if (pf == NULL) {
    perror("fopen:");
    return 1;
  }

  int m = 0;
  scanf("%d", &m);

  if (m > n) {
    printf("invalid number\n");
    return 0;
  }

  for (int i = 0; i < n; ++i) fread(&t[i], sizeof(Stu), 1, pf);
  printf("%s %d", t[m - 1].name, t[m - 1].score);

  free(s);
  free(t);
  s = NULL;
  t = NULL;

  fclose(pf);
  pf = NULL;

  return 0;
}