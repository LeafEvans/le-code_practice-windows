#ifndef _DBLCIRCLELIST_H_
#define _DBLCIRCLELIST_H_
#include "CircleListBase.h"

template<class T>
class DblCircleList : public CircleListBase<T, DblNode<T>> {
 public:
  DblCircleList();
  ~DblCircleList();
  DblCircleList(const DblCircleList &src);
  void toTail();
  bool toPrev(T &elem);
  bool reverse();

 protected:
  virtual bool link(DblNode<T> *prev_node, DblNode<T> *curr_node);
};

template<class T>
DblCircleList<T>::DblCircleList() {
  this->linkTailToHead();
}

template<class T>
DblCircleList<T>::~DblCircleList() {}

template<class T>
DblCircleList<T>::DblCircleList(const DblCircleList<T> &src) {
  *this = src;
  this->linkTailToHead();
}

template<class T>
void DblCircleList<T>::toTail() {
  this->curr_ = this->tail_;
  this->linkTailToHead();
}

template<class T>
bool DblCircleList<T>::toPrev(T &elem) {
  if (!this->curr_) {
    return false;
  }

  if (this->curr_->prev == this->head_) {
    this->curr_ = this->curr_->prev;  // 先往前一次到头节点
  }

  this->curr_ = this->curr_->prev;

  elem = this->curr_->data;

  return true;
}

template<class T>
bool DblCircleList<T>::reverse() {
  if (this->isEmpty()) {
    return false;  // 指针指向同一个
  }

  DblNode<T> *curr = this->first();  // 第一个有效节点
  DblNode<T> *prev = this->tail_;    // 之前的

  do {
    DblNode<T> *next = curr->next;  // 先保存下一个节点的数据
    curr->prev = curr->next;  // 更换当前节点
    curr->next = prev;
    prev = curr;
    curr = next;
  } while (curr != this->head_);  // 将头节点的也进行调转

  this->tail_ = prev;
  this->linkTailToHead();

  return true;
}

#endif // _DBLCIRCLELIST_H_
