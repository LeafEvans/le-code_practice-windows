#ifndef _LINKLISTBASE_H_
#define _LINKLISTBASE_H_

#include "ListBase.h"
#include "Node.h"

template <class T, class NodeType>
class LinkListBase : public ListBase<T> {
 public:
  LinkListBase();
  virtual ~LinkListBase();

  virtual int length() const;                    // 获取链表长度
  virtual bool isEmpty() const;                  // 判断链表是否为空
  void clear();                                  // 清空链表
  virtual bool getElem(int pos, T &elem) const;  // 获取指定位置的元素
  virtual bool setElem(int pos, const T &elem);  // 设置指定位置的元素
  virtual bool delElem(int pos, T &elem);
  virtual bool insert(int pos, const T &elem);            // 插入元素
  virtual void traverse(bool (*visit)(const T &)) const;  // 遍历链表
  virtual int append(const T &elem);  // 添加元素到尾部
  // 重载赋值操作符
  virtual LinkListBase &operator=(const LinkListBase<T, NodeType> &src);
  virtual void toHead();          // 移动当前节点指针到头节点
  virtual bool toNext(T &elem);   // 移动到下一个节点并获取数据
  virtual bool delCurr(T &elem);  // 删除当前节点

 protected:
  virtual bool link(NodeType *prev, NodeType *next) = 0;  // 连接两个节点
  virtual NodeType *find(int pos, NodeType *&prev) const;  // 查找指定位置的节点
  virtual NodeType *first() const;           // 获取第一个节点
  virtual bool isEnd(NodeType *node) const;  // 判断是否为链表末尾

  NodeType *head_;  // 头节点
  NodeType *tail_;  // 尾节点
  NodeType *curr_;  // 当前节点

  int count_;             // 节点数量
  bool special_destroy_;  // 是否为特殊销毁
};

// 默认构造函数
template <class T, class NodeType>
LinkListBase<T, NodeType>::LinkListBase() {
  special_destroy_ = false;  // 特殊销毁状态
  head_ = new NodeType;      // 申请头节点空间
  count_ = 0;                // 计数为 0
  tail_ = head_;
  curr_ = head_;
}

template <class T, class NodeType>
LinkListBase<T, NodeType> &LinkListBase<T, NodeType>::operator=(
    const LinkListBase<T, NodeType> &src) {
  clear();  // 清空原有链表

  special_destroy_ = false;  // 不被特殊销毁

  NodeType *src_node = src.first();  // 第一个有效节点
  NodeType *pre_node = head_;        // 原有链表头节点

  while (!src.isEnd(src_node)) {        // 遍历整个源链表
    NodeType *new_node = new NodeType;  // 新的节点
    new_node->data = src_node->data;  // 新节点的数据与源节点的数据相同
    link(pre_node, new_node);         // 将新节点链接到前一个结点上
    src_node = src_node->next;        // 更新源结点
    pre_node = new_node;              // 前驱结点更新
    ++count_;                         // 结点数量增加
  }

  return *this;
}

template <class T, class NodeType>
LinkListBase<T, NodeType>::~LinkListBase() {
  if (!special_destroy_) {
    clear();  // 清空链表
    if (head_) {
      delete head_;     // 释放头结点的区域
      head_ = nullptr;  // 将头结点置为空
    }
  }
}

template <class T, class NodeType>
int LinkListBase<T, NodeType>::length() const {
  return count_;
}

template <class T, class NodeType>
NodeType *LinkListBase<T, NodeType>::first() const {
  return head_->next;
}

template <class T, class NodeType>
bool LinkListBase<T, NodeType>::isEnd(NodeType *node) const {
  if (!node || node == head_) {  // 为空或者头结点
    return true;
  }
  return false;
}

template <class T, class NodeType>
void LinkListBase<T, NodeType>::toHead() {
  curr_ = head_;
}

template <class T, class NodeType>
bool LinkListBase<T, NodeType>::toNext(T &elem) {
  if (!curr_ || !curr_->next) {  // 如果该节点或下一个节点为空
    return false;
  }
  curr_ = curr_->next;
  elem = curr_->data;
  return true;
}

