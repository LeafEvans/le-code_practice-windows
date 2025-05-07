#include <stdio.h>
#include <stdlib.h>

typedef struct Stu {
  char name[21];
  float score;
} Stu;

typedef struct Node {
  Stu stu;
  struct Node *next;
} Node;

void swapStu(Node *a, Node *b) {
  Stu temp = a->stu;
  a->stu = b->stu;
  b->stu = temp;
}

Node *initLinkList(void) {
  Node *head = (Node *)malloc(sizeof(Node));
  head->next = NULL;
  Node *tail = head;

  printf("请输入学生的数量:>\n");

  int count = 0;
  scanf("%d", &count);

  for (int i = 0; i < count; ++i) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->next = NULL;

    printf("请输入第%d个学生的姓名、成绩:>\n", i + 1);
    scanf("%s %f", new_node->stu.name, &(new_node->stu.score));

    tail->next = new_node;
    tail = new_node;
  }

  return head;
}

void printLink(Node *head) {
  if (head == NULL) return;

  Node *p_cur = head->next;

  while (p_cur != NULL) {
    printf("姓名: %s, 分数 %.1f\n", p_cur->stu.name, p_cur->stu.score);
    p_cur = p_cur->next;
  }
}

void bubbleSort(Node *head) {
  if (head == NULL) return;

  for (Node *p_round = head->next; p_round->next != NULL;
       p_round = p_round->next) {
    for (Node *p_cur = p_round; p_cur->next != NULL; p_cur = p_cur->next) {
      if (p_cur->stu.score > p_cur->next->stu.score) {
        swapStu(p_cur, p_cur->next);
      }
    }
  }
}