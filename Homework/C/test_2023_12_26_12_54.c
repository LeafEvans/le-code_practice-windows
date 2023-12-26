#include <stdio.h>

typedef struct LinkNode {
  int data;
  struct LinkNode *next;
} LinkNode;

void test(void) {
  LinkNode node1 = {10, NULL};
  LinkNode node2 = {20, NULL};
  LinkNode node3 = {30, NULL};
  LinkNode node4 = {40, NULL};
  LinkNode node5 = {50, NULL};
  LinkNode node6 = {60, NULL};

  node1.next = &node2;
  node2.next = &node3;
  node3.next = &node4;
  node4.next = &node5;
  node5.next = &node6;
  // 如何遍历链表？
  // 先定义一个辅助指针变量
  LinkNode *p_cur = &node1;  // 先指向头节点

  while (p_cur != NULL) {  // 当指向的不是空指针时，继续循环
    printf("%d ", p_cur->data);
    p_cur = p_cur->next;
  }
}

int main(void) {
  test();
  return 0;
}