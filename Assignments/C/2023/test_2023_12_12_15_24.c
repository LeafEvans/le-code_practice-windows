#include <stdio.h>
#include <stdlib.h>

struct Student {
  char name[20];
  int id;
  int math;
  int chinese;
  int sum;
};

int cmpStruct(const void *ptr1, const void *ptr2) {
  struct Student *p1 = (struct Student *)ptr1;
  struct Student *p2 = (struct Student *)ptr2;

  if (p1->sum == p2->sum) {
    return p1->id > p2->id ? 1 : -1;
  } else {
    return p1->sum > p2->sum ? -1 : 1;
  }
}

int main(void) {
  int i = 0;
  int n = 0;
  struct Student stu[10];

  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%s %d %d %d", stu[i].name, &stu[i].id, &stu[i].math,
          &stu[i].chinese);
    stu[i].sum = stu[i].chinese + stu[i].math;
  }

  qsort(stu, n, sizeof(stu[0]), cmpStruct);

  for (i = 0; i < n; i++) {
    printf("%s %d\n", stu[i].name, stu[i].sum);
  }

  return 0;
}