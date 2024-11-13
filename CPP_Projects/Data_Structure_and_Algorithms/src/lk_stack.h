#ifndef _LK_STACK_H_
#define _LK_STACK_H_

#include "simple_lk_list.h"

template <class ElemType>
class LkStack : private SimpleLkList<ElemType> {
 public:
  LkStack();                                // 默认构造函数
  LkStack(const LkStack<ElemType>& lsSrc);  // 拷贝构造函数
  ~LkStack();                               // 析构函数

  // 重载接口
  int Length() const;    // 获取链式栈中元素个数
  bool IsEmpty() const;  // 判断链式栈是否为空
  void Clear();          // 清空链式栈
  void Traverse(bool (*pVisit)(const ElemType& tElem)) const;  // 遍历链式栈

  // 个性化接口
  bool Push(const ElemType& tElem);  // 入栈
  bool Top(ElemType& tElem) const;   // 返回栈顶
  bool Pop(ElemType& tElem);         // 出栈
  bool Pop();                        // 出栈
};

template <class ElemType>
LkStack<ElemType>::LkStack() : SimpleLkList<ElemType>() {}

template <class ElemType>
LkStack<ElemType>::LkStack(const LkStack<ElemType>& lsSrc)
    : SimpleLkList<ElemType>(lsSrc) {}

template <class ElemType>
LkStack<ElemType>::~LkStack() {}

template <class ElemType>
int LkStack<ElemType>::Length() const {
  return SimpleLkList<ElemType>::Length();  // 调用基类函数
}

template <class ElemType>
bool LkStack<ElemType>::IsEmpty() const {
  return SimpleLkList<ElemType>::IsEmpty();  // 调用基类函数
}

template <class ElemType>
void LkStack<ElemType>::Clear() {
  SimpleLkList<ElemType>::Clear();  // 调用基类函数
}

template <typename ElemType>
void LkStack<ElemType>::Traverse(bool (*pVisit)(const ElemType& tElem)) const {
  SimpleLkList<ElemType>::Traverse(pVisit);  // 调用基类函数
}

template <class ElemType>
bool LkStack<ElemType>::Push(const ElemType& tElem) {
  if (IsEmpty()) {
    return false;  // 链表为空时，返回 false
  }

  return this->Insert(0, tElem);  // 使用头插法插入元素
}

template <class ElemType>
bool LkStack<ElemType>::Top(ElemType& tElem) const {
  if (IsEmpty()) {
    return false;  // 鏈表爲空時，返回 false
  }

  return this->GetElem(0, tElem);  // 获取栈顶元素
}

template <class ElemType>
bool LkStack<ElemType>::Pop(ElemType& tElem) {
  if (IsEmpty()) {
    return false;  // 鏈表為空時，返回 false
  }
  return this->Delete(0, tElem);  // 刪除棧頂元素
}

template <typename ElemType>
bool LkStack<ElemType>::Pop() {
  if (IsEmpty()) {
    return false;  // 鏈表爲空時，返回 false
  }
  ElemType tElem = ElemType();
  return this->Delete(0, tElem);
}

#endif  // _LK_STACK_H_
