#ifndef _LISTBASE_H_
#define _LISTBASE_H_
#include <memory.h>

template<typename T>
class ListBase {
 public:
  virtual int length() const = 0;  // 返回长度
  virtual bool isEmpty() const = 0;  // 判断是否为空
  virtual void clear() = 0;  // 清空处理
  virtual bool getElem(int pos, T &elem) const = 0;  // 获得相应元素
  virtual bool setElem(int pos, const T &elem) = 0;  // 设置相应元素
  virtual bool delElem(int pos, T &elem) = 0;  // 删除相应元素
  virtual bool insert(int pos, const T &elem) = 0;  // 插入相应元素
  virtual void traverse(bool (*visit)(const T &)) const = 0;  // 遍历线性表
  virtual int append(const T &elem) = 0;  // 添加元素至线性表末尾
};

#endif // _LISTBASE_H_
