#ifndef _SIMPLELINKLIST_H_
#define _SIMPLELINKLIST_H_
#include "LinkListBase.h"

template<class T>
class SimpleLinkList : public LinkListBase<T, Node<T>> {
 public:
  SimpleLinkList();
  ~SimpleLinkList();
  SimpleLinkList(const SimpleLinkList &src);

 protected:
  virtual bool link(Node<T> *prev_node, Node<T> *curr_node);
};

template<class T>
SimpleLinkList<T>::SimpleLinkList() {}

template<class T>
SimpleLinkList<T>::SimpleLinkList(const SimpleLinkList &src) {
  *this = src;
}

template<class T>
SimpleLinkList<T>::~SimpleLinkList() {}

template<class T>
bool SimpleLinkList<T>::link(Node<T> *prev_node,
                             Node<T> *curr_node) {
  if (!prev_node) {
    return false;
  }

  prev_node->next = curr_node;

  return true;
}

#endif // _SIMPLELINKLIST_H_
