#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

Node *initList(void) {
  Node *head = (Node *)malloc(sizeof(Node));
  if (!head) return NULL;

  head->data = -1;
  head->next = NULL;

  int val = -1;
  Node *tail = head;

  while (1) {
    scanf("%d", &val);
    if (val == -1) break;

    Node *new_node = (Node *)malloc(sizeof(Node));

    new_node->data = val;
    new_node->next = NULL;

    tail->next = new_node;
    tail = new_node;
  }

  return head;
}

void printList(Node *head) {
  if (!head || !(head->next)) return;

  Node *curr = head->next;

  while (curr) {
    printf("%d ", curr->data);
    curr = curr->next;
  }
  printf("\n");
}

void insertNodeByValue(Node *head, int old_val, int new_val) {
  if (!head || !head->next) return;

  Node **ptr = &(head->next);

  while (*ptr && (*ptr)->data != old_val) {
    ptr = &((*ptr)->next);
  }

  if (*ptr) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) return;

    new_node->data = new_val;
    new_node->next = *ptr;
    *ptr = new_node;
  }
}

void removeNodeByValue(Node *head, int del_val) {
  if (!head || !head->next) return;

  Node **ptr = &(head->next);

  while (*ptr && (*ptr)->data != del_val) {
    ptr = &((*ptr)->next);
  }

  if (*ptr) {
    Node *temp = *ptr;
    *ptr = (*ptr)->next;
    free(temp);
  }
}

void clearList(Node *head) {
  if (!head || !head->next) return;

  Node *curr = head->next;

  while (curr) {
    Node *temp = curr->next;
    free(curr);
    curr = temp;
  }
}

void destroyList(Node *head) {
  if (!head) return;

  Node *curr = head;

  while (curr) {
    Node *temp = curr->next;
    free(curr);
    curr = temp;
  }
}

void bubbleSortList(Node *head) {
  if (!head || !head->next) return;

  Node *sorted = NULL;
  Node *unsorted = NULL;

  for (Node *curr = head->next; curr->next; curr = curr->next) {
    for (unsorted = head->next; unsorted->next != sorted;
         unsorted = unsorted->next) {
      if (unsorted->data > unsorted->next->data) {
        int temp = unsorted->data;
        unsorted->data = unsorted->next->data;
        unsorted->next->data = temp;
      }
    }
    sorted = unsorted;
  }
}

void insertionSortList(Node *head) {
  if (!head || !head->next) return;

  Node *sorted = head;
  Node *curr = head->next;
  sorted->next = NULL;

  while (curr) {
    Node **ptr = &(sorted);
    while (*ptr && (*ptr)->data < curr->data) {
      ptr = &((*ptr)->next);
    }
    Node *next = curr->next;
    curr->next = *ptr;
    *ptr = curr;
    curr = next;
  }
}

void test(void) {
  Node *head = initList();
  printList(head);
  insertionSortList(head);
  printList(head);
}

int main(void) {
  test();
  return 0;
}