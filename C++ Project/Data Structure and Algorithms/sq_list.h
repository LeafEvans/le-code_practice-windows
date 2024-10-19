#ifndef _SQ_LIST_H_
#define _SQ_LIST_H_
#include "list_base.h"

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
  bool SetBufferSize(int nSize);  // 内部调整缓冲区大小私有函数
  ElemType* m_pData;              // 内部数据缓冲区
  int m_nDataLen;                 // 内部存储有效数据数量
  int m_nBufferLen;               // 内部缓冲区大小
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
bool SqList<ElemType>::SetBufferSize(int nSize) {
  if (nSize <= m_nBufferLen) {
    // 若新大小比原来的小
    return true;
  }

  ElemType* pData = new ElemType[nSize];

  if (!pData) {
    // 申请失败
    return false;
  }

  if (m_pData != pData) {  // 如果新申请的和原来的地址不一致
    memcpy(pData, m_pData, sizeof(ElemType) * m_nDataLen);
    memset(pData + m_nDataLen, 0,
           sizeof(ElemType) * (m_nBufferLen - m_nDataLen));
    delete[] m_pData;
  }

  m_pData = pData;       // 赋值新的数据域
  m_nBufferLen = nSize;  // 更新大小
  return true;
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
    return -1;  // 指针为空或数据长度小于 0
  }

  // 拓宽空间
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

  int nIdx = m_nDataLen;                          // 保留索引
  memcpy(m_pData + m_nDataLen, pData, nDataLen);  // 拷贝数据
  m_nDataLen += nDataLen;                         // 数据长度增加
  return nIdx;                                    // 返回索引
}

template <class ElemType>
bool SqList<ElemType>::Insert(int nIdx, const ElemType& tElem) {
  if (nIdx < 0) {
    return false;  // 索引小於 0
  }

  if (m_nDataLen >= m_nBufferLen) {
    int nNewBufLen = m_nBufferLen;  // 更新數據長度

    if (nNewBufLen < 64) {
      nNewBufLen += 32;
    } else {
      nNewBufLen += nNewBufLen >> 1;
    }

    if (!SetBufferSize(nNewBufLen)) {
      return false;
    }
  }

  if (nIdx <= m_nDataLen - 1) {  // 若索引位於數據内部
    memmove(m_pData + nIdx + 1, m_pData + nIdx,
            sizeof(ElemType) * (m_nBufferLen - nIdx));
  } else {
    nIdx = m_nDataLen;  // 否則，在數據段末尾
  }

  m_pData[nIdx] = tElem;  // 添加新的數據
  ++m_nDataLen;           // 增加數據長度

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
  return nIdx;  // 返回索引
}

template <class ElemType>
bool SqList<ElemType>::Delete(int nIdx, ElemType& tElem) {
  if (nIdx < 0 || nIdx >= m_nDataLen) {
    return false;
  }

  tElem = m_pData[nIdx];  // 保留刪除數據

  if (nIdx < m_nDataLen - 1) {  // 位於數據內部
    memmove(m_pData + nIdx, m_pData + nIdx + 1,
            sizeof(ElemType) * (m_nBufferLen - nIdx - 1));
  }

  --m_nDataLen;  // 數據長度減少

  return true;
}

template <class ElemType>
bool SqList<ElemType>::GetElem(int nIdx, ElemType& tElem) const {
  if (nIdx < 0 || nIdx >= m_nDataLen) {
    return false;
  }

  tElem = m_pData[nIdx];  // 獲取指定數據

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

  m_pData[nIdx] = tElem;  // 設置指定元素

  if (nIdx >= m_nDataLen) {
    m_nDataLen = nIdx + 1;  // 更新數據長度
  }

  return true;
}

template <class ElemType>
void SqList<ElemType>::Traverse(bool (*pVisit)(const ElemType&)) const {
  if (!pVisit) {  // 判斷指針是否有效
    return;
  }

  for (int i = 0; i < m_nDataLen; ++i) {
    // 執行目標函數
    if (!(*pVisit)(m_pData[i])) {
      break;
    }
  }
}
#endif  // _SQ_LIST_H_