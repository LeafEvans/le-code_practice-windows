#ifndef _DYNAMIC_ARRAY_H_
#define _DYNAMIC_ARRAY_H_
#include <memory.h>
#include <stdexcept>

template <class ElemType>
class DynamicArray {
 public:
  DynamicArray();  // 构造函数

#ifdef _INITIALIZER_LIST_
  // 从初始化列表构造，CXX11 才支持
  DynamicArray(std::initializer_list<ElemType> iList);
#endif  // _INITIALIZER_LIST_

  DynamicArray(const DynamicArray& tOther);  // 拷贝构造函数
  ~DynamicArray();                           // 析构函数

  int SetBufferSize(int nSize);  // 设置内部缓存区大小
  int GetValidDataCount();       // 获取当前有效数据数量
  int AddTail(ElemType tElem);   // 添加数据至末尾
  int SaveData(ElemType* pData, int nDataLen);              // 存入数据
  int Insert(int nIdx, ElemType tElem);                     // 插入数据
  bool Remove(int nIdx, ElemType& tElem);                   // 删除数据
  const DynamicArray& operator=(const DynamicArray& tSrc);  // 重载 = 运算符
  const DynamicArray& operator+=(const DynamicArray& tOther);  // 重载 += 运算符
  ElemType& operator[](int nIdx);  // 重载 [] 运算符

 private:
  ElemType* m_pData;  // 内部数据缓冲区
  int m_nDataLen;     // 内部存储有效数据数量
  int m_nBufferLen;   // 内部缓冲区大小
};

// 动态数组实现代码
template <class ElemType>
DynamicArray<ElemType>::DynamicArray()
    : m_pData(new ElemType[4]), m_nBufferLen(4), m_nDataLen(0) {
  memset(m_pData, 0, sizeof(ElemType) * m_nBufferLen);
}

#ifdef _INITIALIZER_LIST_
// CXX11 标准才支持，采用条件编译；若不支持 CXX11 标准，将不编译本接口
template <class ElemType>
DynamicArray<ElemType>::DynamicArray(std::initializer_list<ElemType> iList)
    : m_nDataLen(iList.size()),
      m_nBufferLen(m_nDataLen + 4),
      m_pData(new ElemType[m_nBufferLen]) {
  ElemType* pData = (ElemType*)iList.begin();
  memcpy(m_pData, pData, sizeof(ElemType) * iList.size());
  memset(m_pData + m_nDataLen, 0,
         sizeof(ElemType) * (m_nBufferLen - m_nDataLen));
}
#endif  // _INITIALIZER_LIST_

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
    m_pData = nullptr;
  }
  m_nBufferLen = 0;
  m_nDataLen = 0;
}

template <class ElemType>
int DynamicArray<ElemType>::SetBufferSize(int nSize) {
  if (nSize <= m_nBufferLen) {
    return m_nBufferLen;
  }

  ElemType* pData = new ElemType[nSize];

  if (!pData) {
    return m_nBufferLen;
  }

  if (m_pData != pData) {
    memcpy(pData, m_pData, sizeof(ElemType) * m_nDataLen);
    memset(pData + m_nDataLen, 0,
           sizeof(ElemType) * (m_nBufferLen - m_nDataLen));
    delete[] m_pData;
  }

  m_pData = pData;
  m_nBufferLen = nSize;

  return m_nBufferLen;
}

template <class ElemType>
int DynamicArray<ElemType>::GetValidDataCount() {
  return m_nDataLen;
}

template <class ElemType>
int DynamicArray<ElemType>::AddTail(ElemType tElem) {
  // 返回追加数据所在索引
  if (m_nDataLen >= m_nBufferLen) {
    int nNewBufLen = m_nBufferLen;

    if (nNewBufLen < 64) {
      nNewBufLen += 32;
    } else {
      nNewBufLen += nNewBufLen >> 1;
    }

    if (!SetBufferSize(nNewBufLen)) {
      return -1;
    }
  }

  int nIdx = m_nDataLen;
  m_pData[m_nDataLen++] = tElem;

  return nIdx;
}

template <class ElemType>
int DynamicArray<ElemType>::SaveData(ElemType* pData, int nDataLen) {
  // 返回追加数据首地址索引
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

    if (!SetBufferSize(nNewBufLen)) {
      return -1;
    }
  }

  int nIdx = m_nDataLen;
  memcpy(m_pData + m_nDataLen, pData, sizeof(ElemType) * nDataLen);
  m_nDataLen += nDataLen;

  return nIdx;
}

template <class ElemType>
int DynamicArray<ElemType>::Insert(int nIdx, ElemType tElem) {
  // 返回插入位置索引
  if (nIdx < 0 || nIdx >= m_nBufferLen) {
    return -1;
  }

  // 检查缓冲区
  if (m_nDataLen >= m_nBufferLen) {
    int nNewBufLen = m_nBufferLen;

    if (nNewBufLen < 64) {
      nNewBufLen += 32;
    } else {
      nNewBufLen += nNewBufLen >> 1;
    }

    if (!SetBufferSize(nNewBufLen)) {
      return -1;
    }
  }

  if (nIdx < m_nDataLen) {
    memmove(m_pData + m_nDataLen + 1, m_pData + m_nDataLen,
            sizeof(ElemType) * (m_nBufferLen - m_nDataLen));
    m_pData[nIdx] = tElem;
    ++m_nDataLen;
  } else {
    nIdx = m_nDataLen;
    m_pData[m_nDataLen++] = tElem;
  }

  return nIdx;
}

template <class ElemType>
bool DynamicArray<ElemType>::Remove(int nIdx, ElemType& tElem) {
  if (nIdx < 0 || nIdx >= m_nDataLen) {
    return false;
  }

  tElem = m_pData[nIdx];

  if (nIdx < m_nDataLen - 1) {
    memmove(m_pData + nIdx, m_pData + nIdx + 1,
            sizeof(ElemType) * (m_nBufferLen - m_nDataLen - 1));
  }
  --m_nDataLen;

  return true;
}

template <class ElemType>
const DynamicArray<ElemType>& DynamicArray<ElemType>::operator=(
    const DynamicArray<ElemType>& tSrc) {
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
  ElemType* pOtherBuf = tOther.m_pData;
  int nDataLen = tOther.m_nDataLen;
  if (nDataLen > 0) {
    SaveData(pOtherBuf, nDataLen);
  }
  return *this;
}

template <class ElemType>
ElemType& DynamicArray<ElemType>::operator[](int nIdx) {
  if (nIdx < 0) {
    throw std::runtime_error("Index cannot be negative.");  // 抛出异常
  }

  if (nIdx >= m_nBufferLen) {
    int nNewBufLen = nIdx + 1;

    if (nNewBufLen < 64) {
      nNewBufLen += 32;
    } else {
      nNewBufLen += nNewBufLen >> 1;
    }

    if (!SetBufferSize(nNewBufLen)) {
      throw std::runtime_error("Failed to allocate memory.");
    }
  }

  if (nIdx >= m_nDataLen) {
    m_nDataLen = nIdx + 1;
  }

  return m_pData[nIdx];
}

#endif  // _DYNAMIC_ARRAY_H_