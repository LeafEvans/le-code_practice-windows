#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int val;
  struct Node *next;
} Node;

void swap(Node *node1, Node *node2) {
  int temp = node1->val;
  node1->val = node2->val;
  node2->val = temp;
}

Node *initList(int n) {
  Node *head = (Node *)malloc(sizeof(Node));
  Node *tail = head;
  head->val = 0;
  head->next = NULL;

  while (n--) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    scanf("%d", &(new_node->val));
    new_node->next = NULL;
    tail->next = new_node;
    tail = new_node;
  }

  return head;
}

void selectionSort(Node *head) {
  if (!head || !head->next) return;

  for (Node *curr = head; curr; curr = curr->next) {
    Node *min = curr;
    for (Node *temp = curr->next; temp; temp = temp->next) {
      if (curr->val > temp->val) swap(min, temp);
    }
  }
}

void printList(Node *head) {
  if (!head || !head->next) return;

  for (Node *curr = head->next; curr; curr = curr->next) {
    printf("%d ", curr->val);
  }
  printf("\n");
}

int main(void) {
  int n = 0;
  scanf("%d", &n);
  Node *head = initList(n);
  selectionSort(head);
  printList(head);
  return 0;
}