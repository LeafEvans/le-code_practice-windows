#ifndef LK_STACK_H_
#define LK_STACK_H_

#include "simple_lk_list.h"

template <class ElemType>
class LkStack : private SimpleLkList<ElemType> {
 public:
  LkStack();                                // 默认构造函数
  LkStack(const LkStack<ElemType>& lsSrc);  // 拷贝构造函数
  ~LkStack();                               // 析构函数

  // 重载接口
  int Length() const;    // 获取链式栈中元素的数量
  bool IsEmpty() const;  // 判断链式栈是否为空
  void Clear();          // 清空链式栈
  void Traverse(bool (*pVisit)(const ElemType& tElem)) const;  // 遍历链式栈

  // 个性化接口
  bool Push(const ElemType& tElem);  // 将元素入栈
  bool Top(ElemType& tElem) const;   // 获取栈顶元素
  bool Pop(ElemType& tElem);         // 弹出栈顶元素并返回
  bool Pop();                        // 弹出栈顶元素
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
  return SimpleLkList<ElemType>::Length();  // 调用基类的Length函数
}

template <class ElemType>
bool LkStack<ElemType>::IsEmpty() const {
  return SimpleLkList<ElemType>::IsEmpty();  // 调用基类的IsEmpty函数
}

template <class ElemType>
void LkStack<ElemType>::Clear() {
  SimpleLkList<ElemType>::Clear();  // 调用基类的Clear函数
}

template <typename ElemType>
void LkStack<ElemType>::Traverse(bool (*pVisit)(const ElemType& tElem)) const {
  SimpleLkList<ElemType>::Traverse(pVisit);  // 调用基类的Traverse函数
}

template <class ElemType>
bool LkStack<ElemType>::Push(const ElemType& tElem) {
  if (IsEmpty()) {
    return false;  // 如果链表为空，返回 false
  }

  return this->Insert(0, tElem);  // 使用头插法将元素插入
}

template <class ElemType>
bool LkStack<ElemType>::Top(ElemType& tElem) const {
  if (IsEmpty()) {
    return false;  // 如果链表为空，返回 false
  }

  return this->GetElem(0, tElem);  // 获取栈顶元素
}

template <class ElemType>
bool LkStack<ElemType>::Pop(ElemType& tElem) {
  if (IsEmpty()) {
    return false;  // 如果链表为空，返回 false
  }
  return this->Delete(0, tElem);  // 删除栈顶元素并返回
}

template <typename ElemType>
bool LkStack<ElemType>::Pop() {
  if (IsEmpty()) {
    return false;  // 如果链表为空，返回 false
  }
  ElemType tElem = ElemType();
  return this->Delete(0, tElem);  // 删除栈顶元素
}

#endif  // LK_STACK_H_
