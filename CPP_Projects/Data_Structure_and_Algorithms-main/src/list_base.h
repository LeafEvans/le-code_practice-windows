#ifndef LIST_BASE_H_
#define LIST_BASE_H_

template <typename ElemType>
class ListBase {
 public:
  virtual ~ListBase() {}  // 虚析构函数，确保正确释放派生类资源
  virtual int Length() const = 0;    // 返回线性表中元素个数
  virtual bool IsEmpty() const = 0;  // 检查线性表是否为空
  virtual void Clear() = 0;          // 移除线性表中所有元素
  // 获取指定索引处的元素
  virtual bool GetElem(int nIdx, ElemType& tElem) const = 0;
  // 修改指定索引处的元素
  virtual bool SetElem(int nIdx, const ElemType& tElem) = 0;
  // 删除并返回指定索引处的元素
  virtual bool Delete(int nIdx, ElemType& tElem) = 0;
  // 在指定索引处插入新元素
  virtual bool Insert(int nIdx, const ElemType& tElem) = 0;
  // 使用给定函数遍历所有元素
  virtual void Traverse(bool (*pVisit)(const ElemType& tElem)) const = 0;
  // 在线性表末尾添加新元素并返回其索引
  virtual int AddTail(const ElemType& tElem) = 0;
};

#endif  // LIST_BASE_H_
