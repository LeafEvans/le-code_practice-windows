#ifndef _SIMPLE_LINK_LIST_H_
#define _SIMPLE_LINK_LIST_H_
#include "link_list_base.h"

template <class ElemType>
class SimpleLinkList : public LinkListBase<ElemType, Node<ElemType>> {
 public:
  SimpleLinkList();                              // 構造函數
  ~SimpleLinkList();                             // 析構函數
  SimpleLinkList(const SimpleLinkList& sllSrc);  // 拷貝構造函數

 protected:
  // 鏈接函數
  virtual bool Link(Node<ElemType>* pPreNode, Node<ElemType>* pCurNode);
};

template <class ElemType>
SimpleLinkList<ElemType>::SimpleLinkList() {}

template <class ElemType>
SimpleLinkList<ElemType>::SimpleLinkList(const SimpleLinkList& sllSrc)
    : LinkListBase<ElemType, Node<ElemType>>(sllSrc) {}

template <class ElemType>
SimpleLinkList<ElemType>::~SimpleLinkList() {}

template <class ElemType>
bool SimpleLinkList<ElemType>::Link(Node<ElemType>* pPreNode,
                                    Node<ElemType>* pNextNode) {
  if (!pPreNode) {  // 如果前驅爲空
    return false;
  }
  pPreNode->m_pNext = pNextNode;  // 將前驅節點的後繼節點賦值為 pNextNode
  return true;
}

#endif  // _SIMPLE_LINK_LIST_H_
