#ifndef MATRIX_H_
#define MATRIX_H_
#include <cmath>
#include <iostream>

#include "array.h"

template <class ElemType>
class Matrix : public Array<ElemType> {
 public:
  Matrix(int nRows, int nCols);
  ~Matrix();
  Matrix(const Matrix<ElemType>& mtxSrc);

#ifdef _INITIALIZER_LIST
  bool Init(std::initializer_list<ElemType> iList);
#endif  // _INITIALIZER_LIST

  int GetRows() const;
  int GetCols() const;
  bool Resize(int nRows, int nCols);
  bool IsEmpty() const;
  void PrintMtx(const char* pszMtxName) const;
  ElemType& operator()(int nRow, int nCol);
  Matrix<ElemType> CrossProduct(const Matrix<ElemType>& mtxSrc) const;
  Matrix<ElemType> DotProduct(const Matrix<ElemType>& mtxSrc) const;
  Matrix<ElemType> MultScaler(const ElemType tLambda) const;
  Matrix<ElemType> Sub(const Matrix<ElemType>& mtxSrc) const;
  Matrix<ElemType> Add(const Matrix<ElemType>& mtxSrc) const;
  Matrix<ElemType> Transpose() const;
  Matrix<ElemType> Inverse() const;
  ElemType* operator[](int nRow);
  Matrix<ElemType>& operator=(const Matrix<ElemType>& mtxSrc);
};

template <class ElemType>
Matrix<ElemType>::Matrix(int nRows, int nCols)
    : Array<ElemType>(2, nRows, nCols) {}

template <class ElemType>
Matrix<ElemType>::~Matrix() {}

template <class ElemType>
Matrix<ElemType>::Matrix(const Matrix<ElemType>& mtxSrc)
    : Array<ElemType>(2, mtxSrc.GetRows(), mtxSrc.GetCols()) {
  if (this != &mtxSrc) {
    int nSrcRows = mtxSrc.GetRows();
    int nSrcCols = mtxSrc.GetCols();
    std::copy(mtxSrc.m_pData, mtxSrc.m_pData + nSrcRows * nSrcCols,
              this->m_pData);
  }
}

#ifdef _INITIALIZER_LIST
template <class ElemType>
bool Matrix<ElemType>::Init(std::initializer_list<ElemType> iList) {
  int nSize = iList.size();
  int nTotalElemNum = GetRows() * GetCols();

  if (nSize > nTotalElemNum)
    return false;

  ElemType* pData = static_cast<ElemType*>(iList.begin());
  std::copy(pData, pData + nSize, this->m_pData);
  std::fill(this->m_pData + nSize, this->m_pData + nTotalElemNum, 0);

  return true;
}
#endif  // _INITIALIZER_LIST

template <class ElemType>
bool Matrix<ElemType>::IsEmpty() const {
  return (GetCols() == 0 || GetRows() == 0) ? true : false;
}

template <class ElemType>
void Matrix<ElemType>::PrintMtx(const char* pszMtxName) const {
  if (IsEmpty()) {
    std::cout << "Empty mtxrix!" << std::endl;
    return;
  }

  int nRows = GetRows();
  int nCols = GetCols();

  if (pszMtxName) {
    std::cout << '\n' << pszMtxName << ":\n";
  } else {
    std::cout << std::endl;
  }

  for (int i = 0; i < nRows; ++i) {
    for (int j = 0; j < nCols; ++j) {
      std::cout << (*this)(i, j);
      if (j < nCols - 1)
        std::cout << ",\t";
    }
    std::cout << std::endl;
  }
}

template <class ElemType>
ElemType& Matrix<ElemType>::operator()(int nRow, int nCol) {
  return *this->ElemAddress(nRow, nCol);
}

template <class ElemType>
Matrix<ElemType> Matrix<ElemType>::CrossProduct(
    const Matrix<ElemType>& mtxSrc) const {
  if (GetCols() != mtxSrc.GetRows())
    return Matrix<ElemType>(0, 0);

  Matrix<ElemType> mtxRes(GetRows(), mtxSrc.GetCols());

  int nResRows = mtxRes.GetRows();
  int nResCols = mtxRes.GetCols();

  int nLeftCols = GetCols();

  for (int i = 0; i < nResRows; ++i) {
    for (int j = 0; j < nResCols; ++j) {
      ElemType tSum = 0;

      for (int k = 0; k < nLeftCols; ++k) {
        tSum += (*this)(i, k) * mtxSrc(k, j);
      }

      mtxRes(i, j) = tSum;
    }
  }

  return mtxRes;
}

template <class ElemType>
Matrix<ElemType> Matrix<ElemType>::DotProduct(
    const Matrix<ElemType>& mtxSrc) const {
  if (GetCols() != mtxSrc.GetCols() || GetRows() != mtxSrc.GetRows()) {
    return Matrix<ElemType>(0, 0);
  }

  int nRows = GetRows();
  int nCols = GetCols();

  Matrix<ElemType> mtxRes(nRows, nCols);

  for (int i = 0; i < nRows; ++i) {
    for (int j = 0; j < nCols; ++j) {
      mtxRes(i, j) = (*this)(i, j) * mtxSrc(i, j);
    }
  }

  return mtxRes;
}

