#include <stdio.h>
#include <stdlib.h>

typedef struct DataNode {
  int data;
  struct DataNode *next;
} DataNode;

void removeByLocLinkList(DataNode *head) {
  if (head == NULL || head->next == NULL || head->next->next == NULL) return;

  DataNode *p_pre = NULL;
  DataNode *p_cur = head->next;

  while (p_cur->next->next != NULL) {
    p_pre = p_cur;
    p_cur = p_cur->next;
  }

  p_pre->next = p_cur->next;
  free(p_cur);
  p_cur = NULL;
}

void foreachLinkList(DataNode *head) {
  if (head == NULL) return;

  DataNode *p_cur = head->next;

  while (p_cur != NULL) {
    printf("%d ", p_cur->data);
    p_cur = p_cur->next;
  }
}

DataNode *initLinkList(void) {
  DataNode *head = (DataNode *)malloc(sizeof(DataNode));
  DataNode *tail = head;
  head->data = -1;
  head->next = NULL;

  int val = -1;

  while (1) {
    scanf("%d", &val);
    if (val == -1) break;

    DataNode *new_node = (DataNode *)malloc(sizeof(DataNode));

    tail->next = new_node;
    tail = new_node;
  }

  return head;
}


void test(void) {
  DataNode *head = initLinkList();
  foreachLinkList(head);
  removeByLocLinkList(head);
}

int main(void) {
  test();
  return 0;
}