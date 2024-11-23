#ifndef _LK_LIST_BASE_H_
#define _LK_LIST_BASE_H_

#include <cstddef>

#include "list_base.h"

template <class ElemType, class NodeType>
class LkListBase : public ListBase<ElemType> {
 public:
  LkListBase();                  // 构造函数
  virtual ~LkListBase();         // 析构函数
  virtual int Length() const;    // 获取线性表元素个数
  virtual bool IsEmpty() const;  // 判断线性表是否为空
  virtual void Clear();          // 清空线性表
  virtual bool GetElem(int nIdx, ElemType &tElem) const;  // 获取指定元素位置
  virtual bool SetElem(int nIdx, const ElemType &tElem);  // 设置指定位置元素
  virtual bool Delete(int nIdx, ElemType &tElem);  // 删除指定位置元素
  virtual bool Insert(int nIdx, const ElemType &tElem);  // 指定位置插入元素
  virtual void Traverse(bool (*pVisit)(const ElemType &)) const;  // 遍历线性表
  virtual int AddTail(const ElemType &tElem);  // 添加数据至线性表末尾
  virtual LkListBase<ElemType, NodeType> &operator=(
      const LkListBase<ElemType, NodeType> &llbSrc);  // 重载 = 运算符
  virtual void Head();                 // 当前节点指向头节点
  virtual bool Next(ElemType &tElem);  // 当前节点后移，同时获取后继节点数据
  virtual bool SetCurrElem(const ElemType &tElem);  // 设置当前节点数据
  virtual bool DeleteCurr(ElemType &tElem);         // 删除当前节点数据

 protected:
  // 链接两个节点，不同的节点类型有不同的链接方式
  virtual bool Link(NodeType *pPreNode, NodeType *pNextNode) = 0;
  // 根据索引寻找节点
  virtual NodeType *FindNode(int nIdx, NodeType *&pPreNode) const;
  virtual NodeType *GetFirstNode() const;          // 获取首元节点
  virtual bool IsEndWhile(NodeType *pNode) const;  // 是否结束循环语句

  NodeType *m_pNodeCurr;     // 当前节点指针
  NodeType *m_pNodeHead;     // 头节点指针
  NodeType *m_pNodeTail;     // 尾节点指针
  int m_nNodeCounts;         // 当前节点数量
  bool m_bSpecialDetection;  // 特殊析构方式，如广义表
};

template <class ElemType, class NodeType>
LkListBase<ElemType, NodeType>::LkListBase()
    : m_pNodeCurr(new NodeType()),
      m_pNodeHead(m_pNodeCurr),
      m_pNodeTail(m_pNodeCurr),
      m_nNodeCounts(0),
      m_bSpecialDetection(false) {}

template <class ElemType, class NodeType>
LkListBase<ElemType, NodeType> &LkListBase<ElemType, NodeType>::operator=(
    const LkListBase<ElemType, NodeType> &llbSrc) {
  if (this == &llbSrc) {
    return *this;
  }

  Clear();                      // 清空节点
  m_bSpecialDetection = false;  // 默认非广义表

  NodeType *pSrcNode = llbSrc.GetFirstNode();  // 获取首元节点
  NodeType *pPreNode = m_pNodeHead;  // 前驱节点初始化为头节点

  while (!llbSrc.IsEndWhile(pSrcNode)) {
    NodeType *pNewNode = new NodeType();    // 构造一个新节点
    pNewNode->m_tElem = pSrcNode->m_tElem;  // 为新节点的数据域赋值
    Link(pPreNode, pNewNode);               // 链接前驱节点和新节点
    pSrcNode = pSrcNode->m_pNext;           // 更新源节点
    pPreNode = pNewNode;                    // 更新前驱节点
    ++m_nNodeCounts;                        // 节点数量增加
  }

  m_pNodeTail = pPreNode;     // 设置尾节点
  m_pNodeCurr = m_pNodeHead;  // 设置当前节点
  return *this;               // 返回本身
}

template <class ElemType, class NodeType>
LkListBase<ElemType, NodeType>::~LkListBase() {
  if (!m_bSpecialDetection) {
    NodeType *pCurr = m_pNodeHead->m_pNext;
    while (pCurr != NULL && pCurr != m_pNodeHead) {
      NodeType *pNext = pCurr->m_pNext;
      delete pCurr;
      pCurr = pNext;
    }

    if (m_pNodeHead) {     // 若头节点不为空
      delete m_pNodeHead;  // 释放头节点空间
      m_pNodeHead = NULL;  // 将头节点置为空
    }
  }
}

