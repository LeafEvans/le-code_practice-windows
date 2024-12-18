#ifndef DYNAMIC_ARRAY_H_
#define DYNAMIC_ARRAY_H_
#include <algorithm>
#include <stdexcept>

namespace naDynamicArray {
const int kDefaultSize = 4;
}  // namespace naDynamicArray

template <class ElemType>
class DynamicArray {
 public:
  DynamicArray();  // 默认构造函数

#ifdef _INITIALIZER_LIST
  // 使用初始化列表构造，需要 C++11 支持
  DynamicArray(std::initializer_list<ElemType> iList);
#endif  // _INITIALIZER_LIST

  DynamicArray(const DynamicArray& tOther);  // 拷贝构造函数
  ~DynamicArray();                           // 析构函数

  bool Reserve(int nSize);      // 调整内部缓冲区大小
  int Length() const;           // 获取当前有效数据数量
  int AddTail(ElemType tElem);  // 在末尾添加元素
  int SaveData(ElemType* pData, int nDataLen);  // 批量保存数据
  int Insert(int nIdx, ElemType tElem);         // 在指定位置插入元素
  bool Delete(int nIdx, ElemType& tElem);       // 删除指定位置的元素
  const DynamicArray& operator=(const DynamicArray& tSrc);  // 赋值运算符重载
  const DynamicArray& operator+=(
      const DynamicArray& tOther);  // 加法赋值运算符重载
  ElemType& operator[](int nIdx);   // 下标运算符重载

 private:
  ElemType* m_pData;  // 数据存储区指针
  int m_nDataLen;     // 当前有效数据数量
  int m_nBufferLen;   // 当前缓冲区容量
};

// 动态数组实现代码
template <class ElemType>
DynamicArray<ElemType>::DynamicArray()
    : m_pData(new ElemType[naDynamicArray::kDefaultSize]),
      m_nBufferLen(naDynamicArray::kDefaultSize),
      m_nDataLen(0) {
  std::fill_n(m_pData, m_nBufferLen, ElemType());
}

#ifdef _INITIALIZER_LIST
// 仅在支持 C++11 标准时编译此构造函数
template <class ElemType>
DynamicArray<ElemType>::DynamicArray(std::initializer_list<ElemType> iList)
    : m_pData(new ElemType[iList.size() + naDynamicArray::kDefaultSize]),
      m_nDataLen(iList.size()),
      m_nBufferLen(m_nDataLen + naDynamicArray::kDefaultSize) {
  ElemType* pData = static_cast<ElemType*>(iList.begin());
  std::copy(pData, pData + iList.size(), m_pData);
  std::fill_n(m_pData + m_nDataLen, m_nBufferLen - m_nDataLen, ElemType());
}
#endif  // _INITIALIZER_LIST

template <class ElemType>
DynamicArray<ElemType>::DynamicArray(const DynamicArray<ElemType>& tOther)
    : m_nBufferLen(tOther.m_nBufferLen), m_pData(new ElemType[m_nBufferLen]) {
  int nDataLen = tOther.m_nDataLen;
  ElemType* pOtherBuf = tOther.m_pData;
  if (nDataLen > 0) {
    SaveData(pOtherBuf, nDataLen);
  }
}

template <class ElemType>
DynamicArray<ElemType>::~DynamicArray() {
  if (m_pData) {
    delete[] m_pData;
    m_pData = NULL;
  }
  m_nBufferLen = 0;
  m_nDataLen = 0;
}

template <class ElemType>
bool DynamicArray<ElemType>::Reserve(int nSize) {
  if (nSize <= m_nBufferLen) {
    return true;
  }

  ElemType* pNewData = new ElemType[nSize];

  if (!pNewData) {
    return false;
  }

  if (m_pData != pNewData) {
    std::copy(m_pData, m_pData + m_nDataLen, pNewData);
    std::fill_n(pNewData + m_nDataLen, m_nBufferLen - m_nDataLen, ElemType());
    delete[] m_pData;
  }

  m_pData = pNewData;
  m_nBufferLen = nSize;

  return true;
}

template <class ElemType>
int DynamicArray<ElemType>::Length() const {
  return m_nDataLen;
}

