#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

Node *initLinkList(void) {
  Node *head = (Node *)malloc(sizeof(Node));
  Node *tail = head;
  head->data = -1;
  head->next = NULL;

  int val = -1;

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

void bubbleSortLinkList(Node *head) {
  if (head == NULL || head->next == NULL) return;

  Node *sorted = NULL;  // 已排序部分的头部节点指针
  Node *curr = NULL;    // 当前节点指针

  // 外层循环，控制排序轮次
  for (Node *unsorted = head->next; unsorted->next != NULL;
       unsorted = unsorted->next) {
    // 内层循环，遍历未排序部分的节点
    for (curr = head->next; curr->next != sorted; curr = curr->next) {
      // 比较相邻节点的数据元素大小，进行交换
      if (curr->data > curr->next->data) {
        int temp = curr->data;
        curr->data = curr->next->data;
        curr->next->data = temp;
      }
    }
    sorted = curr;  // 将当前节点指针赋值给 sorted
  }
}

void insertionSortLinkList(Node *head) {
  if (!head || !head->next) return;
  // 空链表和一个元素的链表无需排序
  Node *sorted = head;      // 从头节点开始排序
  Node *curr = head->next;  // 遍历整个所用的指针
  sorted->next = NULL;      // 对原链表进行操作，初始化一个链表

  while (curr) {
    Node **ptr = &sorted;  // 定义一个二级指针来寻找插入的位置
    while (*ptr && (*ptr)->data < curr->data) {
      ptr = &((*ptr)->next);  // 当该位置不为空指针就继续
    }
    Node *next = curr->next;  // 找到插入点
    curr->next = *ptr;        // 将插入的元素的下一个元素改为*ptr
    *ptr = curr;              // 将*ptr前一个节点的next改为NULL
    curr = next;              // 继续遍历
  }
}

void printLinkList(Node *head) {
  if (head == NULL) return;

  Node *current = head->next;

  while (current != NULL) {
    printf("%d ", current->data);
    current = current->next;
  }
  printf("\n");
}

void test(void) {
  Node *head = initLinkList();
  printLinkList(head);
  bubbleSortLinkList(head);
  printLinkList(head);
}

int main(void) {
  test();
  return 0;
}
