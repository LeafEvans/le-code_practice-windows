#include <stdio.h>

typedef struct Stu {
  char arr[10];
  int age;
  float score;
} Stu;

int main(void) {
  Stu s = {"zhangsan", 25, 50.5f};
  FILE* pf = fopen("test_12_23.txt", "r");
  if (pf == NULL) {
    perror("fopen");
    return 1;
  }
  fscanf(pf, "%s %d %f", s.arr, &(s.age), &(s.score));
  fprintf(stdout, "%s %d %f\n", s.arr, s.age, s.score);
  fclose(pf);
  return 0;
}