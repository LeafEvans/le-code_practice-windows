#ifndef _SIMPLE_LK_LIST_H_
#define _SIMPLE_LK_LIST_H_
#include "LinkListBase.h"

template <class ElemType>
class SimpleLkList : public LinkListBase<ElemType, Node<ElemType>> {
 public:
  SimpleLkList();
  ~SimpleLkList();
  SimpleLkList(const SimpleLkList& sllSrc);

 protected:
  virtual bool Link(Node<ElemType>* pPreNode, Node<ElemType>* pCurNode);
};

template <class ElemType>
SimpleLkList<ElemType>::SimpleLkList() {}

template <class ElemType>
SimpleLkList<ElemType>::SimpleLkList(const SimpleLkList& sllSrc) {
  *this = sllSrc;
}

template <class ElemType>
SimpleLkList<ElemType>::~SimpleLkList() {}

template <class ElemType>
bool SimpleLkList<ElemType>::Link(Node<ElemType>* pPreNode,
                                  Node<ElemType>* pNextNode) {
  if (!pPreNode) { 
    return false;
  }
  pPreNode->m_pNext = pNextNode;
  return true;
}
#endif  // _SIMPLE_LK_LIST_H_
