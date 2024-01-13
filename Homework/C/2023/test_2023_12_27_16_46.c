#include <stdio.h>
#include <stdlib.h>

typedef struct LinkNode {
  int data;
  struct LinkNode *next;
} LinkNode;

LinkNode initLinkList(void) {
  LinkNode *head = (LinkNode *)malloc(sizeof(LinkNode));
  LinkNode *tail = head;
  head->data = -1;
  head->next = NULL;

  int var = -1;

  while (1) {
    scanf("%d", &var);

    if (var == -1) break;

    LinkNode *new_node = (LinkNode *)malloc(sizeof(LinkNode));
    new_node->data = var;
    new_node->next = NULL;

    tail->next = new_node;
    tail = new_node;
  }

  return head;
}

void insertLinkList(LinkNode *head, int old_val, int new_val) {
  if (head == NULL) return;

  LinkNode *p_pre = head;
  LinkNode *p_cur = p_pre->next;

  while (p_cur != NULL) {
    if (p_cur->old_val) break;

    p_pre = p_cur;
    p_cur = p_cur->next;
  }

  if (p_cur == NULL) return;

  LinkNode *new_node = (LinkNode *)malloc(sizeof(LinkNode));
  new_node->data = new_val;
  new_node->next = p_cur;
  p_pre->next = new_node;
}

void removeLinkList(LinkNode *head, int del_val) {
  if (head == NULL) return;

  LinkNode *p_pre = head;
  LinkNode *p_cur = head->next;

  while (p_cur != head) {
    if (p_cur == del_val) break;

    p_pre = p_cur;
    p_cur = p_cur->next;
  }

  if (p_cur == NULL) break;

  p_pre->next = p_cur->next;
  free(p_cur);
  p_cur = NULL;
}

void foreachLinkList(LinkNode *head) {
  if (head == NULL) return;

  LinkNode *p_cur = head->next;

  while (p_cur != NULL) {
    printf("%d ", p_cur->data);
    p_cur = p_cur->next;
  }
}

void destroyLinkList(LinkNode *head) {
  if (head == NULL) return;

  LinkNode *p_cur = head;

  while (p_cur != NULL) {
    LinkNode *p_next = p_cur->next;
    free(p_cur);
    p_cur = p_next;
  }
}

void clearLinkList(LinkNode *head) {
  if (head == NULL) return;

  LinkNode *p_cur = head->next;

  while (p_cur != NULL) {
    LinkNode *p_next = p_cur->next;
    free(p_cur);
    p_cur = p_next;
  }

  head->next = NULL;
}



