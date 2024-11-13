#ifndef _SIMPLE_LK_LIST_H_
#define _SIMPLE_LK_LIST_H_

#include "lk_list_base.h"
#include "node.h"

template <class ElemType>
class SimpleLkList : public LkListBase<ElemType, Node<ElemType>> {
 public:
  SimpleLkList();                            // 構造函數
  ~SimpleLkList();                           // 析構函數
  SimpleLkList(const SimpleLkList& sllSrc);  // 拷貝構造函數

 protected:
  // 鏈接函數
  virtual bool Link(Node<ElemType>* pPreNode, Node<ElemType>* pCurrNode);
};

template <class ElemType>
SimpleLkList<ElemType>::SimpleLkList() {}

template <class ElemType>
SimpleLkList<ElemType>::SimpleLkList(const SimpleLkList& sllSrc)
    : LkListBase<ElemType, Node<ElemType>>(sllSrc) {}

template <class ElemType>
SimpleLkList<ElemType>::~SimpleLkList() {}

template <class ElemType>
bool SimpleLkList<ElemType>::Link(Node<ElemType>* pPreNode,
                                  Node<ElemType>* pNextNode) {
  if (!pPreNode) {  // 如果前驅爲空
    return false;
  }
  pPreNode->m_pNext = pNextNode;  // 將前驅節點的後繼節點賦值為 pNextNode
  return true;
}

#endif  // _SIMPLE_LK_LIST_H_
