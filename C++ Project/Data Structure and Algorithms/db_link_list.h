#ifndef _DB_LINK_LIST_H_
#define _DB_LINK_LIST_H_
#include "link_list_base.h"

template <class ElemType>

class DbLinkList : public LinkListBase<ElemType, DbNode<ElemType>> {
 public:
  DbLinkList();                          // 无参构造函数
  DbLinkList(const DbLinkList &dllSrc);  // 拷贝构造函数
  ~DbLinkList();                         // 析构函数

  void Tail();                 // 当前节点指向尾节点
  bool Prev(ElemType &tElem);  // 当前节点变更为前驱

 protected:
  // 具体化节点类型
  virtual bool Link(DbNode<ElemType> *pPreNode, DbNode<ElemType> *pNextNode);
};

template <class ElemType>
DbLinkList<ElemType>::DbLinkList() {}

template <class ElemType>
DbLinkList<ElemType>::~DbLinkList() {}

// Link 方法重写，对应着双向循环链表
template <class ElemType>
DbLinkList<ElemType>::DbLinkList(const DbLinkList &dllSrc)
    : LinkListBase<ElemType, DbNode<ElemType>>(dllSrc) {}

template <class ElemType>
bool DbLinkList<ElemType>::Link(DbNode<ElemType> *pPreNode,
                                DbNode<ElemType> *pNextNode) {
  if (!pPreNode) {
    return false;  // 前驅節點違法
  }

  pPreNode->m_pNext = pNextNode;  // 前驅節點的後繼賦值為 pNextNode

  if (pNextNode) {  // 若后继节点不为空
      // 将后继节点的前驱赋值为
    pNextNode->m_pPre = pPreNode;
  }

  return true;
}

template <class ElemType>
void DbLinkList<ElemType>::Tail() {
  this->m_pNodeCur = this->m_pNodeTail;  // 更新当前节点为尾节点
}

template <class ElemType>
bool DbLinkList<ElemType>::Prev(ElemType &tElem) {
  if (!this->m_pNodeCur) {  // 当前节点为空
    return false;
  }

  // 若爲頭節點，則不能繼續向前
  if (this->m_pNodeCur->m_pPre == this->m_pNodeHead) {
    return false;
  }

  // 将当前节点更新为前驱节点
  this->m_pNodeCur = this->m_pNodeCur->m_pPre;

  // 保存当前节点元素
  tElem = this->m_pNodeCur->m_tElem;

  return true;
}
#endif  // _DB_LINK_LIST_H_