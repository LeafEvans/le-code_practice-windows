#ifndef SQ_STACK_H_
#define SQ_STACK_H_
#include "sq_list.h"

namespace naSqStack {
const int kDefaultSize = 32;
};  // namespace naSqStack

template <class ElemType>
class SqStack : private SqList<ElemType> {
 public:
  SqStack(int nBufferLen = naSqStack::kDefaultSize);  // 默认构造函数
  SqStack(const SqStack<ElemType>& ssSrc);            // 拷贝构造函数
  ~SqStack();                                         // 析构函数

  // 重载接口
  int Length() const;    // 获取顺序栈中元素个数
  bool IsEmpty() const;  // 判断顺序栈是否为空
  void Clear();          // 清空顺序栈
  void Traverse(bool (*pVisit)(const ElemType&)) const;

  // 个性化接口
  bool Push(const ElemType& tElem);  // 入栈
  bool Top(ElemType& tElem) const;   // 栈顶元素
  bool Pop(ElemType& tElem);         // 出栈
  bool Pop();                        // 出栈
};

template <class ElemType>
SqStack<ElemType>::SqStack(int nBufferLen) : SqList<ElemType>(nBufferLen) {}

template <class ElemType>
SqStack<ElemType>::SqStack(const SqStack<ElemType>& ssSrc)
    : SqList<ElemType>(ssSrc) {}

template <class ElemType>
SqStack<ElemType>::~SqStack() {}

template <class ElemType>
int SqStack<ElemType>::Length() const {
  return SqList<ElemType>::Length();  // 调用基类函数
}

template <class ElemType>
bool SqStack<ElemType>::IsEmpty() const {
  return SqList<ElemType>::IsEmpty();  // 调用基类函数
}

template <class ElemType>
void SqStack<ElemType>::Clear() {
  SqList<ElemType>::Clear();  // 调用基类函数
}

template <class ElemType>
void SqStack<ElemType>::Traverse(bool (*pVisit)(const ElemType&)) const {
  SqList<ElemType>::Traverse(pVisit);  // 调用基类函数
}

template <class ElemType>
bool SqStack<ElemType>::Push(const ElemType& tElem) {
  this->AddTail(tElem);  // 调用基类添加到表末尾方法
  return true;
}

template <class ElemType>
bool SqStack<ElemType>::Top(ElemType& tElem) const {
  int nCounts = Length();

  if (IsEmpty()) {
    return false;
  }

  return this->GetElem(nCounts - 1, tElem);  // 调用基类函数
}

template <class ElemType>
bool SqStack<ElemType>::Pop(ElemType& tElem) {
  int nCounts = Length();  // 获取数量大小

  if (IsEmpty()) {  // 若栈为空
    return false;
  }

  return this->Delete(nCounts - 1, tElem);  // 删除栈顶元素
}

template <class ElemType>
bool SqStack<ElemType>::Pop() {
  int nCounts = Length();

  if (IsEmpty()) {
    return false;
  }

  ElemType tElem = ElemType();

  return this->Delete(nCounts - 1, tElem);
}
#endif  // SQ_STACK_H_
