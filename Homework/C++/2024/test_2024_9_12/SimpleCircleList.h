#ifndef _SIMPLECIRCLELIST_H_
#define _SIMPLECIRCLELIST_H_
#include "CircleListBase.h"

template<class T>
class SimpleCircleList : public CircleListBase<T, Node<T>> {
 public:
  SimpleCircleList();
  ~SimpleCircleList();
  SimpleCircleList(const SimpleCircleList &src);

 protected:
  virtual bool link(Node<T> *prev_node, Node<T> *curr_node);
};

template<class T>
SimpleCircleList<T>::SimpleCircleList() {
  this->linkTailToHead();
}

template<class T>
SimpleCircleList<T>::~SimpleCircleList() {}

template<class T>
SimpleCircleList<T>::SimpleCircleList(const SimpleCircleList &src) {
  *this = src;
  this->linkTailToHead();
}

template<class T>
bool SimpleCircleList<T>::link(Node<T> *prev_node, Node<T> *curr_node) {
  if (!prev_node) {  // 前一个必须不为空
    return false;
  }
  prev_node->next = curr_node;
  return true;
}

#endif // _SIMPLECIRCLELIST_H_
