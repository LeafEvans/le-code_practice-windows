#ifndef _NODE_H_
#define _NODE_H_
#include <cstddef>

// 单向链表节点类模板
template <class ElemType>
class Node {
 public:
  Node();                                              // 默认构造函数
  Node(const ElemType &tElem, Node<ElemType> *pNext);  // 带参构造函数
  ~Node();                                             // 析构函数

  void ClearLink();  // 清除节点链接关系的虚函数

  ElemType m_tElem;         // 存储节点数据
  Node<ElemType> *m_pNext;  // 指向下一个节点的指针
};

// 单向链表节点类模板实现

template <class ElemType>
Node<ElemType>::Node() : m_pNext(NULL) {}

template <class ElemType>
Node<ElemType>::Node(const ElemType &tElem, Node<ElemType> *pNext)
    : m_tElem(tElem), m_pNext(pNext) {}

template <class ElemType>
Node<ElemType>::~Node() {}

template <class ElemType>
void Node<ElemType>::ClearLink() {
  m_pNext = NULL;  // 断开与下一个节点的连接
}

// 双向链表节点类模板
template <class ElemType>
class DbNode {
 public:
  DbNode();
  DbNode(const ElemType &tElem, DbNode<ElemType> *pPre,
         DbNode<ElemType> *pNext);
  ~DbNode();

  void ClearLink();  // 清除链接操作

  ElemType m_tElem;           // 存储节点数据
  DbNode<ElemType> *m_pPre;   // 指向前一个节点的指针
  DbNode<ElemType> *m_pNext;  // 指向下一个节点的指针
};

// 双向链表节点类模板实现

template <class ElemType>
DbNode<ElemType>::DbNode() : m_pPre(NULL), m_pNext(NULL) {}

template <class ElemType>
DbNode<ElemType>::DbNode(const ElemType &tElem, DbNode<ElemType> *pPre,
                         DbNode<ElemType> *pNext)
    : m_tElem(tElem), m_pPre(pPre), m_pNext(pNext) {}

template <class ElemType>
DbNode<ElemType>::~DbNode() {}

template <class ElemType>
void DbNode<ElemType>::ClearLink() {
  m_pPre = NULL;   // 断开与前一个节点的连接
  m_pNext = NULL;  // 断开与下一个节点的连接
}

#endif  // _NODE_H_
