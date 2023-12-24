#include <stdio.h>

typedef struct Stu {
  char arr[10];
  int age;
  float score;
} Stu;

int main(void) {
  Stu s = {"zhangsan", 20, 55.5f};
  Stu tmp = {0};
  char buf[100] = {0};
  sprintf(buf, "%s %d %f", s.arr, s.age, s.score);
  printf("%s\n", buf);
  scanf("%s %d %f", tmp.arr, &(tmp.age), &(tmp.score));
  sscanf(buf, "%s %d %f", tmp.arr, &(tmp.age), &(tmp.score));
  printf(buf);
  return 0;
}