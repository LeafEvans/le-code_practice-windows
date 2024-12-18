#ifndef REF_GEN_LIST_H_
#define REF_GEN_LIST_H_
#include <iostream>

#include "lk_list_base.h"
#include "node.h"

template <typename ElemType>
class RefGenList : private LkListBase<ElemType, RefGenNode<ElemType>> {
 public:
  RefGenList();
  RefGenList(const RefGenList<ElemType>& rglSrc);
  ~RefGenList();
  RefGenNode<ElemType>* First() const;
  bool IsEmpty() const;
  void Push(const ElemType& tElem);
  void Push(RefGenList<ElemType>& rglSub);
  void Show() const;
  int Depth() const;
  void Input();
  RefGenNode<ElemType>* Next(RefGenNode<ElemType>* pNode);
  RefGenList<ElemType>& operator=(const RefGenList<ElemType>& rglSrc);

 private:
  virtual bool Link(RefGenNode<ElemType>* pPreNode,
                    RefGenNode<ElemType>* pNextNode);
  void ClearAux(RefGenNode<ElemType>*& pHeadNode);
  void CopyAux(const RefGenNode<ElemType>* pSrcHead,
               RefGenNode<ElemType>* pDesHead);
  void ShowAux(RefGenNode<ElemType>* pHeadNode) const;
  int DepthAux(const RefGenNode<ElemType>* pHeadNode) const;
  void CreateAux(RefGenNode<ElemType>*& pFirstNode);
};

template <class ElemType>
RefGenList<ElemType>::RefGenList() {
  this->m_pHeadNode->m_eTag = _HEAD;  // 设置头节点标识
  this->m_pHeadNode->m_nRef = 1;      // 初始化引用计数为 1
  // 启用特殊析构机制，保证链表节点不会随链表销毁
  this->m_bSpecialDetection = true;
}

template <class ElemType>
RefGenList<ElemType>::RefGenList(const RefGenList<ElemType>& rglSrc) {
  this->m_bSpecialDetection = true;
  CopyAux(rglSrc.m_pHeadNode);
}

template <class ElemType>
RefGenList<ElemType>::~RefGenList() {
  ClearAux(this->m_pHeadNode);
}

template <class ElemType>
RefGenNode<ElemType>* RefGenList<ElemType>::First() const {
  return this->m_pHeadNode->m_pNext;
}

template <class ElemType>
bool RefGenList<ElemType>::IsEmpty() const {
  return LkListBase<ElemType, RefGenNode<ElemType>>::IsEmpty();
}

template <class ElemType>
void RefGenList<ElemType>::Push(const ElemType& tElem) {
  if (!this->Insert(0, tElem))
    return;
  this->m_pCurrNode->m_eTag = _ATOM;
}

template <class ElemType>
void RefGenList<ElemType>::Push(RefGenList<ElemType>& rglSub) {
  if (!this->Insert(0, 0))
    return;
  RefGenNode<ElemType>* pCurrNode = this->m_pCurrNode;
  pCurrNode->m_pSub = rglSub.m_pHeadNode;
  ++(rglSub.m_pHeadNode->m_nRef);
  pCurrNode->m_eTag = _LIST;
}

template <class ElemType>
void RefGenList<ElemType>::Show() const {
  ShowAux(this->m_pHeadNode);
}

template <class ElemType>
int RefGenList<ElemType>::Depth() const {
  return DepthAux(this->m_pHeadNode);
}

template <class ElemType>
void RefGenList<ElemType>::Input() {
  if (this->m_pHeadNode)
    ClearAux(this->m_pHeadNode);

  char chElem;
  this->m_pHeadNode = new RefGenNode<ElemType>(_HEAD);
  this->m_pHeadNode->m_nRef = 1;

  std::cin >> chElem;

  CreateAux(First());
}

template <class ElemType>
RefGenNode<ElemType>* RefGenList<ElemType>::Next(RefGenNode<ElemType>* pNode) {
  return pNode->m_pNext;
}

template <class ElemType>
RefGenList<ElemType>& RefGenList<ElemType>::operator=(
    const RefGenList<ElemType>& rglSrc) {
  if (&rglSrc != this) {
    ClearAux(this->m_pHeadNode);
    CopyAux(rglSrc.m_pHeadNode, this->m_pHeadNode);
  }
  return *this;
}

