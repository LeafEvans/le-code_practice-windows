#ifndef _DBLLINKLIST_H_
#define _DBLLINKLIST_H_
#include "LinkListBase.h"

template <class T>
class DblLinkList : public LinkListBase<T, DblNode<T>> {
 public:
  DblLinkList();                        // 构造函数
  ~DblLinkList();                       // 析构函数
  DblLinkList(const DblLinkList &src);  // 拷贝构造函数
  void toTail();                        // 更新当前指针
  bool toPrev(T &elem);                 // 更新当前指针

 protected:
  virtual bool link(DblNode<T> *prev_node, DblNode<T> *curr_node);  // 连接函数
};

template <class T>
DblLinkList<T>::DblLinkList() {}

template <class T>
DblLinkList<T>::~DblLinkList() {}

template <class T>
DblLinkList<T>::DblLinkList(const DblLinkList &src) {
  *this = src;  // 拷贝构造函数
}

template <class T>
bool DblLinkList<T>::link(DblNode<T> *prev_node, DblNode<T> *curr_node) {
  if (!prev_node) {  // 前一个指针查看是否为空
    return false;
  }

  prev_node->next = curr_node;  // 前一个指针的下一个是当前指针

  if (curr_node) {                // 查看当前指针
    curr_node->prev = prev_node;  // 当前指针的前一个
  }

  return true;
}

template <class T>
void DblLinkList<T>::toTail() {
  this->curr_ = this->tail_;
}

template <class T>
bool DblLinkList<T>::toPrev(T &elem) {
  if (!this->curr_) {  // 查看当前指针是否为空
    return false;
  }

  if (this->curr_->prev == this->head_) {
    return false;  // 看看前一个是不是头指针
  }

  this->curr_ = this->curr_->prev;  // 更新为前一个

  elem = this->curr_->data;  // 存储数值

  return true;
}

#endif  // _DBLLINKLIST_H_
