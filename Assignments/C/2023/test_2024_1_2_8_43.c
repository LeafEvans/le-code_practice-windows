#include <stdio.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

void swap(Node *node1, Node *node2) {
  int temp = node1->data;
  node1->data = node2->data;
  node2->data = temp;
}

void selectionSort(Node *head) {
  if (!head || !head->next) return;
  Node *curr = head;
  while (curr != NULL) {
    Node *min = curr;
    Node *temp = curr->next;
    while (temp != NULL) {
      if (temp->data < min->data) {
        min = temp;
      }
      temp = temp->next;
    }
    swap(curr, min);
    curr = curr->next;
  }
}

void bubbleSort(Node *head) {
  if (!head || !head->next) return;
  Node *sorted = NULL;
  Node *curr = NULL;
  for (Node *unsorted = head; !unsorted->next; unsorted = unsorted->next) {
    for (curr = head; curr->next = sorted; curr = curr->next) {
      if (curr->data > curr->next->data) {
        swap(curr, curr->next);
      }
    }
    sorted = curr;
  }
}

void insertionSort(Node *head) {
  if (!head || !head->next) return;
  Node *sorted = head;
  Node *curr = head->next;
  sorted->next = NULL;

  while (curr) {
    Node **ptr = &sorted;
    while (*ptr && (*ptr)->data < curr->data) ++ptr;
    Node *next = curr->next;
    curr->next = *ptr;
    *ptr = curr;
    curr = curr->next;
  }
}



int main(void) { return 0; }