#ifndef _CIRCLE_LIST_BASH_H_
#define _CIRCLE_LIST_BASH_H_
#include "LinkListBase.h"

template <class ElemType, class NodeType>
class CircleListBase : public LinkListBase<ElemType, NodeType> {
 public:
  CircleListBase();                              // 构造函数
  ~CircleListBase();                             // 析构函数
  CircleListBase(const CircleListBase &clbSrc);  // 拷贝构造函数

  // 添加将尾节点连接到头节点的操作
  virtual bool Delete(int nIdx, ElemType &tElem);  // 重载删除指定位置元素
  virtual bool Insert(int nIdx, const ElemType &tElem);  // 重载指定位置插入元素
  virtual int AddTail(const ElemType &tElem);  // 重载添加数据添加到链表末尾
  virtual bool IsEmpty() const;                // 判断线性表是否为空
  virtual CircleListBase &operator=(
      const CircleListBase<ElemType, NodeType> &clbSrc);  // 重载赋值运算符
  virtual void Clear();                                   // 清空线性表
  virtual bool Next(ElemType &tElem);  // 当前节点后移，同时获取后继数据

 protected:
  virtual NodeType *GetFirstNode() const;  // 获取首元节点
  virtual void LinkTailToHead();           // 链接尾节点与头节点
};

template <class ElemType, class NodeType>
CircleListBase<ElemType, NodeType>::CircleListBase() {}

template <class ElemType, class NodeType>
CircleListBase<ElemType, NodeType>::CircleListBase(
    const CircleListBase &clbSrc) {
  *this = clbSrc;  // 使用重写的赋值运算符
}

template <class ElemType, class NodeType>
CircleListBase<ElemType, NodeType>::~CircleListBase() {}

template <class ElemType, class NodeType>
CircleListBase<ElemType, NodeType> &
CircleListBase<ElemType, NodeType>::operator=(
    const CircleListBase<ElemType, NodeType> &clbSrc) {
  LinkListBase<ElemType, NodeType>::operator=(clbSrc);
  LinkTailToHead();  // 在原有基础上，将尾节点链接到头节点上
  return *this;
}

template <class ElemType, class NodeType>
void CircleListBase<ElemType, NodeType>::LinkTailToHead() {
  this->Link(this->m_pNodeTail, this->m_pNodeHead);
}

template <class ElemType, class NodeType>
void CircleListBase<ElemType, NodeType>::Clear() {
  LinkListBase<ElemType, NodeType>::Clear();
  LinkTailToHead();  // 自己指向自己
}

template <class ElemType, class NodeType>
bool CircleListBase<ElemType, NodeType>::Next(ElemType &tElem) {
  if (IsEmpty()) {  // 链表若为空
    return false;
  }

  if (!this->m_pNodeCur || !this->m_pNodeCur->m_pNext) {
    return false;  // 链表当前节点为空或下一节点为空
  }
  // 更新为下一节点
  this->m_pNodeCur = this->m_pNodeCur->m_pNext;

  // 若下一节点为头节点
  if (this->m_pNodeCur == this->m_pNodeHead) {
    // 继续指向下一个节点
    this->m_pNodeCur = this->m_pNodeCur->m_pNext;
  }

  tElem = this->m_pNodeCur->m_tElem;

  return true;
}

template <class ElemType, class NodeType>
bool CircleListBase<ElemType, NodeType>::Delete(int nIdx, ElemType &tElem) {
  bool bTemp = LinkListBase<ElemType, NodeType>::Delete(nIdx, tElem);
  LinkTailToHead();
  return bTemp;
}

template <class ElemType, class NodeType>
bool CircleListBase<ElemType, NodeType>::Insert(int nIdx,
                                                const ElemType &tElem) {
  bool bTemp = LinkListBase<ElemType, NodeType>::Insert(nIdx, tElem);
  LinkTailToHead();
  return bTemp;
}

template <class ElemType, class NodeType>
int CircleListBase<ElemType, NodeType>::AddTail(const ElemType &tElem) {
  int nIdx = LinkListBase<ElemType, NodeType>::AddTail(tElem);
  LinkTailToHead();
  return nIdx;
}

template <class ElemType, class NodeType>
bool CircleListBase<ElemType, NodeType>::IsEmpty() const {
  // 头节点指针指向头节点自身
  return this->m_pNodeHead->m_pNext == this->m_pNodeHead;
}

template <class ElemType, class NodeType>
NodeType *CircleListBase<ElemType, NodeType>::GetFirstNode() const {
  if (IsEmpty()) {
    return nullptr;  // 空表时返回空指针
  }

  return this->m_pNodeHead->m_pNext;  // 非空时返回首元节点
}

#endif  // _CIRCLE_LIST_BASH_H_