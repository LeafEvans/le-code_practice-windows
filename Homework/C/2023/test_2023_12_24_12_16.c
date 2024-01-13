#include <stdio.h>
#include <stdlib.h>

typedef struct Stu {
  char name[20];
  int score;
} Stu;

int main(void) {
  int n = 0;
  int m = 0;
  scanf("%d", &n);

  Stu *s = (Stu *)malloc(sizeof(Stu) * n);

  for (int i = 0; i < n; ++i) {
    scanf("%s %d", s[i].name, &(s[i].score));
  }

  scanf("%d", &m);

  if (m > n) {
    printf("invalid number\n");
    return 0;
  }
  printf("%s %d\n", s[m - 1].name, s[m - 1].score);

  return 0;
}