#ifndef _LINK_QUEUE_H_
#define _LINK_QUEUE_H_
#include "simple_circle_list.h"

template <class ElemType>
class LinkQueue : private SimpleLinkList<ElemType> {
 public:
  LinkQueue();                                  // 构造函数
  LinkQueue(const LinkQueue<ElemType>& lqSrc);  // 默认构造函数
  ~LinkQueue();                                 // 析构函数

  // 重载接口
  int Length() const;    // 获取链式队列中元素个数
  bool IsEmpty() const;  // 判断队列是否为空
  void Clear();          // 清空链式队列
  void Traverse(bool (*pVisit)(const ElemType& tElem)) const;  // 遍历队列

  // 个性化接口
  bool OutQueue(ElemType& tElem);       // 出队操作
  bool OutQueue();                      // 出队操作
  bool GetHead(ElemType& tElem) const;  // 获取队头操作
  bool InQueue(const ElemType& tElem);  // 入队操作
};

template <class ElemType>
LinkQueue<ElemType>::LinkQueue() {}

template <class ElemType>
LinkQueue<ElemType>::LinkQueue(const LinkQueue<ElemType>& lqSrc)
    : SimpleLinkList<ElemType>::SimpleLinkList(lqSrc) {}

template <class ElemType>
LinkQueue<ElemType>::~LinkQueue() {}

template <class ElemType>
inline int LinkQueue<ElemType>::Length() const {
  return SimpleLinkList<ElemType>::Length();  // 调用基类函数
}

template <class ElemType>
inline bool LinkQueue<ElemType>::IsEmpty() const {
  return SimpleLinkList<ElemType>::IsEmpty();  // 调用基类函数
}

template <class ElemType>
inline void LinkQueue<ElemType>::Clear() {
  return SimpleLinkList<ElemType>::Clear();  // 调用基类函数
}

template <class ElemType>
inline void LinkQueue<ElemType>::Traverse(
    bool (*pVisit)(const ElemType& tElem)) const {
  SimpleLinkList<ElemType>::Traverse(pVisit);  // 调用基类函数
}

template <class ElemType>
inline bool LinkQueue<ElemType>::OutQueue(ElemType& tElem) {
  if (IsEmpty()) {
    return false;  // 安全性检测
  }

  return this->Delete(0, tElem);
}

template <class ElemType>
inline bool LinkQueue<ElemType>::OutQueue() {
  if (IsEmpty()) {
    return false;  // 安全性检测
  }
  ElemType tElem = ElemType();
  return this->(0, tElem);
}

template <class ElemType>
inline bool LinkQueue<ElemType>::GetHead(ElemType& tElem) const {
  if (IsEmpty()) {
    return false;  // 安全性检测
  }

  return this->GetElem(0, tElem);
}

template <class ElemType>
bool LinkQueue<ElemType>::InQueue(const ElemType& tElem) {
  this->AddTail(tElem);
  return true;
}

#endif  // _LINK_QUEUE_H_