template <class ElemType, class NodeType>
int LkListBase<ElemType, NodeType>::Length() const {
  return m_nNodeCounts;  // 放回节点个数
}

template <class ElemType, class NodeType>
NodeType *LkListBase<ElemType, NodeType>::GetFirstNode() const {
  return m_pNodeHead->m_pNext;  // 返回头节点的后继节点
}

template <class ElemType, class NodeType>
bool LkListBase<ElemType, NodeType>::IsEndWhile(NodeType *pNode) const {
  return !pNode || pNode == m_pNodeHead;  // 判断此时是否为空或为头节点
}

template <class ElemType, class NodeType>
void LkListBase<ElemType, NodeType>::Head() {
  m_pNodeCurr = m_pNodeHead;  // 更新当前指针为头节点
}

template <class ElemType, class NodeType>
bool LkListBase<ElemType, NodeType>::Next(ElemType &tElem) {
  if (m_pNodeCurr == NULL || m_pNodeCurr->m_pNext == NULL) {
    return false;
  }

  m_pNodeCurr = m_pNodeCurr->m_pNext;
  tElem = m_pNodeCurr->m_tElem;

  return true;
}

template <class ElemType, class NodeType>
bool LkListBase<ElemType, NodeType>::SetCurrElem(const ElemType &tElem) {
  if (m_pNodeCurr == m_pNodeHead || m_pNodeCurr == NULL) {
    // 若��空或为头节点
    return false;
  }
  m_pNodeCurr->m_tElem = tElem;  // 设置指定位置元素
  return true;
}

template <class ElemType, class NodeType>
bool LkListBase<ElemType, NodeType>::DeleteCurr(ElemType &tElem) {
  if (m_pNodeCurr == NULL || m_pNodeCurr->m_pNext == NULL) {
    // 当前节点或其后继为空，则不能删除
    return false;
  }

  NodeType *pNextNode = m_pNodeCurr->m_pNext;  // 获取当前节点的后继
  NodeType *pPreNode = m_pNodeHead;  // 前驱节点初始化为头节点
  NodeType *pNode = GetFirstNode();  // 获取首元节点

  bool bFindPre = false;  // 默认初始化为 False

  while (!IsEndWhile(pNode)) {
    if (pNode == m_pNodeCurr) {
      // 当遍历节点与当前节点相同
      bFindPre = true;
      break;  // 找到前驱终止循环
    }
    pPreNode = pNode;
    pNode = pNode->m_pNext;
  }

  if (!bFindPre) {  // 若还未找到
    return false;
  }

  Link(pPreNode, pNextNode);  // 链接前后节点
  tElem = pNode->m_tElem;

  if (pNode == m_pNodeTail) {
    // 若为尾节点，设置前驱节点为新尾节点
    m_pNodeTail = pPreNode;
  }

  // 设置当前节点为前驱节点
  m_pNodeCurr = pPreNode;
  delete pNode;     // 删除当前节点
  --m_nNodeCounts;  // 节点数量减少
  return true;
}

template <class ElemType, class NodeType>
void LkListBase<ElemType, NodeType>::Clear() {
  if (m_pNodeHead == NULL) {
    return;
  }

  NodeType *pNode = m_pNodeHead->m_pNext;  // 直接使用头节点的后继

  while (pNode != nullptr && pNode != m_pNodeHead) {
    NodeType *pNodeNext = pNode->m_pNext;  // 存储后继节点
    delete pNode;                          // 删除当前节点
    pNode = pNodeNext;                     // 更新当前节点
  }

  m_pNodeHead->ClearLink();   // 清空头节点链接状态
  m_nNodeCounts = 0;          // 节点数目为 0
  m_pNodeTail = m_pNodeHead;  // 尾节点为头节点
  m_pNodeCurr = m_pNodeHead;  // 当前节点为头节点
}

template <class ElemType, class NodeType>
bool LkListBase<ElemType, NodeType>::IsEmpty() const {
  return !GetFirstNode();  // 首元节点不为空
}

