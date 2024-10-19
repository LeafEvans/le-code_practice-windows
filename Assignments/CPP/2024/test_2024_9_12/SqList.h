#ifndef _SQLIST_H_
#define _SQLIST_H_
#include "ListBase.h"

template <class T>
class SqList : public ListBase<T> {
 public:
  SqList(int buf_size = 16);
  SqList(const SqList &other);
  ~SqList();

  int length() const;
  bool isEmpty() const;
  void clear();
  bool getElem(int pos, T &elem) const;
  bool setElem(int pos, const T &elem);
  bool delElem(int pos, T &elem);
  bool insert(int pos, const T &elem);
  void traverse(bool (*visit)(const T &)) const;
  int append(const T &elem);
  virtual SqList &operator=(const SqList<T> &src);  // 重载等于号运算符
 protected:
  int save(T *data, int data_len);  // 保存相应数据
  int setBufSize(int buf_size);     // 设置缓存区大小
  T *data_;                         // 数据
  int data_len_;                    // 数据大小
  int buf_size_;                    // 缓存区大小
};

// 默认构造函数
template <class T>
SqList<T>::SqList(int buf_size)
    : data_len_(0), buf_size_(buf_size), data_(new T[buf_size]) {
  memset(data_, 0, sizeof(T) * buf_size_);  // 设置内容为 0
}

// 析构函数
template <class T>
SqList<T>::~SqList() {
  // 指针不为空
  if (data_) {
    delete[] data_;   // 释放相应区域
    data_ = nullptr;  // 置为空指针
  }
  data_len_ = 0;  // 数据大小置为 0
  buf_size_ = 0;  // 缓存区大小置为 0
}

// 重载等于号函数
template <class T>
SqList<T> &SqList<T>::operator=(const SqList<T> &src) {
  clear();  // 设置数据大小为 0
  // 源数据数据大小大于 0
  if (src.data_len_ > 0) {
    // 进行保存操作
    save(src.data_, src.data_len_);
  }
  // 返回自身
  return *this;
}

// 拷贝构造函数
template <class T>
SqList<T>::SqList(const SqList<T> &other)
    : data_len_(0), buf_size_(other.buf_size_), data_(new T[buf_size_]) {
  // 源数据数据大小大于 0
  if (other.data_len_ > 0) {
    save(other.data_, data_len_);
  }
}

// 设置缓存区大小的函数
template <class T>
int SqList<T>::setBufSize(int buf_size) {
  // 新缓存区大小比原有缓存区大小小
  if (buf_size <= buf_size_) {
    // 返回原有缓存区大小
    return buf_size_;
  }

  // 申请新的区域
  T *new_data = new T[buf_size];
  // 将原有数据拷贝过去
  memcpy(new_data, data_, sizeof(T) * data_len_);
  memset(new_data + data_len_, 0, sizeof(T) * (buf_size - data_len_));
  // 释放原有数据区域
  delete[] data_;
  data_ = new_data;
  buf_size_ = buf_size;
  return buf_size;
}

template <class T>
int SqList<T>::length() const {
  return data_len_;
}

template <class T>
void SqList<T>::clear() {
  data_len_ = 0;
}

template <class T>
bool SqList<T>::isEmpty() const {
  return data_len_ <= 0;
}

template <class T>
int SqList<T>::save(T *data, int data_len) {
  if (!data || data_len <= 0) {
    return -1;  // 判断数据是否异常
  }

  // 新的数据大小大于等于缓存区大小
  if (data_len_ + data_len >= buf_size_) {
    // 设置新的缓存区大小
    if (!setBufSize((data_len + data_len_))) {
      return -1;
    }
  }

  // 拷贝数据到原有数据末尾
  memcpy(data_ + data_len_, data, sizeof(T) * data_len);
  data_len_ += data_len;  // 增大数据大小

  return data_len_ - data_len;  // 将数据的起始位置返回
}

template <class T>
bool SqList<T>::insert(int pos, const T &elem) {
  if (pos < 0) {  // 查看插入位置是否合理
    return false;
  }

  // 数据大小大于等于缓存区大小
  if (data_len_ >= buf_size_) {
    if (!setBufSize(data_len_ * 2)) {
      return false;
    }
  }

  // 位置相较于数据大小小
  if (pos < data_len_) {
    memmove(data_ + pos + 1, data_ + pos, sizeof(T) * (buf_size_ - pos));
  } else {
    // 位置进行更新
    pos = data_len_;
  }

  // 指定位置元素
  data_[pos] = elem;
  ++data_len_;  // 增加数据大小

  return true;
}

template <class T>
int SqList<T>::append(const T &elem) {
  if (data_len_ >= buf_size_) {  // 数据大小大于等于缓存区大小
    if (!setBufSize(data_len_ * 2)) {
      return -1;
    }
  }

  data_[data_len_] = elem;  // 新增数据到原有数据的末尾

  return data_len_++;  // 返回新增数据位置的同时增加数据大小
}

template <class T>
bool SqList<T>::getElem(int pos, T &elem) const {
  if (pos < 0 || pos >= data_len_) {
    return false;  // 位置不合理
  }

  elem = data_[pos];  // 返回指定位置的数值

  return true;
}

template <class T>
bool SqList<T>::delElem(int pos, T &elem) {
  // 位置不合理
  if (pos < 0 || pos >= data_len_) {
    return false;
  }

  // 删除元素位置在数据内部
  if (pos < data_len_ - 1) {
    // 将后面数据覆盖前面的数据
    memmove(data_ + pos, data_ + pos + 1, sizeof(T) * (buf_size_ - pos - 1));
  }

  --data_len_;  // 数据大小减小

  return true;
}

template <class T>
bool SqList<T>::setElem(int pos, const T &elem) {
  if (pos < 0) {
    return false;
  }

  if (pos >= buf_size_) {
    if (!setBufSize((pos * 2))) {
      return false;
    }
  }
  data_[pos] = elem;  // 设置指定元素

  if (pos >= data_len_) {
    data_len_ = pos + 1;
  }

  return true;
}

// 遍历线性表
template <class T>
void SqList<T>::traverse(bool (*visit)(const T &)) const {
  if (!visit) {
    return;
  }

  for (int i = 0; i < data_len_; ++i) {
    if (!(*visit)(data_[i])) {
      break;
    }
  }
}
#endif  // _SQLIST_H_
