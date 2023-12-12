#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Candidate
{
  char name[10];
  int count;
};

int cmpStructByName(const void *ptr1, const void *ptr2)
{
  return strcmp(((struct Candidate *)ptr1)->name,
                ((struct Candidate *)ptr2)->name);
}

int main(void)
{
  int i = 0;
  int count_qq = 0;
  char name_election[10] = {0};
  struct Candidate successor[3];

  for (i = 0; i < 3; i++)
  {
    scanf("%s", &(successor[i].name));
    successor[i].count = 0; // 在这里初始化，以便于之后进行++操作
  }

  while (strcmp(name_election, "END") != 0)
  {
    scanf("%s", name_election);

    if (strcmp(name_election, successor[0].name) == 0)
    {
      successor[0].count++;
    }
    else if (strcmp(name_election, successor[1].name) == 0)
    {
      successor[1].count++;
    }
    else if (strcmp(name_election, successor[2].name) == 0)
    {
      successor[2].count++;
    }
    else if (strcmp(name_election, "END") != 0)
    {
      count_qq++;
    }
  }

  qsort(successor, 3, sizeof(successor[0]), cmpStructByName);

  for (i = 0; i < 3; ++i)
  {
    printf("%s:%d\n", successor[i].name, successor[i].count);
  }

  printf("%s:%d\n", "QQ", count_qq);

  return 0;
}