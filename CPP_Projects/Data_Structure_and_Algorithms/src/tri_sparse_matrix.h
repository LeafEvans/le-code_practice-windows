#ifndef TRI_SPARSE_MATRIX_H_
#define TRI_SPARSE_MATRIX_H_
#include <memory.h>

#include "matrix.h"
#include "sq_list.h"
#include "triple.h"

// 稀疏矩阵三元组顺序表模板
template <class ElemType>
class TriSparseMatrix : public SqList<Triple<ElemType>> {
 public:
  // 默认构造函数
  TriSparseMatrix(int nRows, int nCols, int nSize = 32);
  // 由稀疏矩阵拷贝构造函数
  TriSparseMatrix(const TriSparseMatrix<ElemType>& tsmSrc);
  TriSparseMatrix(const Matrix<ElemType>& mtxSrc);  // 由普通矩阵拷贝构造函数
  ~TriSparseMatrix();                               // 析构函数
  int GetRows() const;                              // 获取矩阵的行数
  int GetCols() const;                              // 获取矩阵的列数
  int GetNonZero() const;                           // 得到非零元素
  bool SetElem(int nRow, int nCol, const ElemType& tValue);  // 设置指定元素
  bool GetElem(int nRow, int nCol, ElemType& tValue);  // 得到指定元素
  Matrix<ElemType> ToMatrix() const;                   // 输出矩阵
  TriSparseMatrix<ElemType>& operator=(const TriSparseMatrix<ElemType>& tsmSrc);
  TriSparseMatrix<ElemType>& operator=(const Matrix<ElemType>& mtxSrc);
  TriSparseMatrix<ElemType> SimpleTranspose() const;  // 简单转置
  TriSparseMatrix<ElemType> FastTranspose() const;    // 快速转置

 private:
  int Locate(int nRow, int nCol, bool& bFound);  // 获取位置函数
  int m_nRows;                                   // 行数
  int m_nCols;                                   // 列数
};

template <class ElemType>
TriSparseMatrix<ElemType>::TriSparseMatrix(int nRows, int nCols, int nSize)
    : SqList<Triple<ElemType>>(nSize), m_nRows(nRows), m_nCols(nCols) {}

template <class ElemType>
TriSparseMatrix<ElemType>::TriSparseMatrix(
    const TriSparseMatrix<ElemType>& tsmSrc) {
  this->Clear();
  this->SaveData(tsmSrc.m_pData, tsmSrc.Length());
  m_nRows = tsmSrc.m_nRows;
  m_nCols = tsmSrc.m_nCols;
}

template <class ElemType>
TriSparseMatrix<ElemType>::TriSparseMatrix(const Matrix<ElemType>& mtxSrc) {
  this->Clear();
  m_nRows = mtxSrc.m_nRows;
  m_nCols = mtxSrc.m_nCols;

  for (int i = 0; i < m_nRows; ++i) {
    for (int j = 0; j < m_nCols; ++j) {
      if (mtxSrc(i, j) != 0) {
        this->AddTail(Triple<ElemType>(i, j, mtxSrc(i, j)));
      }
    }
  }
}

template <class ElemType>
TriSparseMatrix<ElemType>::~TriSparseMatrix() {}

template <class ElemType>
int TriSparseMatrix<ElemType>::GetRows() const {
  return m_nRows;
}

template <class ElemType>
int TriSparseMatrix<ElemType>::GetCols() const {
  return m_nCols;
}

template <class ElemType>
int TriSparseMatrix<ElemType>::GetNonZero() const {
  return this->Length();
}
template <class ElemType>
bool TriSparseMatrix<ElemType>::SetElem(int nRow, int nCol,
                                        const ElemType& tValue) {
  if (nRow < 0 || nCol < 0 || nRow >= m_nRows || nCol >= m_nCols)
    return false;

  bool bFound = false;

  int nIdx = Locate(nRow, nCol, bFound);

  if (nIdx < 0)
    return false;

  if (!bFound && tValue != 0) {
    this->Insert(nIdx, Triple<ElemType>(nRow, nCol, tValue));
  } else if (bFound && tValue == 0) {
    this->Delete(nIdx, Triple<ElemType>());
  } else if (bFound && tValue != 0) {
    this->m_pData[nIdx] = tValue;
  }

  return true;
}

template <class ElemType>
bool TriSparseMatrix<ElemType>::GetElem(int nRow, int nCol, ElemType& tValue) {
  if (nRow < 0 || nCol < 0 || nRow >= m_nRows || nCol >= m_nCols)
    return false;

  bool bFound = false;

  int nIdx = Locate(nRow, nCol, bFound);

  if (nIdx < 0)
    return false;

  if (!bFound) {
    tValue = 0;
  } else {
    tValue = this->m_pData[nIdx].tValue;
  }

  return true;
}

template <class ElemType>
TriSparseMatrix<ElemType>& TriSparseMatrix<ElemType>::operator=(
    const TriSparseMatrix<ElemType>& tsmSrc) {
  this->Clear();
  this->SaveData(tsmSrc.m_pData, tsmSrc.Length());
  m_nRows = tsmSrc.m_nRows;
  m_nCols = tsmSrc.m_nCols;
  return *this;
}

