#ifndef _DB_CIRCLE_LIST_H_
#define _DB_CIRCLE_LIST_H_
#include "circle_list_base.h"

template <class ElemType>
class DbCircleList : public CircleListBase<ElemType, DbNode<ElemType>> {
 public:
  DbCircleList();                            // 默認構造函數
  ~DbCircleList();                           // 析構函數
  DbCircleList(const DbCircleList& dclSrc);  // 拷貝構造函數
  void Tail();                 // 將當前節點轉移到尾節點
  bool Prev(ElemType& tElem);  // 返回到前驅節點並獲取其值
  bool Reverse();              // 逆轉鏈表

 protected:
  // 鏈接函數
  virtual bool Link(DbNode<ElemType>* pPreNode, DbNode<ElemType>* pNextNode);
};

template <class ElemType>
DbCircleList<ElemType>::DbCircleList() {
  this->LinkTailToHead();  // 调用基类 LinkTailToHead() 方法
}

template <class ElemType>
DbCircleList<ElemType>::~DbCircleList() {}

template <class ElemType>
DbCircleList<ElemType>::DbCircleList(const DbCircleList<ElemType>& dclSrc)
    : CircleListBase<ElemType, DbNode<ElemType>>(dclSrc) {
  this->LinkTailToHead();
}

template <class ElemType>
bool DbCircleList<ElemType>::Link(DbNode<ElemType>* pPreNode,
                                  DbNode<ElemType>* pNextNode) {
  if (!pPreNode) {
    // 若前驅節點為非空
    return false;
  }

  pPreNode->m_pNext = pNextNode;  //

  if (pNextNode) {
    pNextNode->m_pPre = pPreNode;
  }
}

template <class ElemType>
void DbCircleList<ElemType>::Tail() {
  this->m_pNodeCur = this->m_pNodeTail;
}

template <class ElemType>
bool DbCircleList<ElemType>::Prev(ElemType& tElem) {
  if (this->IsEmpty() || !this->m_pNodeCur || !this->m_pNodeCur->m_pPre) {
    // 若鏈表為空、或當前節點不存在、或其前驅不存在
    return false;
  }

  this->m_pNodeCur = this->m_pNodeCur->m_pPre;  // 更新當前節點

  if (this->m_pNodeCur == this->m_pNodeHead) {
    // 若爲頭節點，再更新一次
    this->m_pNodeCur = this->m_pNodeCur->m_pPre;
  }

  tElem = this->m_pNodeCur->m_tElem;  // 獲取當前節點的值

  return true;
}

template <class ElemType>
bool DbCircleList<ElemType>::Reverse() {
  if (this->IsEmpty()) {
    return false;  // 若为空链表，则不需要调转
  }

  DbNode<ElemType>* pFirstNode = this->GetFirstNode();  // 獲取首元節點
  DbNode<ElemType>* pNode = this->m_pNodeHead;          // 初始化遍歷節點

  do {
    DbNode<ElemType>* pNext = pNode->m_pNext;  // 暫存後繼節點
    // 將前驅節點和後繼節點進行互換
    pNode->m_pNext = pNode->m_mPre;
    pNode->m_pPre = pNext;
    pNode = pNext;  // 更新當前節點
  } while (pNode != this->m_pNodeHead);

  this->m_NodeTail = pFirstNode;  // 更新當前尾節點

  return true;
}

#endif  // _DB_CIRCLE_LIST_H_
