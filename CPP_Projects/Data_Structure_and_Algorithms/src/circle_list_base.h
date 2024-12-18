#ifndef CIRCLE_LIST_BASE_H_
#define CIRCLE_LIST_BASE_H_

#include "lk_list_base.h"

template <class ElemType, class NodeType>
class CircleListBase : public LkListBase<ElemType, NodeType> {
 public:
  CircleListBase();                              // 构造函数
  ~CircleListBase();                             // 析构函数
  CircleListBase(const CircleListBase& clbSrc);  // 拷贝构造函数

  // 添加将尾节点连接到头节点的操作
  virtual bool Delete(int nIdx, ElemType& tElem);  // 重载删除指定位置元素
  virtual bool Insert(int nIdx, const ElemType& tElem);  // 重载指定位置插入元素
  virtual int AddTail(const ElemType& tElem);  // 重载添加数据添加到链表末尾
  virtual bool IsEmpty() const;                // 判断线性表是否为空
  virtual CircleListBase& operator=(
      const CircleListBase<ElemType, NodeType>& clbSrc);  // 重载赋值运算符
  virtual void Clear();                                   // 清空线性表
  virtual bool Next(ElemType& tElem);  // 当前节点后移，同时获取后继数据

 protected:
  virtual NodeType* GetFirstNode() const;  // 获取首元节点
  virtual void LinkTailToHead();           // 链接尾节点与头节点
};

template <class ElemType, class NodeType>
CircleListBase<ElemType, NodeType>::CircleListBase() {}

template <class ElemType, class NodeType>
CircleListBase<ElemType, NodeType>::CircleListBase(const CircleListBase& clbSrc)
    : LkListBase<ElemType, NodeType>(clbSrc) {}

template <class ElemType, class NodeType>
CircleListBase<ElemType, NodeType>::~CircleListBase() {}

template <class ElemType, class NodeType>
CircleListBase<ElemType, NodeType>&
CircleListBase<ElemType, NodeType>::operator=(
    const CircleListBase<ElemType, NodeType>& clbSrc) {
  LkListBase<ElemType, NodeType>::operator=(clbSrc);
  LinkTailToHead();  // 在原有基础上，将尾节点链接到头节点上
  return *this;
}

template <class ElemType, class NodeType>
void CircleListBase<ElemType, NodeType>::LinkTailToHead() {
  // 链接尾节点和头节点
  this->Link(this->m_pTailNode, this->m_pHeadNode);
}

template <class ElemType, class NodeType>
void CircleListBase<ElemType, NodeType>::Clear() {
  LkListBase<ElemType, NodeType>::Clear();
  LinkTailToHead();  // 自己指向自己
}

template <class ElemType, class NodeType>
bool CircleListBase<ElemType, NodeType>::Next(ElemType& tElem) {
  if (IsEmpty()) {  // 链表若为空
    return false;
  }

  if (!this->m_pCurrNode || !this->m_pCurrNode->m_pNext) {
    return false;  // 若当前节点或其后继为空
  }

  this->m_pCurrNode = this->m_pCurrNode->m_pNext;  // 更新到下一节点
  tElem = this->m_pCurrNode->m_tData;              // 获取当前节点数据

  if (this->m_pCurrNode == this->m_pHeadNode) {
    // 若为头节点，则再更新一次
    this->m_pCurrNode = this->m_pCurrNode->m_pNext;
  }

  return true;
}

template <class ElemType, class NodeType>
bool CircleListBase<ElemType, NodeType>::Delete(int nIdx, ElemType& tElem) {
  // 调用基类的 Delete 函数
  bool bTemp = LkListBase<ElemType, NodeType>::Delete(nIdx, tElem);
  LinkTailToHead();  // 将尾结点链接到头节点
  return bTemp;      // 返回臨時變量
}

template <class ElemType, class NodeType>
bool CircleListBase<ElemType, NodeType>::Insert(int nIdx,
                                                const ElemType& tElem) {
  // 調用基類的函數
  bool bTemp = LkListBase<ElemType, NodeType>::Insert(nIdx, tElem);
  LinkTailToHead();  // 將尾節點鏈接到頭節點
  return bTemp;
}

template <class ElemType, class NodeType>
int CircleListBase<ElemType, NodeType>::AddTail(const ElemType& tElem) {
  int nIdx = LkListBase<ElemType, NodeType>::AddTail(tElem);
  LinkTailToHead();
  return nIdx;
}

template <class ElemType, class NodeType>
bool CircleListBase<ElemType, NodeType>::IsEmpty() const {
  // 头节点指针指向头节点自身
  return this->m_pHeadNode->m_pNext == this->m_pHeadNode;
}

template <class ElemType, class NodeType>
NodeType* CircleListBase<ElemType, NodeType>::GetFirstNode() const {
  if (IsEmpty()) {
    return NULL;  // 空表时返回空指针
  }

  return this->m_pHeadNode->m_pNext;  // 非空时返回首元节点
}

#endif  // CIRCLE_LIST_BASE_H_