#ifndef DB_NODE_H_
#define DB_NODE_H_
#include <cstddef>
template <class ElemType>
struct DbNode {
  ElemType m_tElem;           // 元素数据
  DbNode<ElemType>* m_pPre;   // 指向前驱节点的指针
  DbNode<ElemType>* m_pNext;  // 指向后继节点的指针

  DbNode() : m_pPre(NULL), m_pNext(NULL) {}  // 默认构造函数

  DbNode(const ElemType& tElem, DbNode<ElemType>* pPre = NULL,
         DbNode<ElemType>* pNext = NULL)  // 带参数的构造函数
      : m_tElem(tElem), m_pPre(pPre), m_pNext(pNext) {}

  void ClearLink() {  // 清除链接
    m_pPre = NULL;
    m_pNext = NULL;
  }
};
#endif  // DB_NODE_H_