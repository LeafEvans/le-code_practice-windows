#ifndef SIMPLE_CIRCLE_LIST_H_
#define SIMPLE_CIRCLE_LIST_H_

#include "circle_list_base.h"
#include "node.h"

template <class ElemType>
class SimpleCircleList : public CircleListBase<ElemType, Node<ElemType>> {
 public:
  SimpleCircleList();                                // 构造函数
  ~SimpleCircleList();                               // 析构函数
  SimpleCircleList(const SimpleCircleList& sclSrc);  // 拷贝构造函数

 protected:
  // 链接两个节点
  virtual bool Link(Node<ElemType>* pPreNode,
                    Node<ElemType>* pNextNode) override;
};

template <class ElemType>
SimpleCircleList<ElemType>::SimpleCircleList() {}

template <class ElemType>
SimpleCircleList<ElemType>::~SimpleCircleList() {}

template <class ElemType>
SimpleCircleList<ElemType>::SimpleCircleList(const SimpleCircleList& sclSrc)
    : CircleListBase<ElemType, Node<ElemType>>::CircleListBase(sclSrc) {
  // 调用父类构造函数后链接尾节点到头节点
  this->LinkTailToHead();
}

template <class ElemType>
bool SimpleCircleList<ElemType>::Link(Node<ElemType>* pPreNode,
                                      Node<ElemType>* pNextNode) {
  if (!pPreNode) {  // 前驱节点为空
    return false;
  }

  pPreNode->m_pNext = pNextNode;  // 更新前驱节点的后继
  return true;
}

#endif  // SIMPLE_CIRCLE_LIST_H_
