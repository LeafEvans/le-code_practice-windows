#ifndef MIN_PRIORITY_HEAP_QUEUE_H_
#define MIN_PRIORITY_HEAP_QUEUE_H_
#include "sq_list.h"

namespace naMinPriorityHeapQueue {
const int kDefaultSize = 128;
}

template <class ElemType>
class MinPriorityHeapQueue : private SqList<ElemType> {
 protected:
  void SiftAdjust(int nLow, int nHigh);
  void BuildHeap();

 public:
  MinPriorityHeapQueue(int nBufferLen = naMinPriorityHeapQueue::kDefaultSize);
  MinPriorityHeapQueue(ElemType* arrElems, int nDataLen,
                       int nBufferLen = naMinPriorityHeapQueue::kDefaultSize);
  virtual ~MinPriorityHeapQueue();
  int Length() const;
  bool IsEmpty() const;
  void Clear();
  void Traverse(bool (*pVisit)(const ElemType&)) const;
  bool OutQueue(ElemType& tElem);
  bool InQueue(const ElemType& tElem);
  bool GetHead(ElemType& tElem) const;
  MinPriorityHeapQueue(const MinPriorityHeapQueue<ElemType>& mphqSrc);
  MinPriorityHeapQueue<ElemType>& operator=(
      const MinPriorityHeapQueue<ElemType>& mphqSrc);
};

template <class ElemType>
void MinPriorityHeapQueue<ElemType>::SiftAdjust(int nLow, int nHigh) {
  for (int i = nLow, j = 2 * nLow + 1; i <= nHigh; i = j, j = 2 * j + 1) {
    if (j < nHigh && (this->m_pData[i] > this->m_pData[i + 1])) {
      ++i;  // j 指向两个孩子中较小的
    }

    if (this->m_pData[i] <= this->m_pData[j]) {
      break;  // 已经是小根堆
    }
    std::swap(this->m_pData[i], this->m_pData[j]);  // 交换
  }
}

template <class ElemType>
void MinPriorityHeapQueue<ElemType>::BuildHeap() {
  for (int i = this->m_nDataLen / 2 - 1; i >= 0; --i) {
    SiftAdjust(i, this->m_nDataLen - 1);
  }
}


template <class ElemType>
MinPriorityHeapQueue<ElemType>::MinPriorityHeapQueue(int nBufferLen)
    : SqList<ElemType>(nBufferLen) {}

template <class ElemType>
MinPriorityHeapQueue<ElemType>::MinPriorityHeapQueue(ElemType* arrElems,
                                                     int nDataLen,
                                                     int nBufferLen)
    : SqList<ElemType>(nBufferLen) {
  if (nBufferLen < nDataLen) {
    this->Reserve(nDataLen);
  }

  for (int i = 0; i < nDataLen; ++i) {
    this->m_pData[i] = arrElems[i];
  }
  this->m_nDataLen = nDataLen;
  BuildHeap();
}

template <class ElemType>
MinPriorityHeapQueue<ElemType>::~MinPriorityHeapQueue() {}

template <class ElemType>
int MinPriorityHeapQueue<ElemType>::Length() const {
  return SqList<ElemType>::Length();
}

template <class ElemType>
bool MinPriorityHeapQueue<ElemType>::IsEmpty() const {
  return SqList<ElemType>::IsEmpty();
}

template <class ElemType>
void MinPriorityHeapQueue<ElemType>::Clear() {
  SqList<ElemType>::Clear();
}

template <class ElemType>
void MinPriorityHeapQueue<ElemType>::Traverse(
    bool (*pVisit)(const ElemType&)) const {
  SqList<ElemType>::Traverse(pVisit);
}

template <class ElemType>
bool MinPriorityHeapQueue<ElemType>::OutQueue(ElemType& tElem) {
  if (IsEmpty())
    return false;
  tElem = this->m_pData[0];
  std::swap(this->m_pData[0], this->m_pData[this->m_nDataLen - 1]);
  SiftAdjust(0, this->m_nDataLen - 2);
  --(this->m_nDataLen);
  return true;
}

template <class ElemType>
bool MinPriorityHeapQueue<ElemType>::GetHead(ElemType& tElem) const {
  if (IsEmpty())
    return false;
  tElem = this->m_pElemData[0];
  return true;
}

template <class ElemType>
bool MinPriorityHeapQueue<ElemType>::InQueue(const ElemType& tElem) {
  if (this->m_nDataLen >= this->m_nBufferLen) {
    this->Reserve(this->m_nDataLen * 2 + 1);
  }

  int nNode = this->m_nDataLen++;
  this->m_pData[nNode] = tElem;

  SiftAdjust(0, nNode);
  return true;
}

template <class ElemType>
MinPriorityHeapQueue<ElemType>::MinPriorityHeapQueue(
    const MinPriorityHeapQueue<ElemType>& mphqSrc) {
  if (&mphqSrc != this) {
    delete this->m_pData;
    this->m_nDataLen = new ElemType[mphqSrc.m_nBufferLen];
    this->m_nDataLen = mphqSrc.m_nDataLen;

    std::copy(mphqSrc.m_pData, mphqSrc.m_pData + this->m_nDataLen,
              this->m_pData);
  }
}

template <class ElemType>
MinPriorityHeapQueue<ElemType>& MinPriorityHeapQueue<ElemType>::operator=(
    const MinPriorityHeapQueue<ElemType>& mphqSrc) {
  if (&mphqSrc != this) {
    delete this->m_pData;
    this->m_nDataLen = new ElemType[mphqSrc.m_nBufferLen];
    this->m_nDataLen = mphqSrc.m_nDataLen;

    std::copy(mphqSrc.m_pData, mphqSrc.m_pData + this->m_nDataLen,
              this->m_pData);
  }
  return *this;
}
#endif  // MIN_PRIORITY_HEAP_QUEUE_H_