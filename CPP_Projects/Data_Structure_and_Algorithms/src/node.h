#ifndef _NODE_H_
#define _NODE_H_

#include <cstddef>

template <class ElemType>
struct Node {
  ElemType m_tElem;
  Node<ElemType> *m_pNext;

  Node() : m_pNext(NULL) {}
  Node(const ElemType &tElem, Node<ElemType> *pNext = NULL)
      : m_tElem(tElem), m_pNext(pNext) {}

  void ClearLink() { m_pNext = NULL; }
};

template <class ElemType>
struct DbNode {
  ElemType m_tElem;
  DbNode<ElemType> *m_pPre;
  DbNode<ElemType> *m_pNext;

  DbNode() : m_pPre(NULL), m_pNext(NULL) {}

  DbNode(const ElemType &tElem, DbNode<ElemType> *pPre = NULL,
         DbNode<ElemType> *pNext = NULL)
      : m_tElem(tElem), m_pPre(pPre), m_pNext(pNext) {}

  void ClearLink() {
    m_pPre = NULL;
    m_pNext = NULL;
  }
};
#endif  // _NODE_H_
