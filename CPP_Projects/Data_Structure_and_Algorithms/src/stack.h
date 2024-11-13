#ifndef _STACK_H_
#define _STACK_H_
#include "sq_list.h"

template <class ElemType, template <class> class Base = SqList>
class Stack : private Base<ElemType> {
public:
  Stack();                                   // 默认构造函数
  Stack(const Stack<ElemType, Base> &lsSrc); // 拷贝构造函数
  ~Stack();                                  // 析构函数

  // 重载接口
  int Length() const;   // 获取栈中元素个数
  bool IsEmpty() const; // 判断栈是否为空
  void Clear();         // 清空栈
  void Traverse(bool (*pVisit)(const ElemType &tElem)) const; // 遍历栈

  // 个性化接口
  bool Push(const ElemType &tElem); // 入栈
  bool Top(ElemType &tElem) const;  // 返回栈顶
  bool Pop(ElemType &tElem);        // 出栈
  bool Pop();                       // 出栈
};

template <class ElemType, template <class> class Base>
Stack<ElemType, Base>::Stack() : Base<ElemType>() {}

template <class ElemType, template <class> class Base>
Stack<ElemType, Base>::Stack(const Stack<ElemType, Base> &lsSrc)
    : Base<ElemType>(lsSrc) {}

template <class ElemType, template <class> class Base>
Stack<ElemType, Base>::~Stack() {}

template <class ElemType, template <class> class Base>
int Stack<ElemType, Base>::Length() const {
  return Base<ElemType>::Length(); // 调用基类函数
}

template <class ElemType, template <class> class Base>
bool Stack<ElemType, Base>::IsEmpty() const {
  return Base<ElemType>::IsEmpty(); // 调用基类函数
}

template <class ElemType, template <class> class Base>
void Stack<ElemType, Base>::Clear() {
  Base<ElemType>::Clear(); // 调用基类函数
}

template <class ElemType, template <class> class Base>
void Stack<ElemType, Base>::Traverse(
    bool (*pVisit)(const ElemType &tElem)) const {
  Base<ElemType>::Traverse(pVisit); // 调用基类函数
}

template <class ElemType, template <class> class Base>
bool Stack<ElemType, Base>::Push(const ElemType &tElem) {
  return this->Insert(0, tElem); // 使用头插法插入元素
}

template <class ElemType, template <class> class Base>
bool Stack<ElemType, Base>::Top(ElemType &tElem) const {
  if (IsEmpty()) {
    return false; // 栈为空时，返回 false
  }
  return this->GetElem(0, tElem); // 获取栈顶元素
}

template <class ElemType, template <class> class Base>
bool Stack<ElemType, Base>::Pop(ElemType &tElem) {
  if (IsEmpty()) {
    return false; // 栈为空时，返回 false
  }
  return this->Delete(0, tElem); // 删除栈顶元素
}

template <class ElemType, template <class> class Base>
bool Stack<ElemType, Base>::Pop() {
  if (IsEmpty()) {
    return false; // 栈为空时，返回 false
  }
  ElemType tElem = ElemType();
  return this->Delete(0, tElem);
}

#endif // _STACK_H_
