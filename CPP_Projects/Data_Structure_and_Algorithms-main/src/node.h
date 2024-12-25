#include <cstddef>

#ifndef NODE_H_
#define NODE_H_

template <class ElemType>
struct Node {
  ElemType m_tElem;         // 元素数据
  Node<ElemType>* m_pNext;  // 指向下一个节点的指针

  Node() : m_pNext(NULL) {}  // 默认构造函数
  // 带参数的构造函数
  Node(const ElemType& tElem, Node<ElemType>* pNext = NULL)
      : m_tElem(tElem), m_pNext(pNext) {}

  void ClearLink() { m_pNext = NULL; }  // 清除链接
};
#endif  // _NODE_H_
