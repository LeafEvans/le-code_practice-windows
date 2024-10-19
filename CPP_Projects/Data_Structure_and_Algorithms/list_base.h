#ifndef _LIST_BASH_H_
#define _LIST_BASH_H_
#include <memory.h>

template<class ElemType>
class ListBase {
 public:
  virtual int Length() const = 0;    // 获取线性表元素个数
  virtual bool IsEmpty() const = 0;  // 判断线性表是否为空
  virtual void Clear() = 0;          // 清空线性表
  virtual bool GetElem(int nIdx, ElemType &tElem) const = 0;  // 获取指定位置元素
  virtual bool SetElem(int nIdx, const ElemType &tElem) = 0;  // 设置指定位置元素
  virtual bool Delete(int nIdx, ElemType &tElem) = 0;  // 删除指定位置元素
  virtual bool Insert(int nIdx, const ElemType &tElem) = 0;  // 插入指定位置元素
  // 遍历线性表
  virtual void Traverse(bool (*pVisit)(const ElemType &tElem)) const = 0;
  virtual int AddTail(const ElemType &tElem) = 0;  // 添加数据至线性表末尾
};

#endif  // _LIST_BASH_H_