template <class T, class NodeType>
bool LinkListBase<T, NodeType>::delCurr(T &elem) {
  if (!curr_ ||
      curr_ == head_) {  // 如果该节点为空或当前节点为头节点（循环链表）
    return false;
  }

  NodeType *next_node = curr_->next;  // 下一个节点
  NodeType *prev_node = head_;        // 寻找前一个节点
  NodeType *curr_node = first();      // 第一个有效节点
  bool found_prev = false;            // 是否找到前一个节点

  while (!isEnd(curr_node)) {  // 如果不是终点
    if (curr_node == curr_) {  // 如果当前节点已经是目标节点
      found_prev = true;       // 定义为真
      break;                   // 退出
    }
    curr_node = curr_node->next;  // 寻找下一个节点
    prev_node = prev_node->next;  // 前一个节点更新
  }

  if (!found_prev) {  // 找不到
    return false;     // 寻找失败
  }

  link(prev_node, curr_node->next);  // 进行新的连接
  elem = curr_node->data;            // 将删除点的数据保存

  if (curr_node == tail_) {  // 如果当前节点是末尾节点
    tail_ = prev_node;       // 更新末尾节点为前一个节点
  }

  curr_ = prev_node;  // 当前节点更新为前一个节点
  delete curr_node;   // 释放对应的区域
  --count_;           // 节点数量减少
  return true;
}

template <class T, class NodeType>
void LinkListBase<T, NodeType>::clear() {
  if (!head_) {  // 如果头节点为空
    return;
  }

  NodeType *node = first();  // 遍历节点

  while (!isEnd(node)) {  // 不是在末尾
    // 下一个节点
    NodeType *next_node = node->next;
    delete node;       // 释放该节点的空间
    node = next_node;  // 下一个节点
  }
  head_->clearLink();  // 将头节点的 next 置为空
  tail_ = head_;
  curr_ = head_;
  count_ = 0;
}

template <class T, class NodeType>
NodeType *LinkListBase<T, NodeType>::find(int pos, NodeType *&prev_node) const {
  if (pos < 0) {  // 不合理的位置
    return nullptr;
  }

  NodeType *node = first();  // 第一个有效节点
  prev_node = head_;         // 前一个结点

  for (int i = 0; !isEnd(node); ++i) {
    if (i == pos) {  // 如果是指定的
      break;         // 退出
    }
    prev_node = node;   // 将前一个赋值为 node
    node = node->next;  // 更新节点
  }

  return node;  // 返回找到的
}

template <class T, class NodeType>
bool LinkListBase<T, NodeType>::setElem(int pos, const T &elem) {
  NodeType *prev_node;  // 前一个
  NodeType *node = find(pos, prev_node);
  if (!node) {  // 异常
    return false;
  }
  node->data = elem;  // 存储指定数据
  return true;
}

template <class T, class NodeType>
bool LinkListBase<T, NodeType>::getElem(int pos, T &elem) const {
  NodeType *prev_node;  // 前一个
  NodeType *node = find(pos, prev_node);
  if (!node) {
    return false;
  }
  elem = node->data;  // 存储指定元素
  return true;
}

template <class T, class NodeType>
bool LinkListBase<T, NodeType>::delElem(int pos, T &elem) {
  NodeType *prev_node;
  NodeType *node = find(pos, prev_node);

  if (!node) {
    return false;
  }

  link(prev_node, node->next);  // 连接起来
  elem = node->data;            // 存储指定元素

  if (node == tail_) {  // 如果被删元素为末尾元素
    tail_ = prev_node;
  }

  curr_ = prev_node;  // 设置当前元素
  delete node;        // 释放指定空间
  --count_;           // 减少元素数量
  return true;
}

template <class T, class NodeType>
bool LinkListBase<T, NodeType>::insert(int pos, const T &elem) {
  NodeType *prev_node;
  NodeType *node = find(pos, prev_node);

  if (!node) {
    if (pos == count_) {
      prev_node = tail_;  // 末尾元素
    } else {
      false;
    }
  }

  NodeType *new_node = new NodeType;  // 新节点
  new_node->data = elem;              // 更新内部数据部分
  link(prev_node, new_node);
  link(new_node, node);  // 进行连接操作

  if (pos == count_) {
    tail_ = new_node;  // 如果是末尾
  }

  curr_ = new_node;  // 更新当前元素
  ++count_;
  return true;
}

template <class T, class NodeType>
void LinkListBase<T, NodeType>::traverse(bool (*visit)(const T &)) const {
  if (!visit) {  // 判断指针是否有效
    return;
  }

  NodeType *node = first();  // 第一个有效节点
  while (!isEnd(node)) {     // 遍历线性表
    if (!(*visit)(node->data)) {
      break;
    }
    node = node->next;  // 指向下一个节点
  }
}

template <class T, class NodeType>
bool LinkListBase<T, NodeType>::isEmpty() const {
  if (head_->next) {
    return false;
  }
  return true;
}

template <class T, class NodeType>
int LinkListBase<T, NodeType>::append(const T &elem) {
  NodeType *new_node = new NodeType;
  new_node->data = elem;
  link(tail_, new_node);
  tail_ = new_node;
  curr_ = new_node;
  return count_++;
}

#endif  // _LINKLISTBASE_H_
