#ifndef _SIMPLE_CIRCLE_LIST_H_
#define _SIMPLE_CIRCLE_LIST_H_
#include "CircleListBase.h"

template <class ElemType>
class SimpleCircleList : public CircleListBase<ElemType, Node<ElemType>> {
 public:
  SimpleCircleList();                                // 构造函数
  ~SimpleCircleList();                               // 析构函数
  SimpleCircleList(const SimpleCircleList& sclSrc);  // 拷贝构造函数

 protected:
  // 链接两个节点
  virtual bool Link(Node<ElemType>* pPreNode, Node<ElemType>* pNextNode);
};

template <class ElemType>
SimpleCircleList<ElemType>::SimpleCircleList() {}

template <class ElemType>
SimpleCircleList<ElemType>::~SimpleCircleList() {}

template <class ElemType>
SimpleCircleList<ElemType>::SimpleCircleList(const SimpleCircleList& sclSrc) {
  *this = sclSrc;
  this->LinkTailToHead();
}

template <class ElemType>
bool SimpleCircleList<ElemType>::Link(Node<ElemType>* pPreNode,
                                      Node<ElemType>* pNextNode) {
  if (!pPreNode) {  // 前驱节点为空
    return false;
  }

  pPreNode->m_pNext = pNextNode;
  return true;
}

#endif  // _SIMPLE_CIRCLE_LIST_H_