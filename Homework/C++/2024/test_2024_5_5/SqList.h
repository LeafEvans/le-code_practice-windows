#if !defined(_SQ_LIST_H_)
#define _SQ_LIST_H_
#include "ListBase.h"
template <class T>
class SqList : public ListBase<T> {
 public:
  SqList(int buf_size = 16);                           // 默认构造函数
  SqList(const SqList& other);                         // 拷贝构造函数
  ~SqList();                                           // 析构函数
  int length() const;                                  // 获取数据长度
  bool isEmpty() const;                                // 判断是否为空
  void clear();                                        // 清空数据
  bool getElem(int pos, T& elem) const;                // 获取元素
  bool setElem(int pos, const T& elem);                // 设置元素
  bool del(int pos, T& elem);                          // 删除元素
  bool insert(int pos, const T& elem);                 // 插入元素
  void traverse(bool (*visit)(const T&)) const;        // 遍历线性表
  int append(const T& elem);                           // 尾部添加元素
  virtual SqList& operator=(const SqList<T>& source);  // 重载等于号运算符

 protected:
  int save(T* data, int data_len);  // 保存数据
  int setBufSize(int size);         // 设置缓存区大小
  T* data_;                         // 数据
  int data_len_;                    // 数据大小
  int buf_len_;                     // 缓存区大小
};

template <class T>
SqList<T>::SqList(int buf_size) {
  data_ = new T[buf_size];                 // 申请区域
  buf_len_ = buf_size;                     // 设置缓存区大小
  data_len_ = 0;                           // 数据大小为 0
  memset(data_, 0, sizeof(T) * buf_len_);  // 数据初始化为 0
}

template <class T>
SqList<T>::~SqList() {
  if (data_) {        // 判断是否为空指针
    delete[] data_;   // 释放内存数据
    data_ = nullptr;  // 置为空指针
  }

  buf_len_ = 0;   // 缓存区大小为 0
  data_len_ = 0;  // 数据大小为 0
}

template <class T>
SqList<T>& SqList<T>::operator=(const SqList<T>& source) {
  clear();  // 将数据大小置为 0
  T* data = source.data_;
  if (source.data_len_ > 0) {     // 判断是否有数据
    save(data, source.data_len);  // 如果有就保存
  }

  return *this;
}

template <class T>
SqList<T>::SqList(const SqList<T>& other) {
  buf_len_ = other.buf_len_;
  data_ = new T[buf_len_];
  data_len_ = 0;
  if (other.data_len > 0) {             // 判断长度是否大于 0
    save(other.data_, other.data_len);  // 保存数据
  }
}

template <class T>
int SqList<T>::setBufSize(int size) {
  if (size <= buf_len_) {  // 如果新的比原来的小
    return buf_len_;
  }
  T* data = new T[size];  // 申请新的空间
  // 将原本的数据拷贝过去
  memcpy(data_, data_len_, sizeof(T) * data_len_);
  // 将缓存区的剩余部分设置为 0
  memset(data_ + data_len_, 0, (buf_len_ - data_len_) * sizeof(T));
  // 释放原本的数据区域
  delete[] data_;
  data_ = data;     // 设置新的数据区
  buf_len_ = size;  // 赋值新的数据
  return buf_len_;  // 返回缓存区大小
}

template <class T>
int SqList<T>::length() const {
  return data_len_;
}

template <class T>
bool SqList<T>::isEmpty() const {
  if (data_len_ <= 0) {
    return true;
  }
  return false;
}

template <class T>
int SqList<T>::save(T* data, int data_len) {
  if (!data || data_len <= 0) {
    return -1;  // 判断异常情况
  }

  // 判断是否超过缓存区大小
  if (data_len_ + data_len >= buf_len_) {
    // 设置新的缓存区大小
    if (!setBufSize((data_len + data_len_) * 2)) {
      return -1;
    }
  }

  // 将数据拷贝过去
  memcpy(data_ + data_len_, data, sizeof(T) * data_len);
  data_len_ += data_len;

  return data_len_ - data_len;  // 返回数据起始位置
}

template <class T>
bool SqList<T>::insert(int pos, const T& elem) {
  if (pos < 0) {
    return false;  // 判断异常情况
  }

  if (data_len_ > buf_len_) {  // 数据大小大于缓存区大小
    if (!setBufSize(data_len_ * 2)) {
      // 设置大小失败
      return false;
    }
  }

  if (pos <= data_len_ - 1) {
    // 移动数据，便于插入
    memmove(data_ + pos + 1, data_ + pos, sizeof(T) * (data_len_ - pos));
  } else {
    // 更新位置到数据末尾
    pos = data_len_;
  }

  // 更新指定位置元素
  data_[pos] = elem;
  ++data_len_;

  return true;
}

template <class T>
int SqList<T>::append(const T& elem) {
  if (data_len_ >= buf_len_) {
    if (!setBufSize(data_len_ * 2)) {
      return -1;
    }
  }

  data_[data_len_] = elem;  // 插入元素
  return data_len_++;       // 返回元素索引，进行增加
}

template <class T>
bool SqList<T>::del(int pos, T& elem) {
  if (pos < 0 || pos >= data_len_) {
    return false;
  }

  elem = data_[pos];

  if (pos < data_len_ - 1) {
    memmove(data_ + pos, data_ + pos + 1, sizeof(T) * (data_len_ - pos - 1));
  }
}

#endif  // _SQ_LIST_H_