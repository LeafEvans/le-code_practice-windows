#ifndef DB_LK_LIST_H_
#define DB_LK_LIST_H_
#include "lk_list_base.h"
#include "db_node.h"

template <class ElemType>
class DbLkList : public LkListBase<ElemType, DbNode<ElemType>> {
 public:
  DbLkList();                        // 默认构造函数
  DbLkList(const DbLkList& dllSrc);  // 拷贝构造函数
  ~DbLkList();                       // 析构函数

  void Tail();                 // 将当前节点移动到尾节点
  bool Prev(ElemType& tElem);  // 将当前节点移动到前驱节点并获取其元素值

 protected:
  // 链接两个节点，实现双向链表的特性
  virtual bool Link(DbNode<ElemType>* pPreNode, DbNode<ElemType>* pNextNode);
};

template <class ElemType>
DbLkList<ElemType>::DbLkList() {}

template <class ElemType>
DbLkList<ElemType>::~DbLkList() {}

template <class ElemType>
DbLkList<ElemType>::DbLkList(const DbLkList& dllSrc)
    : LkListBase<ElemType, DbNode<ElemType>>(dllSrc) {}

template <class ElemType>
bool DbLkList<ElemType>::Link(DbNode<ElemType>* pPreNode,
                              DbNode<ElemType>* pNextNode) {
  if (!pPreNode) {
    return false;  // 前驱节点不能为空
  }

  pPreNode->m_pNext = pNextNode;  // 设置前驱节点的后继

  if (pNextNode) {                 // 如果后继节点存在
    pNextNode->m_pPre = pPreNode;  // 设置后继节点的前驱
  }

  return true;
}

template <class ElemType>
void DbLkList<ElemType>::Tail() {
  this->m_pCurrNode = this->m_pTailNode;  // 将当前节点设置为尾节点
}

template <class ElemType>
bool DbLkList<ElemType>::Prev(ElemType& tElem) {
  if (!this->m_pCurrNode) {  // 当前节点不存在
    return false;
  }

  if (this->m_pCurrNode->m_pPre == this->m_pHeadNode) {
    return false;  // 当前节点已是首元节点，无法继续向前
  }

  this->m_pCurrNode = this->m_pCurrNode->m_pPre;  // 移动到前驱节点
  tElem = this->m_pCurrNode->m_tElem;  // 获取当前节点的元素值

  return true;
}
#endif  // DB_LK_LIST_H_