template <class ElemType>
bool RefGenList<ElemType>::Link(RefGenNode<ElemType>* pPreNode,
                                RefGenNode<ElemType>* pNextNode) {
  if (!pPreNode)
    return false;
  pPreNode->m_pNext = pNextNode;
  return true;
}

template <class ElemType>
void RefGenList<ElemType>::ClearAux(RefGenNode<ElemType>*& pHeadNode) {
  if (!pHeadNode || pHeadNode->m_eTag != _HEAD)
    return;

  --(pHeadNode->m_nRef);

  if (pHeadNode->m_nRef == 0) {
    RefGenNode<ElemType>* pNode = First();

    while (pNode) {
      RefGenNode<ElemType>* pNextNode = pNode->m_pNext;

      if (pNode->m_eTag == _LIST)
        ClearAux(pNode->m_pSub);

      delete pNode;
      pNode = pNextNode;
    }
  }

  delete pHeadNode;
  pHeadNode = NULL;
}

template <class ElemType>
void RefGenList<ElemType>::CopyAux(const RefGenNode<ElemType>* pSrcHead,
                                   RefGenNode<ElemType>* pDesHead) {
  pDesHead = new RefGenNode<ElemType>(_HEAD);
  RefGenNode<ElemType>* pDesCurr = pDesHead;
  pDesHead->m_nRef = 1;

  for (RefGenNode<ElemType>* pSrcCurr = pSrcHead->m_pNext; pSrcCurr != NULL;
       pSrcCurr = pSrcCurr->m_pNext) {
    if (pSrcCurr->m_eTag == _LIST) {
      CopyAux(pSrcCurr->m_pSub, pDesCurr->m_pSub);
    } else {
      pDesCurr->m_tElem = pSrcCurr->m_tElem;
    }
  }
}

template <class ElemType>
void RefGenList<ElemType>::ShowAux(RefGenNode<ElemType>* pHeadNode) const {
  bool bIsFirst = true;
  std::cout << '(';
  for (RefGenNode<ElemType>* pNode = pHeadNode->m_pNext; pNode != NULL;
       pNode = pNode->m_pNex) {
    if (bIsFirst) {
      bIsFirst = false;
    } else {
      std::cout << ',';
    }

    if (pNode->m_eTag == _ATOM) {
      std::cout << pNode->m_tElem;
    } else {
      ShowAux(pNode->m_pSub);
    }
  }
  std::cout << ')';
}

template <class ElemType>
int RefGenList<ElemType>::DepthAux(
    const RefGenNode<ElemType>* pHeadNode) const {
  if (!pHeadNode->m_pNext)
    return 1;
  int nSubMaxDepth = 0;
  for (RefGenNode<ElemType>* pNode = pHeadNode->m_pNext; pNode != NULL;
       pNode = pNode->m_pNext) {
    if (pNode->m_eTag == _LIST) {
      int nSubDepth = DepthAux(pNode->m_pSub);
      if (nSubDepth > nSubMaxDepth)
        nSubMaxDepth = nSubDepth;
    }
  }
  return nSubMaxDepth + 1;
}

template <class ElemType>
void RefGenList<ElemType>::CreateAux(RefGenNode<ElemType>*& pFirstNode) {
  char chElem;
  std::cin >> chElem;

  switch (chElem) {
    case ')':  // 遇到')'表示当前表结束，返回
      return;

    case '(': {  // 遇到'('表示开始子表
      pFirstNode = new RefGenNode<ElemType>(_LIST);
      RefGenNode<ElemType>* pSubHead = new RefGenNode<ElemType>(_HEAD);
      pSubHead->m_nRef = 1;
      pFirstNode->m_pSub = pSubHead;
      CreateAux(pSubHead->m_pNext);  // 递归创建子表
      std::cin >> chElem;

      // 处理子表后是否有','分隔符
      if (chElem != ',')
        std::cin.putback(chElem);
      CreateAux(pFirstNode->m_pNext);  // 递归创建当前表的下一个节点
      break;
    }

    default: {                   // 处理原子元素
      std::cin.putback(chElem);  // 将字符放回流中
      ElemType tData;
      std::cin >> tData;
      pFirstNode = new RefGenNode<ElemType>(_ATOM);
      pFirstNode->m_tElem = tData;

      std::cin >> chElem;
      // 处理原子元素后是否有','分隔符
      if (chElem != ',')
        std::cin.putback(chElem);
      CreateAux(pFirstNode->m_pNext);  // 递归创建下一个节点
      break;
    }
  }
}

#endif  // REF_GEN_LIST_H_