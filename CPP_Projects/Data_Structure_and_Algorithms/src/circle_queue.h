#ifndef CIRCLE_QUEUE_H_
#define CIRCLE_QUEUE_H_

#include <algorithm>

namespace naCircleQueue {
const int kDefaultSize = 32;
}  // namespace naCircleQueue

template <typename ElemType>
class CircleQueue {
 public:
  // 构造函数，指定初始缓冲区大小，默认为kDefaultSize
  CircleQueue(int nBufferLen = naCircleQueue::kDefaultSize);
  CircleQueue(const CircleQueue<ElemType>& cqSrc);  // 拷贝构造函数
  ~CircleQueue();  // 析构函数，释放动态分配的内存

  int Length() const;    // 获取队列中当前元素个数
  bool IsEmpty() const;  // 判断队列是否为空
  void Clear();          // 清空队列，重置所有计数器
  // 遍历队列并对每个元素执行访问函数，如果访问函数返回false则终止遍历
  void Traverse(bool (*pVisit)(const ElemType& tElem)) const;
  bool OutQueue(ElemType& tElem);       // 出队操作，返回出队元素
  bool OutQueue();                      // 出队操作，不返回元素
  bool GetHead(ElemType& tElem) const;  // 获取队头元素，不改变队列状态
  bool InQueue(const ElemType& tElem);  // 入队操作，必要时自动扩容
                                        // 赋值运算符重载
  CircleQueue<ElemType>& operator=(const CircleQueue<ElemType>& cqSrc);
  // 批量入队，必要时自动扩容
  bool BatchInQueue(const ElemType* pDataBuf, int nDataLen);
  // 批量出队，返回实际出队元素个数
  int BatchOutQueue(ElemType* pDataBuf, int nDataLen);

 private:
  bool IsFull() const;     // 判断队列是否已满
  bool Resize(int nSize);  // 调整队列容量，仅在需要扩容时调用

  ElemType* m_pData;  // 存储元素的动态数组
  int m_nFront;       // 队头索引
  int m_nRear;        // 队尾索引（指向下一个可插入位置）
  int m_nBufferLen;   // 队列当前容量
  int m_nDataLen;     // 队列中当前元素个数
};

template <typename ElemType>
inline CircleQueue<ElemType>::CircleQueue(int nBufferLen)
    : m_pData(new ElemType[nBufferLen]),
      m_nFront(0),
      m_nRear(0),
      m_nBufferLen(nBufferLen),
      m_nDataLen(0) {}

template <typename ElemType>
inline CircleQueue<ElemType>::CircleQueue(const CircleQueue<ElemType>& cqSrc) {
  if (this != &cqSrc) {

    Clear();
    if (m_nBufferLen != cqSrc.m_nBufferLen) {
      delete[] m_pData;
      m_pData = new ElemType[cqSrc.m_nBufferLen];
      m_nBufferLen = cqSrc.m_nBufferLen;
    }
    m_nDataLen = cqSrc.m_nDataLen;
    m_nFront = cqSrc.m_nFront;
    m_nRear = cqSrc.m_nRear;
    std::copy(cqSrc.m_pData, cqSrc.m_pData + m_nBufferLen, m_pData);
  }
}

template <class ElemType>
inline CircleQueue<ElemType>::~CircleQueue() {
  delete[] m_pData;  // 释放动态分配的内存
  m_pData = NULL;
  m_nFront = m_nRear = m_nDataLen = 0;
}

template <typename ElemType>
inline int CircleQueue<ElemType>::Length() const {
  return m_nDataLen;
}

template <typename ElemType>
inline bool CircleQueue<ElemType>::IsEmpty() const {
  return m_nDataLen == 0;
}

template <typename ElemType>
inline void CircleQueue<ElemType>::Clear() {
  m_nFront = m_nRear = m_nDataLen = 0;
}

template <typename ElemType>
inline void CircleQueue<ElemType>::Traverse(
    bool (*pVisit)(const ElemType& tElem)) const {
  if (IsEmpty() || !pVisit) {
    return;
  }

  for (int i = 0, idx = m_nFront; i < m_nDataLen;
       ++i, idx = (idx + 1) % m_nBufferLen) {
    if (!(*pVisit)(m_pData[idx])) {
      break;  // 如果访问函数返回false，终止遍历
    }
  }
}

template <typename ElemType>
inline bool CircleQueue<ElemType>::OutQueue(ElemType& tElem) {
  if (IsEmpty()) {
    return false;
  }

  tElem = m_pData[m_nFront];
  m_nFront = (m_nFront + 1) % m_nBufferLen;
  --m_nDataLen;
  return true;
}

template <typename ElemType>
inline bool CircleQueue<ElemType>::OutQueue() {
  if (IsEmpty()) {
    return false;
  }

  m_nFront = (m_nFront + 1) % m_nBufferLen;
  --m_nDataLen;
  return true;
}

