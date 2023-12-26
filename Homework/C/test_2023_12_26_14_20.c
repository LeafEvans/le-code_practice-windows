#include <stdio.h>
#include <stdlib.h>

// 定义节点数据结构
typedef struct LinkNode {
  int data;
  struct LinkNode *next;
} LinkNode;

// 在值为old_val的位置插入一个新的数据new_val，old_val在原位置的后面
void insertByValueLinkList(LinkNode *header, int old_val, int new_val) {
  if (NULL == header) return;

  LinkNode *p_pre = header;
  LinkNode *p_cur = p_pre->next;

  while (p_cur != NULL) {
    if (p_cur->data == old_val) break;

    p_pre = p_cur;
    p_cur = p_pre->next;
  }

  if (p_cur == NULL)
    return;  // p_cur为空指针，说明链表中不存在值为old_val的节点

  // 先创建一个新结点
  LinkNode *new_node = (LinkNode *)malloc(sizeof(LinkNode));
  new_node->data = new_val;
  new_node->next = p_cur;  // 插入新节点
  p_pre->next = new_node;
}

// 删除值为val的结点
void removeByValueLinkList(LinkNode *header, int del_val) {
  if (NULL == header) return;

  LinkNode *p_pre = header;
  LinkNode *p_cur = p_pre->next;

  while (p_cur != NULL) {
    if (p_cur->data == del_val) {
      break;
    }
    p_pre = p_cur;
    p_cur = p_pre->next;
  }

  if (NULL == p_cur) return;

  p_pre->next = p_cur->next;  // 重新建立删除节点的前驱和后继节点关系
  free(p_cur);                // 释放删除节点内存
  p_cur = NULL;
}
// 遍历链表
void foreachLinkList(LinkNode *header) {
  if (NULL == header) return;

  LinkNode *p_cur = header->next;  // 定义一个辅助指针帮助遍历

  while (p_cur != NULL) {  // 当节点指向下一个节点的指针不为空时
    printf("%d ", p_cur->data);  // 打印出来
    p_cur = p_cur->next;         // 更新辅助指针的值
  }
}

// 销毁链表
void destroyLinkList(LinkNode *header) {
  if (NULL == header) return;

  LinkNode *p_cur = header;

  while (p_cur != NULL) {
    LinkNode *p_next = p_cur->next;  // 先保存下当前节点的下一个节点地址
    free(p_cur);                     // 释放当前节点内存
    p_cur = p_next;                  // 指针向后移动
  }
}

// 清空
void clearLinkList(LinkNode *header) {
  if (NULL == header) return;

  LinkNode *p_cur = header->next;

  while (p_cur != NULL) {
    LinkNode *p_next = p_cur->next;
    free(p_cur);
    p_cur = p_next;
  }

  header->next = NULL;
}

// 初始化链表
LinkNode *initLinkList(void) {
  LinkNode *header = (LinkNode *)malloc(sizeof(LinkNode));  // 创建头节点
  LinkNode *p_rear = header;  // 创建尾部节点，一开始它是头部节点的地址
  header->data = -1;    // 第一个数据随便定义，因为不用
  header->next = NULL;  // 下一个为空

  int val = -1;  // 定义数值域的判断，并进行循环的判断

  while (1) {
    printf("请输入插入的数据:>\n");
    scanf("%d", &val);
    if (val == -1) break;  // 当输入为 -1 时跳出

    // 先创建新节点
    LinkNode *new_node = malloc(sizeof(LinkNode));  // 创建一个新节点
    new_node->data = val;   // 新节点的数值即为刚才的数值
    new_node->next = NULL;  // 新节点的下一个指向空

    // 新节点插入链表中，尾插
    p_rear->next = new_node;  // 将当前尾部指针指向的节点的指针指向新的节点
    // 更新尾部指针指向
    p_rear = new_node;  // 更新尾部节点
  }

  return header;
}

void test(void) {
  LinkNode *header = initLinkList();
  foreachLinkList(header);
  insertByValueLinkList(header, 300, 666);
  printf("\n");
  clearLinkList(header);
  1 foreachLinkList(header);
}

int main(void) {
  test();
  return 0;
}