template <class ElemType>
TriSparseMatrix<ElemType>& TriSparseMatrix<ElemType>::operator=(
    const Matrix<ElemType>& mtxSrc) {
  this->Clear();
  m_nRows = mtxSrc.GetRows();
  m_nCols = mtxSrc.GetCols();

  for (int i = 0; i < m_nRows; ++i) {
    for (int j = 0; j < m_nCols; ++j) {
      if (mtxSrc(i, j) != 0) {
        this->AddTail(Triple<ElemType>(i, j, mtxSrc(i, j)));
      }
    }
  }

  return *this;
}

template <class ElemType>
Matrix<ElemType> TriSparseMatrix<ElemType>::ToMatrix() const {
  Matrix<ElemType> mtxRes;

  ElemType* pMtxData = mtxRes.m_pData;

  std::fill(pMtxData, pMtxData + m_nRows + m_nCols, 0);

  int nNonZero = GetNonZero();

  for (int k = 0; k < nNonZero; ++k) {
    const Triple<ElemType>& triElem = (this->m_pData)[k];
    int nRow = triElem.ePos.stPos.u16Row;
    int nCol = triElem.ePos.stPos.u16Col;
    ElemType tValue = triElem.tValue;
    mtxRes(nRow, nCol) = tValue;
  }

  return mtxRes;
}

template <class ElemType>
TriSparseMatrix<ElemType> TriSparseMatrix<ElemType>::SimpleTranspose() const {
  int nCols = GetCols();
  int nRows = GetRows();
  int nNonZero = GetNonZero();

  TriSparseMatrix<ElemType> tsmRes(nCols, nRows, nNonZero + 8);

  for (int k = 0; k < nNonZero; ++k) {
    const Triple<ElemType> triElem = (this->m_pData)[k];
    int nRow = triElem.ePos.stPos.u16Row;
    int nCol = triElem.ePos.stPos.u16Col;
    ElemType tValue = triElem.tValue;
    tsmRes.SetElem(nCol, nRow, tValue);
  }

  return tsmRes;
}

template <class ElemType>
TriSparseMatrix<ElemType> TriSparseMatrix<ElemType>::FastTranspose() const {
  int nRows = GetRows();
  int nCols = GetCols();
  int nNonZero = GetNonZero();

  TriSparseMatrix<ElemType> tsmRes(nCols, nRows, nNonZero + 8);
  tsmRes.m_nDataLen = nNonZero;

  // 存储每列非零元素个数，初始化为 0
  int* pColCounts = new int[nCols]();
  // 存储每列的首个元素的存储位置，初始化为 0
  int* pColPositions = new int[nCols]();

  // 统计每列的非零元素个数
  for (int k = 0; k < nNonZero; ++k) {
    int nCol = (this->m_pData)[k].ePos.stPos.u16Col;
    ++pColCounts[nCol];
  }

  // 计算每一列首个非零元素的位置
  int nSum = 0;
  for (int j = 0; j < nNonZero; ++j) {
    pColPositions[j] = nSum;
    nSum += pColCounts[j];
  }

  for (int k = 0; k < nNonZero; ++k) {
    const Triple<ElemType>& triElem = (this->m_pData)[k];
    int nRow = triElem.ePos.stPos.u16Row;
    int nCol = triElem.ePos.stPos.u16Col;
    int nDesPos = pColPositions[nCol];
    ElemType tValue = triElem.tValue;

    tsmRes.m_pData[nDesPos].ePos.stPos.u16Row = nRow;
    tsmRes.m_pData[nDesPos].ePos.stPos.u16Col = nCol;
    tsmRes.m_pData[nDesPos].tValue = tValue;

    ++pColPositions[nCol];
  }

  return tsmRes;
}

template <class ElemType>
int TriSparseMatrix<ElemType>::Locate(int nRow, int nCol, bool& bFound) {
  bFound = false;

  if (nRow < 0 || nCol < 0 || nRow >= m_nRows || nCol >= m_nCols)
    return -1;

  int nSearchStart = 0;
  int nSearchEnd = GetNonZero() - 1;

  ElemPos ePos;
  ePos.stPos.u16Row = nRow;
  ePos.stPos.u16Col = nCol;

  if (ePos.u32Key < this->m_pData[nSearchStart].ePos.u32Key)
    return 0;
  if (ePos.u32Key > this->m_pData[nSearchEnd].ePos.u32Key) {
    return nSearchEnd + 1;
  }

  int nIdx = -1;

  while (nSearchEnd - nSearchStart > 1) {
    int nMidPos = (nSearchStart + nSearchEnd) >> 1;

    if (ePos.u32Key < this->m_pData[nMidPos].ePos.u32Key) {
      nSearchEnd = nMidPos;
    } else if (ePos.u32Key > this->m_pData[nMidPos].ePos.u32Key) {
      nSearchStart = nMidPos;
    } else {
      nIdx = nMidPos;
      bFound = true;
      break;
    }
  }

  if (!bFound) {
    if (ePos.u32Key == this->m_pData[nSearchStart].ePos.u32Key) {
      bFound = true;
      nIdx = nSearchStart;
    } else if (ePos.u32Key == this->m_pData[nSearchEnd].ePos.u32Key) {
      bFound = true;
      nIdx = nSearchEnd;
    } else {
      nIdx = nSearchStart + 1;
    }
  }

  return nIdx;
}

#endif  // TRI_SPARSE_MATRIX_H_