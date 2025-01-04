#include <cstddef>
#include <cstdio>
#include <iostream>

template <class ElemType, class KeyType>
int SqSearch(const ElemType* arrElem, size_t nSize, KeyType tKey) {
  for (size_t i = 0; i < nSize; ++i) {
    if (arrElem[i] == tKey)
      return i;
  }
  return -1;
}

template <class ElemType, class KeyType>
int BinSearch(ElemType* arrElem, size_t nSize, KeyType tKey) {
  size_t nLow = 0, nHigh = nSize - 1;
  while (nLow <= nHigh) {
    size_t nMid = nLow + (nHigh - nLow) / 2;
    if (arrElem[nMid] == tKey) {
      return nMid;
    } else if (tKey < arrElem[nMid]) {
      nHigh = nMid - 1;
    } else {
      nLow = nMid + 1;
    }
  }
  return -1;
}

int main() {
  printf("Hello, World!\n");
  for (int i = 0; i < 10; ++i) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
  return 0;
}