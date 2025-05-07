#ifndef INC_SORT_H_
#define INC_SORT_H_
#include "sq_stack.h"

template <typename ElemType>
bool InsertSort(ElemType* arrElem, int nSize) {
  if (!arrElem || nSize < 1)
    return false;

  int j;
  for (int i = 1; i < nSize; ++i) {
    ElemType tElem = arrElem[i];
    for (j = i - 1; j >= 0 && arrElem[j] > tElem; --j) {
      arrElem[j + 1] = arrElem[j];
    }
    arrElem[j + 1] = tElem;
  }
  return true;
}

template <typename ElemType>
bool ShellSort(ElemType* arrElem, int nSize) {
  if (!arrElem || nSize < 1)
    return false;

  int j;
  for (int nGap = nSize / 2; nGap > 0; nGap /= 2) {
    for (int i = nGap; i < nSize; ++i) {
      ElemType tElem = arrElem[i];
      for (j = i - nGap; j >= 0 && arrElem[j] > tElem; j -= nGap) {
        arrElem[j + nGap] = arrElem[j];
      }
      arrElem[j + nGap] = tElem;
    }
  }
  return true;
}

template <typename ElemType>
bool BubbleSort(ElemType* arrElem, int nSize) {
  if (!arrElem || nSize < 1)
    return false;

  bool bFlag = true;

  for (int i = 0; i < nSize - 1 && bFlag; ++i) {
    bFlag = false;
    for (int j = i + 1; j < nSize - i - 1; ++j) {
      if (arrElem[j + 1] < arrElem[j]) {
        std::swap(arrElem[j + 1], arrElem[j]);
        bFlag = true;
      }
    }
  }
  return true;
}

/* template <typename ElemType>
int Partition(ElemType* arrElem, int nLeft, int nRight) {
  int i = nLeft - 1, j = nRight + 1;

  ElemType tPivot = arrElem[nLeft];

  while (i < j) {
    do {
      ++i;
    } while (arrElem[i] < tPivot);

    do {
      --j;
    } while (arrElem[j] > tPivot);

    if (i < j) {
      std::swap(arrElem[i], arrElem[j]);
    }
  }

  return j;
}

template <typename ElemType>
bool QuickSort(ElemType* arrElem, int nLeft, int nRight) {
  if (!arrElem)
    return false;

  if (nLeft >= nRight)
    return true;

  int i = Partition(arrElem, nLeft, nRight);

  QuickSort(arrElem, nLeft, i);
  QuickSort(arrElem, i + 1, nRight);
} */

template <typename ElemType>
int Partition(ElemType* arrElem, int nLeft, int nRight) {
  int i = nLeft - 1, j = nRight + 1;
  ElemType tPivot = arrElem[nLeft];
  while (i < j) {
    do {
      ++i;
    } while (arrElem[i] < tPivot);
    do {
      --j;
    } while (arrElem[j] > tPivot);
    if (i < j) {
      std::swap(arrElem[i], arrElem[j]);
    }
  }

  return j;
}

template <typename ElemType>
bool QuickSort(ElemType* arrElem, int nLeft, int nRight) {
  if (nLeft >= nRight)
    return true;

  int i = Partition(arrElem, nLeft, nRight);

  QuickSort(arrElem, nLeft, i);
  QuickSort(arrElem, i + 1, nRight);
}

template <typename ElemType>
bool SwapSort(ElemType* arrElem, int nSize) {
  if (!arrElem || nSize < 1)
    return false;
  for (int i = 0; i < nSize; ++i) {
    int k = i;
    for (int j = i + 1; j < nSize; ++j) {
      if (arrElem[j] < arrElem[k])
        k = j;
    }
    std::swap(arrElem[i], arrElem[k]);
  }
  return true;
}

template <typename ElemType>
bool MergeSort(ElemType* arrElem, int nLeft, int nRight) {
  if (!arrElem)
    return false;

  int nMid = (nRight - nLeft) / 2;

  MergeSort(arrElem, nLeft, nMid);
  MergeSort(arrElem, nMid + 1, nRight);

  int i = nLeft, j = nMid + 1, k = 0;
  ElemType* arrTemp = new ElemType[nRight - nLeft + 1];

  while (i < nMid && j < nRight) {
    if (arrElem[i] <= arrElem[j]) {
      arrTemp[k++] = arrElem[i++];
    } else {
      arrTemp[k++] = arrElem[j++];
    }
  }

  while (i < nMid) {
    arrTemp[k++] = arrElem[i++];
  }

  while (j < nRight) {
    arrTemp[k++] = arrElem[j++];
  }

  for (int n = nLeft, m = 0; n < nRight; ++n, ++m) {
    arrElem[n] = arrTemp[m];
  }

  delete[] arrElem;

  return true;
}
#endif  // INC_SORT_H_