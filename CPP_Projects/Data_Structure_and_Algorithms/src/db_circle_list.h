#ifndef DB_CIRCLE_LIST_H_
#define DB_CIRCLE_LIST_H_

#include "circle_list_base.h"
#include "node.h"

template <class ElemType>
class DbCircleList : public CircleListBase<ElemType, DbNode<ElemType>> {
 public:
  DbCircleList();                            // 构造函数
  ~DbCircleList();                           // 析构函数
  DbCircleList(const DbCircleList& dclSrc);  // 拷贝构造函数
  void Tail();                 // 将当前节点移动到尾节点
  bool Prev(ElemType& tElem);  // 移动到前驱节点并获取其值
  bool Reverse();              // 反转链表

 protected:
  // 链接两个节点
  virtual bool Link(DbNode<ElemType>* pPreNode, DbNode<ElemType>* pNextNode);
};

template <class ElemType>
DbCircleList<ElemType>::DbCircleList() {
  this->LinkTailToHead();  // 初始化时链接尾节点到头节点
}

template <class ElemType>
DbCircleList<ElemType>::~DbCircleList() {}

template <class ElemType>
DbCircleList<ElemType>::DbCircleList(const DbCircleList<ElemType>& dclSrc)
    : CircleListBase<ElemType, DbNode<ElemType>>(dclSrc) {
  this->LinkTailToHead();  // 拷贝构造后确保尾节点链接到头节点
}

template <class ElemType>
bool DbCircleList<ElemType>::Link(DbNode<ElemType>* pPreNode,
                                  DbNode<ElemType>* pNextNode) {
  if (!pPreNode) {
    // 前驱节点不能为空
    return false;
  }

  pPreNode->m_pNext = pNextNode;  // 设置前驱节点的后继

  if (pNextNode) {
    pNextNode->m_pPre = pPreNode;  // 设置后继节点的前驱（如果存在）
  }
}

template <class ElemType>
void DbCircleList<ElemType>::Tail() {
  this->m_pCurrNode = this->m_pTailNode;  // 将当前节点设置为尾节点
}

template <class ElemType>
bool DbCircleList<ElemType>::Prev(ElemType& tElem) {
  if (this->IsEmpty() || !this->m_pCurrNode || !this->m_pCurrNode->m_pPre) {
    // 链表为空、当前节点不存在或其前驱不存在时返回失败
    return false;
  }

  this->m_pCurrNode = this->m_pCurrNode->m_pPre;  // 移动到前驱节点

  if (this->m_pCurrNode == this->m_pHeadNode) {
    // 如果到达头节点，再往前移动一次
    this->m_pCurrNode = this->m_pCurrNode->m_pPre;
  }

  tElem = this->m_pCurrNode->m_tElem;  // 获取当前节点的值

  return true;
}

template <class ElemType>
bool DbCircleList<ElemType>::Reverse() {
  if (this->IsEmpty()) {
    return false;
  }

  DbNode<ElemType> pFirstNode = this->GetFirstNode();
  DbNode<ElemType> pNode = this->m_pHeadNode;

  do {
    DbNode<ElemType> pNext = pNode->m_pNext;
    pNode->m_pNext = pNode->m_pPre;
    pNode->m_pPre = pNext;
    pNode = pNext;
  } while (pNode != this->m_pHeadNode);

  this->m_pTailNode = pFirstNode;

  return true;
}

#endif  // DB_CIRCLE_LIST_H_
