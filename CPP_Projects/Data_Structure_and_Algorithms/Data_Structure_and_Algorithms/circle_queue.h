#ifndef _CIRCLE_QUEUE_H_
#define _CIRCLE_QUEUE_H_
#include <algorithm>

const int kDefaultSize = 32;  //

template <typename ElemType>
class CircleQueue {
 public:
  CircleQueue(int nBufferLen = kDefaultSize);      // 默认构造函数
  CircleQueue(const CircleQueue<ElemType>& cqSrc);  // 拷贝构造函数
  ~CircleQueue();                                   // 析构函数

  int Length() const;    // 获取链式队列中元素个数
  bool IsEmpty() const;  // 判断链式队列是否为空
  void Clear();          // 清空鏈式隊列
  void Traverse(bool (*pVisit)(const ElemType& tElem)) const;  // 遍歷鏈式隊列
  bool OutQueue(ElemType& tElem);                              // 出隊操作
  bool OutQueue();                                             // 出隊操作
  bool GetHead(ElemType& tElem) const;  // 獲取隊頭操作
  bool InQueue(const ElemType& tElem);  // 入隊操作
  CircleQueue<ElemType>& operator=(
      const CircleQueue<ElemType>& cqSrc);  // 重載赋值運算符
  bool BatchInQueue(const ElemType* pDataBuf, int nDataLen);  // 批次入隊
  int BatchOutQueue(ElemType* pDataBuf, int nDataLen);        // 批次出隊

 private:
  bool IsFull() const;     // 是否隊滿
  bool Resize(int nSize);  // 重新分配緩存区大小

  ElemType* m_pData;  // 元素存儲區域
  int m_nFront;       // 队头索引
  int m_nRear;        // 队尾索引
  int m_nBufferLen;   // 隊列最大元素個數
  int m_nDataLen;     // 元素個數
};

template <typename ElemType>
inline CircleQueue<ElemType>::CircleQueue(int nBufferLen)
    : m_pData(new ElemType[kDefaultSize]),
      m_nFront(0),
      m_nRear(0),
      m_nBufferLen(kDefaultSize),
      m_nDataLen(0) {}

template <typename ElemType>
inline CircleQueue<ElemType>::CircleQueue(const CircleQueue<ElemType>& cqSrc) {
  *this = cqSrc;  // 直接使用赋值运算符
}

template <class ElemType>
inline CircleQueue<ElemType>::~CircleQueue() {
  if (m_pData) {        // 若指針不爲空
    delete[] m_pData;   // 釋放 m_pData 指向的空間
    m_pData = NULL;  // 將指針置爲空
  }

  // 隊頭、隊尾以及數據大小置爲 0
  m_nFront = m_nRear = m_nDataLen = 0;
}

template <typename ElemType>
inline int CircleQueue<ElemType>::Length() const {
  return m_nDataLen;  // 返回數據大小
}

template <typename ElemType>
inline bool CircleQueue<ElemType>::IsEmpty() const {
  return m_nDataLen == 0;  // 若爲 0 時，返回
}

template <typename ElemType>
inline void CircleQueue<ElemType>::Clear() {
  // 將隊頭、隊尾和數據大小置爲 0
  m_nFront = m_nRear = m_nDataLen = 0;
}

template <typename ElemType>
inline void CircleQueue<ElemType>::Traverse(
    bool (*pVisit)(const ElemType& tElem)) const {
  if (IsEmpty() || !pVisit) {
    return;  // 循環隊列爲空或指針為空
  }

  int nCounts = 0;  // 計數器

  // nIdx 為索引，通過相關迭代公式保持合理性
  for (int nIdx = 0; nCounts < m_nDataLen;
       ++nCounts, nIdx = (nIdx + 1) % m_nBufferLen) {
    (*pVisit)(m_pData[nIdx]);
  }
}

template <typename ElemType>
inline bool CircleQueue<ElemType>::OutQueue(ElemType& tElem) {
  if (IsEmpty()) {
    return false;  // 保護性檢查
  }

  tElem = m_pData[m_nFront];                 // 獲取隊頭元素
  m_nFront = (m_nFront + 1) % m_nBufferLen;  // 更新队头元素位置
  --m_nDataLen;                              // 元素数量减少
  return true;
}

template <typename ElemType>
inline bool CircleQueue<ElemType>::OutQueue() {
  if (IsEmpty()) {
    return false;  // 安全性检查
  }

  m_nFront = (m_nFront + 1) % m_nBufferLen;  // 获取队头元素
  --m_nDataLen;                              // 元素数量减少
  return true;
}

template <typename ElemType>
inline bool CircleQueue<ElemType>::GetHead(ElemType& tElem) const {
  if (IsEmpty()) {
    return false;  // 安全性检查
  }
  tElem = m_pData[m_nFront];  // 获取队头元素
  return true;
}

template <class ElemType>
inline bool CircleQueue<ElemType>::InQueue(const ElemType& tElem) {
  if (IsFull()) {  // 判断是否队满
    // 更新大小
    int nNewBufLen = m_nBufferLen * 2;

    if (nNewBufLen < 64) {
      nNewBufLen += 32;
    } else {
      nNewBufLen += nNewBufLen >> 1;
    }

    if (!Resize(nNewBufLen)) {
      return false;  // 分配空间失败
    }
  }

  m_pData[m_nRear] = tElem;                // 更新队头元素
  m_nRear = (m_nRear + 1) % m_nBufferLen;  // 更新队尾索引
  ++m_nDataLen;                            // 元素数量增加
  return true;
}

