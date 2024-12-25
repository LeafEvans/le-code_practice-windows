#ifndef LK_QUEUE_H_
#define LK_QUEUE_H_
#include "simple_lk_list.h"

template <class ElemType>
class LkQueue : private SimpleLkList<ElemType> {
 public:
  LkQueue();                                // 构造函数
  LkQueue(const LkQueue<ElemType>& lqSrc);  // 默认构造函数
  ~LkQueue();                               // 析构函数

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
LkQueue<ElemType>::LkQueue() {}

template <class ElemType>
LkQueue<ElemType>::LkQueue(const LkQueue<ElemType>& lqSrc)
    : SimpleLkList<ElemType>::SimpleLkList(lqSrc) {}

template <class ElemType>
LkQueue<ElemType>::~LkQueue() {}

template <class ElemType>
inline int LkQueue<ElemType>::Length() const {
  return SimpleLkList<ElemType>::Length();  // 调用基类函数
}

template <class ElemType>
inline bool LkQueue<ElemType>::IsEmpty() const {
  return SimpleLkList<ElemType>::IsEmpty();  // 调用基类函数
}

template <class ElemType>
inline void LkQueue<ElemType>::Clear() {
  return SimpleLkList<ElemType>::Clear();  // 调用基类函数
}

template <class ElemType>
inline void LkQueue<ElemType>::Traverse(
    bool (*pVisit)(const ElemType& tElem)) const {
  SimpleLkList<ElemType>::Traverse(pVisit);  // 调用基类函数
}

template <class ElemType>
inline bool LkQueue<ElemType>::OutQueue(ElemType& tElem) {
  if (IsEmpty()) {
    return false;  // 安全性检测
  }

  return this->Delete(0, tElem);
}

template <class ElemType>
inline bool LkQueue<ElemType>::OutQueue() {
  if (IsEmpty()) {
    return false;  // 安全性检测
  }
  return this->Delete(0, ElemType());
}

template <class ElemType>
inline bool LkQueue<ElemType>::GetHead(ElemType& tElem) const {
  if (IsEmpty()) {
    return false;  // 安全性检测
  }

  return this->GetElem(0, tElem);
}

template <class ElemType>
bool LkQueue<ElemType>::InQueue(const ElemType& tElem) {
  this->AddTail(tElem);
  return true;
}

#endif  // LK_QUEUE_H_