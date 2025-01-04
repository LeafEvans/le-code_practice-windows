#ifndef INC_SORT_H_
#define INC_SORT_H_
#include "sq_stack.h"

template <typename ElemType>
bool InsertSort(ElemType* arrElem, int nSize) {
  if (!arrElem || nSize < 1)
    return false;

  int j;
  for (int i = 0; i < nSize; ++i) {
    ElemType tElem = arrElem[i];
    for (j = i - 1; (j >= 0 && tElem < arrElem[j]); --j) {
      arrElem[j + 1] = arrElem[j];
    }
    arrElem[j + 1] = tElem;
  }
}

template <typename ElemType>
bool ShellSort(ElemType* arrElem, int nSize) {
  if (!arrElem || nSize < 1)
    return false;
}

template <typename ElemType>
bool BubbleSort(ElemType* arrElem, int nSize) {
  if (!arrElem || nSize < 1)
    return false;

  bool bFlag = true;

  for (int i = 0; i < nSize - 1 && bFlag; ++i) {
    bFlag = false;
    for (int j = 0; j < nSize - 1 - i; ++j) {
      if (arrElem[j + 1] < arrElem[j]) {
        std::swap(arrElem[j], arrElem[j + 1]);
        bFlag = true;
      }
    }
  }

  return true;
}


#endif  // INC_SORT_H_