template <typename ElemType>
inline CircleQueue<ElemType>& CircleQueue<ElemType>::operator=(
    const CircleQueue<ElemType>& cqSrc) {
  Clear();  // q清空环型队列

  if (m_pData) {
    delete[] m_pData;  // 删除数值域
  }

  ElemType* pSrcData = cqSrc.m_pData;  // 源数据

  m_nBufferLen = cqSrc.m_nBufferLen;     // 更新缓冲区大小
  m_nDataLen = cqSrc.m_nDataLen;         // 更新数据大小
  m_pData = new ElemType[m_nBufferLen];  // 更新数据区域
  m_nFront = 0;                          // 更新队头
  m_nRear = cqSrc.m_nDataLen;            // 更新队尾

  std::copy(pSrcData, pSrcData + m_nBufferLen, m_pData);  // 拷贝数据

  return *this;
}

template <class ElemType>
inline bool CircleQueue<ElemType>::BatchInQueue(const ElemType* pDataBuf,
                                                int nDataLen) {
  if (m_nDataLen + nDataLen > m_nBufferLen) {
    // 缓冲区过小重新分配内存
    int nNewBufLen = m_nDataLen + nDataLen;

    if (nNewBufLen < 64) {
      nNewBufLen += 32;
    } else {
      nNewBufLen += nNewBufLen >> 1;
    }

    if (!Resize(nNewBufLen)) {
      return false;  // 分配失败
    }
  }

  if (m_nRear >= m_nFront && m_nRear + nDataLen > m_nBufferLen) {
    // 队尾索引大于队头索引且队尾至缓冲区末尾的空间不足
    int nCopyLen = m_nBufferLen - m_nRear;  // 队尾至缓冲区尾部空间

    // 拷贝部分数据从队尾至缓冲区尾部
    std::copy(pDataBuf, pDataBuf + nCopyLen, m_pData + m_nRear);
    // 将剩余数据从缓冲区头部开始拷贝
    std::copy(pDataBuf + nCopyLen, pDataBuf + nDataLen, m_pData);
  } else {
    // 直接从队尾开始拷贝
    std::copy(pDataBuf, pDataBuf + nDataLen, m_pData + m_nRear);
  }

  m_nDataLen += nDataLen;                         // 增加数据长度
  m_nRear = (m_nRear + nDataLen) % m_nBufferLen;  // 更新队尾指针

  return bool;
}

template <typename ElemType>
inline int CircleQueue<ElemType>::BatchOutQueue(ElemType* pDataBuf,
                                                int nDataLen) {
  int nOutLen = nDataLen;

  if (nOutLen <= 0) {
    return 0;  // 无效数据量
  }

  if (nOutLen > m_nDataLen) {
    nOutLen = m_nDataLen;  // 目标数据量大于队列中的数据量，更新目标数据量
  }

  if (m_nFront >= m_nRear && m_nFront + nOutLen > m_nBufferLen) {
    int nCopyLen = m_nBufferLen - m_nFront;  // 队头至缓冲区尾部可用空间
    // 先拷贝队头至缓冲区尾部的部分数据
    std::copy(m_pData + m_nFront, m_pData + m_nBufferLen, pDataBuf);
    // 后拷贝缓冲区头部至队尾的数据
    std::copy(m_pData, m_pData + (nOutLen - nCopyLen), pDataBuf + nCopyLen);
  } else {
    // 数据是连续的，直接从队列前部复制
    std::copy(m_pData + m_nFront, m_pData + m_nFront + nOutLen, pDataBuf);
  }

  m_nDataLen -= nOutLen;  // 更新队列中剩余的数据量
  m_nFront = (m_nFront + nOutLen) % m_nBufferLen;  // 更新队头指针位置

  return nOutLen;  // 返回实际取出的数据量
}

template <typename ElemType>
inline bool CircleQueue<ElemType>::IsFull() const {
  return m_nDataLen >= m_nBufferLen;
}

template <class ElemType>
inline bool CircleQueue<ElemType>::Resize(int nSize) {
  if (nSize <= m_nBufferLen) {
    return true;  // 更新大小小于原有大小
  }

  ElemType* pNewData = new ElemType[nSize];

  if (!pNewData) {
    return false;  // 申请失败
  }

  if (m_nDataLen > 0) {
    // 存放数据时进行拷贝操作
    if (m_nFront >= m_nRear) {
      // 若队头索引大于队尾索引
      std::copy(m_pData + m_nFront, m_pData + m_nBufferLen, pNewData);
      std::copy(m_pData, m_pData + m_nRear, pNewData + m_nBufferLen - m_nFront);
    } else {
      // 直接拷贝
      std::copy(m_pData + m_nFront, m_pData + m_nRear, pNewData);
    }
  }

  delete[] m_pData;      // 释放数据区域
  m_pData = pNewData;    // 更新指标指向
  m_nFront = 0;          // 更新队头索引
  m_nRear = m_nDataLen;  // 更新队尾索引
  m_nBufferLen = nSize;  // 更新缓冲区大小

  return true;
}
#endif  // _CIRCLE_QUEUE_H_