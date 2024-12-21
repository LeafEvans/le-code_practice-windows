#ifndef ARRAY_H_
#define ARRAY_H_
#include <cstdarg>
#include <stdexcept>
#include <string>

template <class ElemType>
class Array {
 public:
  Array(int nDim, ...);  // 构造函数，接受维度数和各维度的大小作为参数
  ~Array();              // 析构函数
  Array(const Array<ElemType>& arrSrc);  // 复制构造函数
  ElemType& operator()(int nSub0, ...);  // 重载括号运算符，用于访问数组元素
  ElemType* ElemAddress(int nSub0, ...) const;  // 获取指定元素的内存地址
  Array<ElemType>& operator=(const Array<ElemType>& arrSrc);  // 赋值运算符

 protected:
  int Locate(int nSub0, va_list& pvaList) const;  // 定位元素的内存位置
  ElemType* m_pData;                              // 数组数据的基地址
  int m_nDim;                                     // 数组的维度数
  int* m_pBounds;                                 // 每个维度的大小
  int* m_pConstants;  // 存储用于快速定位元素的常量数组。公式如下：
                      // C_1 = B_2 * ... * B_n
                      // C_{i-1} = C_i * B_i
};

template <class ElemType>
Array<ElemType>::Array(int nDim, ...) {
  if (nDim < 0) {
    throw std::runtime_error(
        "Invalid array dimension: Expected a positive dimension, but got " +
        std::to_string(nDim) + ".");
  }

  m_nDim = nDim;
  m_pBounds = new int[nDim];

  int nTotalElemNum = 1;
  va_list pvaList;

  va_start(pvaList, nDim);
  for (int i = 0; i < nDim; ++i) {
    m_pBounds[i] = va_arg(pvaList, int);
    nTotalElemNum *= m_pBounds[i];
  }
  va_end(pvaList);

  m_pData = new int[nTotalElemNum];

  m_pConstants = new int[nDim];

  m_pConstants[nDim - 1] = 1;

  for (int i = nDim - 2; i >= 0; --i) {
    m_pConstants[i] = m_pConstants[i + 1] * m_pBounds[i + 1];
  }
}

template <class ElemType>
Array<ElemType>::~Array() {
  if (m_pData)
    delete[] m_pData;
  if (m_pBounds)
    delete[] m_pBounds;
  if (m_pConstants)
    delete[] m_pConstants;
}

template <class ElemType>
Array<ElemType>::Array(const Array<ElemType>& arrSrc) {
  if (&arrSrc != this) {
    if (m_pData)
      delete[] m_pData;
    if (m_pBounds)
      delete[] m_pBounds;
    if (m_pConstants)
      delete[] m_pConstants;

    m_nDim = arrSrc.m_nDim;

    int nTotalElemNum = 1;

    for (int i = 0; i < m_nDim; ++i) {
      nTotalElemNum *= arrSrc.m_pBounds[i];
    }

    m_pData = new int[nTotalElemNum];
    std::copy(arrSrc.m_pData, arrSrc.m_pData + nTotalElemNum, m_pData);

    m_pBounds = new int[m_nDim];
    std::copy(arrSrc.m_pBounds, arrSrc.m_pBounds + m_nDim, m_pBounds);

    m_pConstants = new int[m_nDim];
    std::copy(arrSrc.m_pConstants, arrSrc.m_pConstants + m_nDim, m_pConstants);
  }
}

template <class ElemType>
ElemType& Array<ElemType>::operator()(int nSub0, ...) {
  va_list pvaList;
  va_start(pvaList, nSub0);
  int nIdx = Locate(nSub0, pvaList);
  va_end(pvaList);
  return *(m_pData + nIdx);
}

template <class ElemType>
ElemType* Array<ElemType>::ElemAddress(int nSub0, ...) const {
  va_list pvaList;
  va_start(pvaList, nSub0);
  int nIdx = Locate(nSub0, pvaList);
  va_end(pvaList);
  return (nIdx < 0) ? NULL : m_pData + nIdx;
}

template <class ElemType>
Array<ElemType>& Array<ElemType>::operator=(const Array<ElemType>& arrSrc) {
  if (&arrSrc != this) {
    if (m_pData)
      delete[] m_pData;
    if (m_pBounds)
      delete[] m_pBounds;
    if (m_pConstants)
      delete[] m_pConstants;

    m_nDim = arrSrc.m_nDim;

    int nTotalElemNum = 1;

    for (int i = 0; i < m_nDim; ++i) {
      nTotalElemNum *= arrSrc.m_pBounds[i];
    }

    m_pData = new int[nTotalElemNum];
    std::copy(arrSrc.m_pData, arrSrc.m_pData + nTotalElemNum, m_pData);

    m_pBounds = new int[m_nDim];
    std::copy(arrSrc.m_pBounds, arrSrc.m_pBounds + m_nDim, m_pBounds);

    m_pConstants = new int[m_nDim];
    std::copy(arrSrc.m_pBounds, arrSrc.m_pBounds + m_nDim, m_pBounds);
  }
  return *this;
}

template <typename ElemType>
int Array<ElemType>::Locate(int nSub0, va_list& pvaList) const {
  if (nSub0 < 0 || nSub0 >= m_pBounds[0]) {
    throw std::runtime_error("Out of bound in dimension 0: " +
                             std::to_string(nSub0));
  }

  int nIdx = m_pConstants[0] * nSub0;

  for (int i = 1; i < m_nDim; ++i) {
    int nSub = va_arg(pvaList, int);

    if (nSub < 0 || nSub > m_pBounds[i]) {
      throw std::runtime_error("Out of bound in dimension " +
                               std::to_string(i) + ": " + std::to_string(nSub));
    }

    nIdx += m_pConstants[i] * nSub;
  }

  return nIdx;
}
#endif  // ARRAY_H_