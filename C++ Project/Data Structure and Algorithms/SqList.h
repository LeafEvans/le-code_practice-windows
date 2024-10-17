#ifndef _SQ_LIST_H_
#define _SQ_LIST_H_
#include "ListBase.h"

template <class ElemType>
class SqList : public ListBase<ElemType> {
 public:
  SqList(int nBufferLen = 16);              // 构造函数
  SqList(const SqList<ElemType>& slOther);  // 拷贝构造函数
  ~SqList();                                // 析构函数
  int Length() const;                       // 获取线性表中元素个数
  bool IsEmpty() const;                     // 判断线性表是否为空
  void Clear();                             // 清空线性表
  bool GetElem(int nIdx, ElemType& tElem) const;  // 获取指定位置元素
  bool SetElem(int nIdx, const ElemType& tElem);  // 设置指定元素元素
  bool Delete(int nIdx, ElemType& tElem);         // 删除指定位置元素
  bool Insert(int nIdx, const ElemType& tElem);   // 在指定位置插入元素
  void Traverse(bool (*pVisit)(const ElemType&)) const;  // 遍历线性表
  int AddTail(const ElemType& tElem);  // 添加数据到线性表末尾
  virtual SqList& operator=(const SqList<ElemType>& slSrc);  // 重载赋值运算符

 protected:
  int SaveData(ElemType* pData, int nDataLen);  // 内部存储数据私有函数
  int SetBufferSize(int nSize);  // 内部调整缓冲区大小私有函数
  ElemType* m_pData;             // 内部数据缓冲区
  int m_nDataLen;                // 内部存储有效数据数量
  int m_nBufferLen;              // 内部缓冲区大小
};

template <class ElemType>
SqList<ElemType>::SqList(int nBufferLen)
    : m_pData(new ElemType[nBufferLen]),
      m_nBufferLen(nBufferLen),
      m_nDataLen(0) {
  memset(m_pData, 0, sizeof(ElemType) * m_nBufferLen);
}

template <class ElemType>
SqList<ElemType>::~SqList() {
  if (m_pData) {
    delete[] m_pData;
    m_pData = nullptr;
  }
  m_nDataLen = 0;
  m_nBufferLen = 0;
}

template <class ElemType>
SqList<ElemType>& SqList<ElemType>::operator=(const SqList<ElemType>& slSrc) {
  Clear();
  int nDataLen = slSrc.m_nDataLen;
  ElemType* pOtherBuf = slSrc.m_pData;

  if (nDataLen) {
    // 被拷贝对象有效数据长度不为 0
    SaveData(pOtherBuf, nDataLen);  // 拷贝数据
  }

  return *this;
}

template <class ElemType>
SqList<ElemType>::SqList(const SqList<ElemType>& slOther) {
  int nDataLen = slOther.m_nDataLen;
  m_nBufferLen = slOther.m_nBufferLen;
  m_pData = new ElemType[m_nBufferLen];
  ElemType* pOtherBuf = slOther.m_pData;

  if (nDataLen > 0) {
    SaveData(pOtherBuf, nDataLen);
  }
}

template <class ElemType>
int SqList<ElemType>::SetBufferSize(int nSize) {
  if (nSize <= m_nBufferLen) {
    return m_nBufferLen;
  }

  ElemType* pData = new ElemType[nSize];
  memcpy(pData, m_pData, sizeof(ElemType) * m_nDataLen);
  memset(pData + m_nDataLen, 0, sizeof(ElemType) * (m_nBufferLen - m_nDataLen));
  delete[] m_pData;
  m_pData = pData;
  m_nBufferLen = nSize;
  return m_nBufferLen;
}

template <class ElemType>
int SqList<ElemType>::Length() const {
  return m_nDataLen;
}

template <class ElemType>
void SqList<ElemType>::Clear() {
  m_nDataLen = 0;
}

template <class ElemType>
bool SqList<ElemType>::IsEmpty() const {
  return m_nDataLen <= 0;
}

template <class ElemType>
int SqList<ElemType>::SaveData(ElemType* pData, int nDataLen) {
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
  memcpy(m_pData + m_nDataLen, pData, nDataLen);
  m_nDataLen += nDataLen;

  return nIdx;
}

template <class ElemType>
bool SqList<ElemType>::Insert(int nIdx, const ElemType& tElem) {
  if (nIdx < 0) {
    return false;
  }

  if (m_nDataLen >= m_nBufferLen) {
    int nNewBufLen = m_nBufferLen;

    if (nNewBufLen < 64) {
      nNewBufLen += 32;
    } else {
      nNewBufLen += nNewBufLen >> 1;
    }

    if (!SetBufferSize(nNewBufLen)) {
      return false;
    }
  }

  if (nIdx <= m_nDataLen - 1) {
    memmove(m_pData + nIdx + 1, m_pData + nIdx,
            sizeof(ElemType) * (m_nBufferLen - nIdx));
  } else {
    nIdx = m_nDataLen;
  }

  m_pData[nIdx] = tElem;
  ++m_nDataLen;

  return true;
}

template <class ElemType>
int SqList<ElemType>::AddTail(const ElemType& tElem) {
  if (m_nDataLen >= m_nBufferLen) {
    int nNewBufLen = m_nDataLen;
    if (nNewBufLen < 64) {
      nNewBufLen += 32;
    } else {
      nNewBufLen += nNewBufLen >> 1;
    }

    if (!SetBufferSize(nNewBufLen)) {
      return false;
    }
  }

  int nIdx = m_nDataLen;
  m_pData[nIdx] = tElem;
  ++m_nDataLen;
  return nIdx;
}

template <class ElemType>
bool SqList<ElemType>::Delete(int nIdx, ElemType& tElem) {
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
bool SqList<ElemType>::GetElem(int nIdx, ElemType& tElem) const {
  if (nIdx < 0 || nIdx >= m_nDataLen) {
    return false;
  }

  tElem = m_pData[nIdx];

  return true;
}

template <class ElemType>
bool SqList<ElemType>::SetElem(int nIdx, const ElemType& tElem) {
  if (nIdx < 0) {
    return false;
  }

  if (nIdx >= m_nBufferLen) {
    int nNewBufLen = nIdx;

    if (nNewBufLen < 64) {
      nNewBufLen += 32;
    } else {
      nNewBufLen += nNewBufLen >> 1;
    }

    if (!SetBufferSize(nNewBufLen)) {
      return false;
    }
  }

  m_pData[nIdx] = tElem;

  if (nIdx >= m_nDataLen) {
    m_nDataLen = nIdx + 1;
  }

  return true;
}

template <class ElemType>
void SqList<ElemType>::Traverse(bool (*pVisit)(const ElemType&)) const {
  if (!pVisit) {
    return;
  }

  for (int i = 0; i < m_nDataLen; ++i) {
    if (!(*pVisit)(m_pData[i])) {
      break;
    }
  }
}

#endif  // _SQ_LIST_H_