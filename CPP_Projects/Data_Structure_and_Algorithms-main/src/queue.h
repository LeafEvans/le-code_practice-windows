#ifndef QUEUE_H_
#define QUEUE_H_
#include "simple_lk_list.h"

template <class ElemType, template <class> class Base = SimpleLkList>
class Queue : private Base<ElemType> {
 public:
  Queue();                                    // 构造函数
  Queue(const Queue<ElemType, Base>& lqSrc);  // 拷贝构造函数
  ~Queue();                                   // 析构函数

  // 重载接口
  int Length() const;    // 获取链式队列中元素个数
  bool IsEmpty() const;  // 判断队列是否为空
  void Clear();          // 清空链式队列
  void Traverse(bool (*pVisit)(const ElemType& tElem)) const;  // 遍历队列

  // 个性化接口
  bool OutQueue(ElemType& tElem);       // 出队操作
  bool OutQueue();                      // 无参出队操作
  bool GetHead(ElemType& tElem) const;  // 获取队头操作
  bool InQueue(const ElemType& tElem);  // 入队操作
};

template <class ElemType, template <class> class Base>
Queue<ElemType, Base>::Queue() : Base<ElemType>() {}

template <class ElemType, template <class> class Base>
Queue<ElemType, Base>::Queue(const Queue<ElemType, Base>& lqSrc)
    : Base<ElemType>(lqSrc) {}

template <class ElemType, template <class> class Base>
Queue<ElemType, Base>::~Queue() {}

template <class ElemType, template <class> class Base>
inline int Queue<ElemType, Base>::Length() const {
  return Base<ElemType>::Length();  // 调用基类的 Length 方法
}

template <class ElemType, template <class> class Base>
inline bool Queue<ElemType, Base>::IsEmpty() const {
  return Base<ElemType>::IsEmpty();  // 调用基类的 IsEmpty 方法
}

template <class ElemType, template <class> class Base>
inline void Queue<ElemType, Base>::Clear() {
  Base<ElemType>::Clear();  // 调用基类的 Clear 方法
}

template <class ElemType, template <class> class Base>
inline void Queue<ElemType, Base>::Traverse(
    bool (*pVisit)(const ElemType& tElem)) const {
  Base<ElemType>::Traverse(pVisit);  // 调用基类的 Traverse 方法
}

template <class ElemType, template <class> class Base>
inline bool Queue<ElemType, Base>::OutQueue(ElemType& tElem) {
  if (IsEmpty()) {
    return false;  // 安全性检测
  }
  return Base<ElemType>::Delete(0, tElem);  // 删除队头元素
}

template <class ElemType, template <class> class Base>
inline bool Queue<ElemType, Base>::OutQueue() {
  if (IsEmpty()) {
    return false;  // 安全性检测
  }
  ElemType tElem = ElemType();
  return Base<ElemType>::Delete(0, tElem);  // 删除队头元素
}

template <class ElemType, template <class> class Base>
inline bool Queue<ElemType, Base>::GetHead(ElemType& tElem) const {
  if (IsEmpty()) {
    return false;  // 安全性检测
  }
  return Base<ElemType>::GetElem(0, tElem);  // 获取队头元素
}

template <class ElemType, template <class> class Base>
bool Queue<ElemType, Base>::InQueue(const ElemType& tElem) {
  Base<ElemType>::AddTail(tElem);  // 插入到队尾
  return true;
}

#endif  // QUEUE_H_
