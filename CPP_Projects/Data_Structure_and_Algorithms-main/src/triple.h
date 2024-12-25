#ifndef TRIPLE_H_
#define TRIPLE_H_

typedef union {
  unsigned int u32Key;

  struct {
#ifdef IS_BIG_ENDIAN
    // 大端模式
    unsigned short u16Row;
    unsigned short u16Col;
#else
    // 小端模式
    unsigned short u16Col;
    unsigned short u16Row;
#endif  // IS_BIG_ENDIAN
  } stPos;
} ElemPos;

template <class ElemType>
struct Triple {
  ElemPos ePos;
  ElemType tValue;

  Triple();
  Triple(int nRow, int nCol, const ElemType& tValue);
};

template <class ElemType>
Triple<ElemType>::Triple() {}

template <class ElemType>
Triple<ElemType>::Triple(int nRow, int nCol, const ElemType& tValue) {
  ePos.stPos.u16Row = nRow;
  ePos.stPos.u16Col = nCol;
  this->tValue = tValue;
}
#endif  // TRIPLE_H_
