#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stu {
  char name[21];
  int sno;
  int chinese;
  int english;
  int math;
  int sum;
  struct Stu *next;
} Stu;

Stu *initLink(void) {
  Stu *head = (Stu *)malloc(sizeof(Stu));
  head->next = NULL;
  return head;
}

Stu *insertLink(Stu *head) {
  if (head == NULL) return NULL;

  char str[20] = {0};

  while (1) {
    scanf("%s", str);
    if (strcmp(str, "exit") == 0) break;

    Stu *p_pre = head;
    Stu *p_cur = head->next;
    Stu *new_node = (Stu *)malloc(sizeof(Stu));

    strcpy(new_node->name, str);
    scanf("%d %d %d %d", &(new_node->sno), &(new_node->chinese),
          &(new_node->english), &(new_node->math));
    new_node->sum = new_node->chinese + new_node->english + new_node->math;

    while (p_cur != NULL && (new_node->sum < p_cur->sum)) {
      p_pre = p_cur;
      p_cur = p_cur->next;
    }

    if (p_cur != NULL && (new_node->sum == p_cur->sum)) {
      while (p_cur != NULL && strcmp(new_node->name, p_cur->name) > 0) {
        p_pre = p_cur;
        p_cur = p_cur->next;
      }
    }

    p_pre->next = new_node;
    new_node->next = p_cur;
  }

  return head;
}

void foreachLink(Stu *head) {
  if (head == NULL) return;

  Stu *p_cur = head->next;

  printf("[");
  while (p_cur != NULL) {
    if (p_cur->next != NULL) {
      printf("{name:%s,sum:%d,sno:%d},\n", p_cur->name, p_cur->sum, p_cur->sno);
    } else {
      printf("{name:%s,sum:%d,sno:%d}]\n", p_cur->name, p_cur->sum, p_cur->sno);
    }
    p_cur = p_cur->next;
  }
}

void test(void) {
  Stu *head = initLink();
  insertLink(head);
  foreachLink(head);
}

int main(void) {
  test();
  return 0;
}