template <class ElemType, class NodeType>
NodeType *LkListBase<ElemType, NodeType>::FindNode(int nIdx,
                                                   NodeType *&pPreNode) const {
  if (nIdx < 0) {  // 如果索引小于0，返回NULL
    return NULL;
  }

  pPreNode = m_pNodeHead;  // 初始化前驱节点为头节点

  NodeType *pFindNode = NULL;        // 初始化找到的节点为NULL
  NodeType *pNode = GetFirstNode();  // 获取首元节点

  for (int i = 0; !IsEndWhile(pNode); ++i) {  // 遍历链表
    if (i == nIdx) {      // 如果当前索引等于目标索引
      pFindNode = pNode;  // 找到目标节点
      break;              // 退出循环
    }

    pPreNode = pNode;        // 更新前驱节点
    pNode = pNode->m_pNext;  // 移动到下一个节点
  }

  return pFindNode;  // 返回找到的节点
}

template <class ElemType, class NodeType>
bool LkListBase<ElemType, NodeType>::SetElem(int nIdx, const ElemType &tElem) {
  NodeType *pPreNode;  // 前驱节点
  NodeType *pNode = FindNode(nIdx, pPreNode);

  if (pNode == NULL) {  // 如果目标节点为空
    return false;
  }
  pNode->m_tElem = tElem;  // 设定目标节点数值

  return true;
}

template <class ElemType, class NodeType>
bool LkListBase<ElemType, NodeType>::GetElem(int nIdx, ElemType &tElem) const {
  NodeType *pPreNode;  // 得到指定位置元素
  NodeType *pNode = FindNode(nIdx, pPreNode);

  if (pNode == NULL) {  // 当前节点为空
    return false;
  }

  tElem = pNode->m_tElem;  // 获取指定元素

  return true;
}

template <class ElemType, class NodeType>
bool LkListBase<ElemType, NodeType>::Delete(int nIdx, ElemType &tElem) {
  NodeType *pPreNode;
  NodeType *pNode = FindNode(nIdx, pPreNode);

  if (pNode == NULL) {  // 当前节点为空
    return false;
  }

  Link(pPreNode, pNode->m_pNext);  // 链接前驱和后继

  tElem = pNode->m_tElem;

  if (pNode == m_pNodeTail) {  // 若当前节点为尾节点
    m_pNodeTail = pPreNode;    // 置其前驱节点为尾节点
  }

  m_pNodeCurr = pPreNode;  // 当前节点为前驱节点
  delete pNode;            // 删除目标节点
  --m_nNodeCounts;         // 节点数量减少

  return true;
}

template <class ElemType, class NodeType>
bool LkListBase<ElemType, NodeType>::Insert(int nIdx, const ElemType &tElem) {
  NodeType *pPreNode;
  NodeType *pNode = FindNode(nIdx, pPreNode);

  if (pNode == NULL) {            // 指针为空
    if (nIdx == m_nNodeCounts) {  // 说明插入位置位于线性表末尾
      AddTail(tElem);             // 调用 AddTail 方法
      return true;                // 返回 true
    } else {
      return false;  // 否则返回 false
    }
  }

  NodeType *pNewNode = new NodeType();  // 新节点
  pNewNode->m_tElem = tElem;            // 设置其元素
  Link(pPreNode, pNewNode);             // 链接节点
  Link(pNewNode, pNode);

  ++m_nNodeCounts;         // 节点数量增加
  m_pNodeCurr = pNewNode;  // 设置当前节点为新节点

  return true;
}

template <class ElemType, class NodeType>
void LkListBase<ElemType, NodeType>::Traverse(
    bool (*pVisit)(const ElemType &)) const {
  if (pVisit == NULL || IsEmpty()) {
    return;  // 指针为空或為空
  }

  for (NodeType *pNode = GetFirstNode(); !IsEndWhile(pNode);
       pNode = pNode->m_pNext) {
    if (!(*pVisit)(pNode->m_tElem)) {
      break;
    }
  }
}

template <class ElemType, class NodeType>
int LkListBase<ElemType, NodeType>::AddTail(const ElemType &tElem) {
  NodeType *pNewNode = new NodeType();
  pNewNode->m_tElem = tElem;    // 为新节点赋值
  Link(m_pNodeTail, pNewNode);  // 链接尾节点和新节点
  m_pNodeTail = pNewNode;       // 尾节点变更为新节点
  m_pNodeCurr = pNewNode;       // 变更当前节点为新节点
  return m_nNodeCounts++;       // 返回新节点索引，节点数目加 1
}

#endif  // _LK_LIST_BASE_H_
