#ifndef _NODE_H_
#define _NODE_H_

// 单向链表节点
template <class ElemType>
class Node {
 public:
  Node();                                              // 默认构造函数
  Node(const ElemType &tElem, Node<ElemType> *pNext);  // 有参构造函数
  virtual ~Node();                                     // 析构函数

  virtual void ClearLink();  // 清除链接关系

  ElemType m_tElem;         // 数据域
  Node<ElemType> *m_pNext;  // 指针域
};

template <class ElemType>
Node<ElemType>::Node() : m_pNext(NULL) {}

template <class ElemType>
Node<ElemType>::Node(const ElemType &tElem, Node<ElemType> *pNext)
    : m_tElem(tElem), m_pNext(pNext) {}

template <class ElemType>
Node<ElemType>::~Node() {}

template <class ElemType>
void Node<ElemType>::ClearLink() {
  m_pNext = NULL;  // 将指向后驱节点的指针置为空
}

// 双向链表节点
template <class ElemType>
class DbNode : public Node<ElemType> {
 public:
  DbNode();
  DbNode(const ElemType &tElem, DbNode<ElemType> *pPre,
         DbNode<ElemType> *pNext);
  ~DbNode();

  void ClearLink() override;  // 重写清除链接操作

  DbNode<ElemType> *m_pPre;
};

template <class ElemType>
DbNode<ElemType>::DbNode() : Node<ElemType>(), m_pPre(NULL) {}

template <class ElemType>
DbNode<ElemType>::DbNode(const ElemType &tElem, DbNode<ElemType> *pPre,
                         DbNode<ElemType> *pNext)
    : Node<ElemType>(tElem, pNext), m_pPre(pPre) {}

template <class ElemType>
DbNode<ElemType>::~DbNode() {}

template <class ElemType>
void DbNode<ElemType>::ClearLink() {
  Node<ElemType>::ClearLink();  // 调用父类的 ClearLink
  m_pPre = NULL;
}

#endif  // _NODE_H_