template <class ElemType>
Matrix<ElemType> Matrix<ElemType>::MultScaler(const ElemType tLambda) const {
  Matrix<ElemType> mtxElem = *this;
  int nRows = GetRows();
  int nCols = GetCols();
  for (int i = 0; i < nRows; ++i) {
    for (int j = 0; j < nCols; ++j) {
      mtxElem(i, j) = (*this)(i, j) * tLambda;
    }
  }
}

template <class ElemType>
Matrix<ElemType> Matrix<ElemType>::Sub(const Matrix<ElemType>& mtxSrc) const {
  if (GetCols() != mtxSrc.GetCols() || GetRows() != mtxSrc.GetRows()) {
    return Matrix<ElemType>(0, 0);
  }

  int nRows = GetRows();
  int nCols = GetCols();

  Matrix<ElemType> mtxRes(nRows, nCols);

  for (int i = 0; i < nRows; ++i) {
    for (int j = 0; j < nCols; ++j) {
      mtxRes(i, j) = (*this)(i, j) - mtxSrc(i, j);
    }
  }

  return mtxRes;
}

template <class ElemType>
Matrix<ElemType> Matrix<ElemType>::Add(const Matrix<ElemType>& mtxSrc) const {
  if (GetCols() != mtxSrc.GetCols() || GetRows() != mtxSrc.GetRows()) {
    return Matrix<ElemType>(0, 0);
  }

  int nRows = GetRows();
  int nCols = GetCols();

  Matrix<ElemType> mtxRes(nRows, nCols);

  for (int i = 0; i < nRows; ++i) {
    for (int j = 0; j < nCols; ++j) {
      mtxRes(i, j) = (*this)(i, j) + mtxSrc(i, j);
    }
  }

  return mtxRes;
}

template <class ElemType>
Matrix<ElemType> Matrix<ElemType>::Transpose() const {
  int nRows = GetRows();
  int nCols = GetCols();

  Matrix<ElemType> mtxRes(nCols, nRows);

  for (int i = 0; i < nRows; ++i) {
    for (int j = 0; j < nCols; ++j) {
      mtxRes(j, i) = (*this)(i, j);
    }
  }

  return mtxRes;
}

template <class ElemType>
Matrix<ElemType> Matrix<ElemType>::Inverse() const {
  if (GetCols() != GetRows())
    return Matrix<ElemType>(0, 0);

  int nSize = GetRows();

  ElemType fEpsilon = 1e-7;

  Matrix<ElemType> mtxAug(nSize, 2 * nSize);

  for (int i = 0; i < nSize; ++i) {
    for (int j = 0; j < nSize; ++j) {
      mtxAug(i, j) = (*this)(i, j);
      mtxAug(i, j + nSize) = (i == j) ? 1 : 0;
    }
  }

  for (int i = 0; i < nSize; ++i) {
    ElemType fMax = std::abs(mtxAug(i, i));
    int nMaxRow = i;
    for (int k = i + 1; k < nSize; ++k) {
      if (std::abs(mtxAug(k, i)) > fMax) {
        fMax = std::abs(mtxAug(k, i));
        nMaxRow = k;
      }
    }

    if (fMax < fEpsilon)
      return Matrix<ElemType>(0, 0);

    if (nMaxRow != i) {
      for (int j = 0; j < 2 * nSize; ++j) {
        std::swap(mtxAug(i, j), mtxAug(nMaxRow, j));
      }
    }

    ElemType fPivot = mtxAug(i, i);

    for (int j = i; j < 2 * nSize; ++j) {
      mtxAug(i, j) /= fPivot;
    }

    for (int k = 0; k < nSize; ++k) {
      if (k != i) {
        ElemType fFactor = mtxAug(k, i);
        for (int j = i; j < 2 * nSize; ++j) {
          mtxAug(k, j) -= fFactor * mtxAug(i, j);
        }
      }
    }
  }

  Matrix<ElemType> mtxInv(nSize, nSize);
  for (int i = 0; i < nSize; ++i) {
    for (int j = 0; j < nSize; ++j) {
      mtxInv(i, j) = mtxAug(i, j + nSize);
    }
  }

  return mtxInv;
}

template <class ElemType>
int Matrix<ElemType>::GetRows() const {
  return this->m_pBounds[0];
}

template <class ElemType>
int Matrix<ElemType>::GetCols() const {
  return this->m_pBounds[1];
}

template <class ElemType>
bool Matrix<ElemType>::Resize(int nRows, int nCols) {
  if (nRows < 1 || nCols < 1)
    return false;

  if (this->m_pData)
    delete[] this->m_pData;

  this->m_pData = new ElemType[nRows * nCols];
  this->m_pBounds[0] = nRows;
  this->m_pBounds[1] = nCols;
  this->m_pConstants[0] = nCols;

  return true;
}

template <class ElemType>
Matrix<ElemType>& Matrix<ElemType>::operator=(const Matrix<ElemType>& mtxSrc) {
  if (this != &mtxSrc) {
    int nSrcRows = mtxSrc.GetRows();
    int nSrcCols = mtxSrc.GetCols();
    if (GetRows() != nSrcRows || GetCols() != nSrcCols) {
      Resize(nSrcRows, nSrcCols);
    }
    std::copy(mtxSrc.m_pData, mtxSrc.m_pData + nSrcRows * nSrcCols,
              this->m_pData);
  }
  return *this;
}

#endif  // MATRIX_H_