template <typename ElemType>
inline bool CircleQueue<ElemType>::GetHead(ElemType& tElem) const {
  if (IsEmpty()) {
    return false;
  }
  tElem = m_pData[m_nFront];
  return true;
}

template <class ElemType>
inline bool CircleQueue<ElemType>::InQueue(const ElemType& tElem) {
  if (IsFull()) {
    int nNewBufLen = m_nBufferLen * 2;
    nNewBufLen =
        (nNewBufLen < 64) ? nNewBufLen + 32 : nNewBufLen + (nNewBufLen >> 1);
    if (!Resize(nNewBufLen)) {
      return false;  // 扩容失败
    }
  }

  m_pData[m_nRear] = tElem;
  m_nRear = (m_nRear + 1) % m_nBufferLen;
  ++m_nDataLen;
  return true;
}

template <typename ElemType>
inline CircleQueue<ElemType>& CircleQueue<ElemType>::operator=(
    const CircleQueue<ElemType>& cqSrc) {
  if (this != &cqSrc) {

    Clear();
    if (m_nBufferLen != cqSrc.m_nBufferLen) {
      delete[] m_pData;
      m_pData = new ElemType[cqSrc.m_nBufferLen];
      m_nBufferLen = cqSrc.m_nBufferLen;
    }
    m_nDataLen = cqSrc.m_nDataLen;
    m_nFront = cqSrc.m_nFront;
    m_nRear = cqSrc.m_nRear;
    std::copy(cqSrc.m_pData, cqSrc.m_pData + m_nBufferLen, m_pData);
  }
  return *this;
}

template <class ElemType>
inline bool CircleQueue<ElemType>::BatchInQueue(const ElemType* pDataBuf,
                                                int nDataLen) {
  if (m_nDataLen + nDataLen > m_nBufferLen) {
    int nNewBufLen = m_nDataLen + nDataLen;
    nNewBufLen =
        (nNewBufLen < 64) ? nNewBufLen + 32 : nNewBufLen + (nNewBufLen >> 1);
    if (!Resize(nNewBufLen)) {
      return false;  // 扩容失败
    }
  }

  // 复制数据到队列
  if (m_nRear >= m_nFront && m_nRear + nDataLen > m_nBufferLen) {
    int nFirstPart = m_nBufferLen - m_nRear;
    std::copy(pDataBuf, pDataBuf + nFirstPart, m_pData + m_nRear);
    std::copy(pDataBuf + nFirstPart, pDataBuf + nDataLen, m_pData);
  } else {
    std::copy(pDataBuf, pDataBuf + nDataLen, m_pData + m_nRear);
  }

  m_nDataLen += nDataLen;
  m_nRear = (m_nRear + nDataLen) % m_nBufferLen;

  return true;
}

template <typename ElemType>
inline int CircleQueue<ElemType>::BatchOutQueue(ElemType* pDataBuf,
                                                int nDataLen) {
  int nOutLen = std::min(nDataLen, m_nDataLen);
  if (nOutLen <= 0) {
    return 0;
  }

  // 复制数据到输出缓冲区
  if (m_nFront + nOutLen > m_nBufferLen) {
    int nFirstPart = m_nBufferLen - m_nFront;
    std::copy(m_pData + m_nFront, m_pData + m_nBufferLen, pDataBuf);
    std::copy(m_pData, m_pData + (nOutLen - nFirstPart), pDataBuf + nFirstPart);
  } else {
    std::copy(m_pData + m_nFront, m_pData + m_nFront + nOutLen, pDataBuf);
  }

  m_nDataLen -= nOutLen;
  m_nFront = (m_nFront + nOutLen) % m_nBufferLen;

  return nOutLen;
}

template <typename ElemType>
inline bool CircleQueue<ElemType>::IsFull() const {
  return m_nDataLen >= m_nBufferLen;
}

template <class ElemType>
inline bool CircleQueue<ElemType>::Resize(int nSize) {
  if (nSize <= m_nBufferLen) {
    return true;
  }

  ElemType* pNewData = new ElemType[nSize];
  if (!pNewData) {
    return false;
  }

  // 复制现有数据到新缓冲区
  if (m_nDataLen > 0) {
    if (m_nFront < m_nRear) {
      std::copy(m_pData + m_nFront, m_pData + m_nRear, pNewData);
    } else {
      std::copy(m_pData + m_nFront, m_pData + m_nBufferLen, pNewData);
      std::copy(m_pData, m_pData + m_nRear,
                pNewData + (m_nBufferLen - m_nFront));
    }
  }

  delete[] m_pData;
  m_pData = pNewData;
  m_nFront = 0;
  m_nRear = m_nDataLen;
  m_nBufferLen = nSize;

  return true;
}

#endif  // CIRCLE_QUEUE_H_
