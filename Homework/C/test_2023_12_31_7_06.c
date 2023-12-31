#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

Node *createList(void) {
  Node *head = (Node *)malloc(sizeof(Node));
  if (head == NULL) return NULL;
  head->next = NULL;
  return head;
}

void insertNode(Node *head, int data) {
  if (head == NULL) return;

  Node *new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL) return;
  new_node->data = data;
  new_node->next = NULL;

  Node *curr = head->next;
  while (curr->next != NULL) curr = curr->next;
  curr->next = new_node;
}

void insertionSortLinkList(Node *head) {
  if (!head || !head->next) return;  // 空链表或只有一个元素的链表，无需排序
  
  Node *sorted = head;  // 以第一个节点为已排序部分的起点
  Node *curr = head->next;
  sorted->next = NULL;  // 已排序链表的尾部

  while (curr) {
    Node **ptr = &sorted;
    while (*ptr && (*ptr)->data < curr->data) {
      ptr = &((*ptr)->next);
    }
    Node *next = curr->next;  // 保存下一个待处理的节点
    curr->next = *ptr;        // 将当前节点插入已排序链表
    *ptr = curr;
    curr = next;  // 移动到下一个节点
  }
}

int main(void) { return 0; }