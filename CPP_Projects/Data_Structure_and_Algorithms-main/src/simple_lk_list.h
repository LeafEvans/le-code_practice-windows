#ifndef SIMPLE_LK_LIST_H_
#define SIMPLE_LK_LIST_H_

#include "lk_list_base.h"
#include "node.h"

template <class ElemType>
class SimpleLkList : public LkListBase<ElemType, Node<ElemType>> {
 public:
  SimpleLkList();                            // 默认构造函数
  ~SimpleLkList();                           // 析构函数
  SimpleLkList(const SimpleLkList& sllSrc);  // 拷贝构造函数

 protected:
  // 链接节点函数
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
  if (!pPreNode) {  // 如果前驱节点为空
    return false;
  }
  pPreNode->m_pNext = pNextNode;  // 将前驱节点的后继指向 pNextNode
  return true;
}

#endif  // SIMPLE_LK_LIST_H_