template <class ElemType>
int DynamicArray<ElemType>::AddTail(ElemType tElem) {
  // 在末尾添加元素，返回新元素的索引
  if (m_nDataLen >= m_nBufferLen) {
    int nNewBufLen = m_nDataLen;

    if (nNewBufLen < 64) {
      nNewBufLen += 32;
    } else {
      nNewBufLen += nNewBufLen >> 1;
    }

    if (!Reserve(nNewBufLen)) {
      return -1;
    }
  }

  int nIdx = m_nDataLen;
  m_pData[m_nDataLen++] = tElem;

  return nIdx;
}

template <class ElemType>
int DynamicArray<ElemType>::SaveData(ElemType* pData, int nDataLen) {
  // 批量保存数据，返回新数据的起始索引
  if (!pData || nDataLen <= 0) {
    return -1;
  }

  if (m_nDataLen + nDataLen >= m_nBufferLen) {
    int nNewBufLen = m_nDataLen + nDataLen;

    if (nNewBufLen < 64) {
      nNewBufLen += 32;
    } else {
      nNewBufLen += nNewBufLen >> 1;
    }

    if (!Reserve(nNewBufLen)) {
      return -1;
    }
  }

  int nIdx = m_nDataLen;
  std::copy(pData, pData + nDataLen, m_pData + m_nDataLen);
  m_nDataLen += nDataLen;

  return nIdx;
}

template <class ElemType>
int DynamicArray<ElemType>::Insert(int nIdx, ElemType tElem) {
  // 在指定位置插入元素，返回插入位置的索引
  if (nIdx < 0 || nIdx >= m_nBufferLen) {
    return -1;  // 索引无效
  }

  // 检查并扩展缓冲区
  if (m_nDataLen >= m_nBufferLen) {
    int nNewBufLen = m_nDataLen;

    if (nNewBufLen < 64) {
      nNewBufLen += 32;
    } else {
      nNewBufLen += nNewBufLen >> 1;
    }

    if (!Reserve(nNewBufLen)) {
      return -1;  // 缓冲区扩展失败
    }
  }

  // 插入元素
  if (nIdx < m_nDataLen) {
    std::copy_backward(m_pData + nIdx, m_pData + m_nDataLen,
                       m_pData + m_nDataLen + 1);
    m_pData[nIdx] = tElem;
    ++m_nDataLen;
  } else {
    nIdx = m_nDataLen;
    m_pData[m_nDataLen++] = tElem;
  }

  return nIdx;
}

template <class ElemType>
bool DynamicArray<ElemType>::Delete(int nIdx, ElemType& tElem) {
  // 删除指定位置的元素，并通过引用返回被删除的元素
  if (nIdx < 0 || nIdx >= m_nDataLen) {
    return false;
  }

  tElem = m_pData[nIdx];

  if (nIdx < m_nDataLen - 1) {
    std::copy(m_pData + nIdx + 1, m_pData + m_nDataLen, m_pData + nIdx);
  }
  --m_nDataLen;

  return true;
}

template <class ElemType>
const DynamicArray<ElemType>& DynamicArray<ElemType>::operator=(
    const DynamicArray<ElemType>& tSrc) {
  // 赋值运算符重载
  m_nDataLen = 0;

  ElemType* pOtherBuf = tSrc.m_pData;
  int nDataLen = tSrc.m_nDataLen;

  if (nDataLen > 0) {
    SaveData(pOtherBuf, nDataLen);
  }

  return *this;
}

template <class ElemType>
const DynamicArray<ElemType>& DynamicArray<ElemType>::operator+=(
    const DynamicArray<ElemType>& tOther) {
  // 加法赋值运算符重载，将另一个动态数组的内容追加到当前数组
  int nDataLen = tOther.m_nDataLen;
  if (nDataLen > 0) {
    ElemType* pOtherBuf = tOther.m_pData;
    SaveData(pOtherBuf, nDataLen);
  }
  return *this;
}

template <class ElemType>
ElemType& DynamicArray<ElemType>::operator[](int nIdx) {
  // 下标运算符重载，支持自动扩展数组
  if (nIdx < 0) {
    throw std::runtime_error("索引不能为负数");
  }

  if (nIdx >= m_nBufferLen) {
    int nNewBufLen = nIdx + 1;

    if (nNewBufLen < 64) {
      nNewBufLen += 32;
    } else {
      nNewBufLen += nNewBufLen >> 1;
    }

    if (!Reserve(nNewBufLen)) {
      throw std::runtime_error("内存分配失败");
    }
  }

  if (nIdx >= m_nDataLen) {
    m_nDataLen = nIdx + 1;
  }

  return m_pData[nIdx];
}

#endif  // DYNAMIC_ARRAY_H_