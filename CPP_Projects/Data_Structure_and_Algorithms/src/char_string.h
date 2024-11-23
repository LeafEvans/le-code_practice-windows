#ifndef _CHAR_STRING_H_
#define _CHAR_STRING_H_

#include <cctype>   // 字符处理函数
#include <cstdarg>  // 可变参数支持
#include <cstdio>   // 标准输入输出
#include <cstring>
#include <iostream>  // 输入输出流

#include "sq_list.h"  // 顺序表基类

// 字符编码相关常量
const int kForceANSI = 0x10000;     // 强制使用ANSI编码
const int kForceUnicode = 0x20000;  // 强制使用Unicode编码
const int kForceInt64 = 0x40000;    // 强制使用64位整数

// 返回下一个字符的指针
inline const char* NextChar(const char* pszInput) { return pszInput + 1; }

// CharString类：实现字符串操作，继承自SqList<char>
class CharString : public SqList<char> {
 public:
  CharString();                         // 默认构造函数
  CharString(const char* pszSrc);       // C风格字符串构造函数
  CharString(const CharString& csSrc);  // 拷贝构造函数
  ~CharString();                        // 析构函数
  CharString& operator=(const CharString& csSrc);  // 赋值运算符
  CharString& operator+=(const CharString& csSrc);  // 字符串拼接（CharString）
  CharString& operator+=(const char* pszSrc);  // 字符串拼接（C风格字符串）
  const char& operator[](int nIdx) const;        // 下标访问运算符
  CharString& CopyN(const char* pszSrc, int n);  // 复制前n个字符
  int Index(const CharString& csPat, int nIdx = 0) const;  // 子串查找
  int KMPIndex(const CharString& csPat, int nIdx = 0) const;  // KMP算法子串查找
  const char* ToCStr() const;                  // 转换为C风格字符串
  void Format(const char* pszFormat, ...);     // 格式化字符串
  int Compare(const CharString& csSrc) const;  // 字符串比较
  int AddTail(const char& chElem);             // 在尾部添加字符
  bool Delete(int nIdx, char& chElem);         // 删除指定位置的字符
  bool Insert(int nIdx, const char& chElem);   // 在指定位置插入字符

 private:
  int SaveData(const char* pData, int nDataLen);  // 保存数据
  void GetNextVal(const CharString& csPat,
                  int* arrNextVal) const;  // KMP算法辅助函数
  void AppendZero();                       // 在字符串末尾添加'\0'
};

// 辅助函数声明
CharString Read(std::istream& istrInput);  // 从输入流读取字符串
CharString Read(std::istream& istrInput,
                char& chTerminal);  // 从输入流读取字符串，直到遇到终止字符
void Write(const CharString& csOutput);  // 将字符串写入输出流
void Concat(CharString& csDes, const CharString& csSrc);  // 连接两个字符串
void Copy(CharString& csDes, const CharString& csSrc);    // 复制字符串
void Copy(CharString& csDes, const CharString& csSrc,
          int n);  // 复制指定长度的字符串
int Index(const CharString& csDes, const CharString& csPat,
          int nIdx = 0);  // 在字符串中查找子串
CharString SubString(const CharString& csStr, int nIdx, int nLen);  // 提取子串

// 比较运算符重载
bool operator==(const CharString& csFirst, const CharString& csSecond);
bool operator<(const CharString& csFirst, const CharString& csSecond);
bool operator>(const CharString& csFirst, const CharString& csSecond);
bool operator<=(const CharString& csFirst, const CharString& csSecond);
bool operator>=(const CharString& csFirst, const CharString& csSecond);
bool operator!=(const CharString& csFirst, const CharString& csSecond);

// 内联函数实现

inline CharString::CharString() : SqList() { AppendZero(); }

inline CharString::CharString(const char* pszSrc) {
  int nSrcLen = static_cast<int>(strlen(pszSrc));
  SaveData(pszSrc, nSrcLen);
  AppendZero();
}

inline CharString::CharString(const CharString& csSrc) : SqList(csSrc) {
  AppendZero();
}

inline CharString::~CharString() {}

inline CharString& CharString::operator=(const CharString& csSrc) {
  int nSrcLen = csSrc.Length();
  char* pSrcBuf = csSrc.m_pData;
  Clear();
  SaveData(pSrcBuf, nSrcLen);
  AppendZero();
  return *this;
}

inline CharString& CharString::operator+=(const CharString& csSrc) {
  int nSrcLen = csSrc.Length();
  char* pSrcBuf = csSrc.m_pData;
  SaveData(pSrcBuf, nSrcLen);
  AppendZero();
  return *this;
}

inline CharString& CharString::operator+=(const char* pszSrc) {
  int nSrcLen = static_cast<int>(strlen(pszSrc));
  SaveData(pszSrc, nSrcLen);
  AppendZero();
  return *this;
}

inline const char& CharString::operator[](int nIdx) const {
  if (nIdx < 0 || nIdx >= m_nDataLen) {
    throw std::out_of_range("Index out of range: CharString::operator[]");
  }
  return m_pData[nIdx];
}

inline CharString& CharString::CopyN(const char* pszSrc, int n) {
  Clear();
  int nSrcLen = static_cast<int>(strlen(pszSrc));
  n = std::min(n, nSrcLen);
  SaveData(pszSrc, n);
  AppendZero();
  return *this;
}

inline int CharString::Index(const CharString& csPat, int nIdx) const {
  int nPatLen = csPat.Length();

  if (m_nDataLen - nIdx < nPatLen) {
    return -1;
  } else if (nPatLen == 0) {
    return nIdx;
  }

  const char* pszPat = csPat.ToCStr();

  if (memcmp(m_pData + nIdx, pszPat, nPatLen) == 0) {
    return nIdx;
  }

  int nPatSum = 0;
  int nWindowSum = 0;

  for (int i = 0; i < nPatLen; ++i) {
    nPatSum += pszPat[i];
    nWindowSum += m_pData[i + nIdx];
  }

  for (int i = nIdx + 1; i < m_nDataLen; ++i) {
    nWindowSum += m_pData[i + nPatLen - 1] - m_pData[i - 1];
    if (nPatSum == nWindowSum && m_pData[i] == pszPat[0] &&
        m_pData[i + nPatLen - 1] == pszPat[nPatLen - 1] &&
        memcmp(m_pData + i, pszPat, nPatLen) == 0) {
      return i;
    }
  }

  return -1;
}

inline int CharString::KMPIndex(const CharString& csPat, int nIdx) const {
  int nPatLen = csPat.Length();

  if (m_nDataLen - nIdx < nPatLen) {
    return -1;
  } else if (nPatLen == 0) {
    return nIdx;
  }

  const char* pszPat = csPat.ToCStr();
  int* arrNextVal = new int[nPatLen];
  GetNextVal(csPat, arrNextVal);

  int i = nIdx, j = 0;
  while (i < m_nDataLen) {
    if (j == -1 || m_pData[i] == pszPat[j]) {
      ++i;
      ++j;
    } else {
      j = arrNextVal[j];
    }

    if (j == nPatLen) {
      delete[] arrNextVal;
      return i - j;
    }
  }

  delete[] arrNextVal;
  return -1;
}

inline const char* CharString::ToCStr() const { return m_pData; }

inline void CharString::Format(const char* pszFormat, ...) {
  va_list pvaList, pvaListSave;
  va_start(pvaList, pszFormat);
  va_copy(pvaListSave, pvaList);

  // 计算格式化的最大长度
  int nMaxLen = 0;
  for (const char* pszCurr = pszFormat; *pszCurr != '\0';
       pszCurr = NextChar(pszCurr)) {
    // 获取下一个字符
    const char* pszNext = NextChar(pszCurr);

    if (*pszCurr != '%' || *pszNext == '%') {
      nMaxLen += 1;
      continue;
    }

    int nItemLen = 0;

    // 解析宽度
    int nWidth = 0;
    while (*pszCurr != '\0') {
      if (*pszCurr == '#') {
        nMaxLen += 2;
      } else if (*pszCurr == '*') {
        nWidth = va_arg(pvaList, int);
      } else if (*pszCurr == '-' || *pszCurr == '+' || *pszCurr == '0') {
        // 忽略标志字符
      } else {
        break;
      }
      pszCurr = NextChar(pszCurr);
    }

    // 解析数字宽度
    if (nWidth == 0) {
      nWidth = atoi(pszCurr);
      while (*pszCurr != '\0' && isdigit(*pszCurr)) {
        pszCurr = NextChar(pszCurr);
      }
    }

    // 解析精度
    int nPrecision = 0;
    if (*pszCurr == '.') {
      pszCurr = NextChar(pszCurr);

      if (*pszCurr == '*') {
        nPrecision = va_arg(pvaList, int);
        pszCurr = NextChar(pszCurr);
      } else {
        nPrecision = atoi(pszCurr);

        while (*pszCurr != '\0' && isdigit(*pszCurr)) {
          pszCurr = NextChar(pszCurr);
        }
      }
    }

    // 解析长度修饰符
    int nModifier = 0;
    if (memcmp(pszCurr, "I64", 3) == 0) {
      pszCurr += 3;
      nModifier = kForceInt64;
    } else {
      switch (*pszCurr) {
        case 'h':
          nModifier = kForceANSI;
          pszCurr = NextChar(pszCurr);
          break;
        case 'l':
          nModifier = kForceUnicode;
          pszCurr = NextChar(pszCurr);
          break;
        case 'F':
        case 'N':
        case 'L':
        default:
          pszCurr = NextChar(pszCurr);
          break;
      }
    }

    // 根据格式说明符计算项目长度
    switch (*pszCurr | nModifier) {
      // 字符类型
      case 'c':
      case 'C':
      case 'c' | kForceANSI:
      case 'C' | kForceANSI:
      case 'c' | kForceUnicode:
      case 'C' | kForceUnicode: {
        nItemLen = 2;
        va_arg(pvaList, int);
      } break;

      // 字符串类型
      case 's':
      case 'S':
      case 's' | kForceANSI:
      case 'S' | kForceANSI:
      case 's' | kForceUnicode:
      case 'S' | kForceUnicode: {
        const char* pszNextArg = va_arg(pvaList, const char*);
        if (!pszNextArg) {
          nItemLen = 6;  // "(null)"
        } else {
          nItemLen = static_cast<int>(strlen(pszNextArg));
          nItemLen = std::max(1, nItemLen);
        }
      } break;

      default:
        break;
    }

    // 应用精度和宽度限制
    if (nItemLen != 0) {
      if (nPrecision != 0) {
        nItemLen = std::min(nItemLen, nPrecision);
      }
      nItemLen = std::max(nItemLen, nWidth);
    } else {
      switch (*pszCurr) {
        case 'd':
        case 'i':
        case 'u':
        case 'x':
        case 'o': {
          if (nModifier & kForceInt64) {
            va_arg(pvaList, long long);
          } else {
            va_arg(pvaList, int);
          }
          nItemLen = std::max(32, nWidth + nPrecision);
        } break;

        // 浮点数
        case 'e':
        case 'g':
        case 'G': {
          va_arg(pvaList, double);
          nItemLen = std::max(128, nWidth + nPrecision);
        } break;

        // 浮点数（固定精度）
        case 'f': {
          double fNum = va_arg(pvaList, double);
          int nBufferLen = std::max(nWidth, 312 + nPrecision + 6);
          char* pszTemp = new char[nBufferLen];
          std::snprintf(pszTemp, nBufferLen, "%*.*f", nWidth, nPrecision + 6,
                        fNum);
          nItemLen = static_cast<int>(strlen(pszTemp));
          delete[] pszTemp;
        } break;

        // 指针类型
        case 'p': {
          va_arg(pvaList, void*);
          nItemLen = std::max(32, nWidth + nPrecision);
        } break;

        // 特殊情况：写入字符数
        case 'n':
          va_arg(pvaList, int*);
          break;

        default:
          break;
      }
    }
    nMaxLen += nItemLen;
  }

  // 调整字符串大小并格式化
  Reserve(nMaxLen + 1);

  m_nDataLen = vsnprintf(m_pData, nMaxLen + 1, pszFormat, pvaListSave);

  // 确保字符串以空字符结尾
  m_pData[m_nDataLen] = 0;
  va_end(pvaListSave);
}

inline int CharString::Compare(const CharString& csSrc) const {
  const char* pDes = ToCStr();
  const char* pSrc = csSrc.ToCStr();
  return strcmp(pDes, pSrc);
}

inline int CharString::AddTail(const char& chElem) {
  int nIdx = SqList<char>::AddTail(chElem);
  AppendZero();
  return nIdx;
}

inline bool CharString::Delete(int nIdx, char& chElem) {
  bool bTemp = SqList<char>::Delete(nIdx, chElem);
  AppendZero();
  return bTemp;
}

inline bool CharString::Insert(int nIdx, const char& chElem) {
  bool bTemp = SqList<char>::Insert(nIdx, chElem);
  AppendZero();
  return bTemp;
}

inline int CharString::SaveData(const char* pData, int nDataLen) {
  int nIdx = SqList<char>::SaveData(pData, nDataLen);
  AppendZero();
  return nIdx;
}

inline void CharString::GetNextVal(const CharString& csPat,
                                   int* arrNextVal) const {
  int nPatLen = csPat.Length();
  const char* pszPat = csPat.ToCStr();
  arrNextVal[0] = -1;
  arrNextVal[1] = 0;
  int i = 2;
  int k = 0;

  while (i < nPatLen) {
    if (k == -1 || pszPat[i - 1] == pszPat[k]) {
      arrNextVal[i] = k + 1;
      ++i;
      ++k;
    } else {
      k = arrNextVal[k];
    }
  }
}

inline void CharString::AppendZero() {
  if (m_nDataLen >= m_nBufferLen) {
    Reserve(m_nDataLen * 2 + 8);
  }
  m_pData[m_nDataLen] = '\0';
}

inline CharString Read(std::istream& istrInput) {
  CharString csResult;
  char chCurrent;

  while (istrInput.peek() != EOF &&
         (chCurrent = static_cast<char>(istrInput.get())) != '\n') {
    csResult.AddTail(chCurrent);
  }
  return csResult;
}

inline CharString Read(std::istream& istrInput, char& chTerminal) {
  CharString csResult;
  char chCurrent;

  while (istrInput.peek() != EOF &&
         (chCurrent = static_cast<char>(istrInput.get())) != '\n') {
    csResult.AddTail(chCurrent);
  }
  chTerminal = chCurrent;
  return csResult;
}

inline void Write(const CharString& csOutput) {
  std::cout << csOutput.ToCStr() << std::endl;
}

inline void Concat(CharString& csDes, const CharString& csSrc) {
  csDes += csSrc;
}

inline void Copy(CharString& csDes, const CharString& csSrc) { csDes = csSrc; }

inline void Copy(CharString& csDes, const CharString& csSrc, int n) {
  csDes.CopyN(csSrc.ToCStr(), n);
}

inline int Index(const CharString& csDes, const CharString& csPat, int nIdx) {
  return csDes.Index(csPat, nIdx);
}

inline CharString SubString(const CharString& csStr, int nIdx, int nLen) {
  CharString csSub;

  if (nIdx >= 0 && nIdx < csStr.Length() && nLen >= 0) {
    nLen = std::min(nLen, csStr.Length() - nIdx);
    csSub.CopyN(csStr.ToCStr() + nIdx, nLen);
  }

  return csSub;
}

inline bool operator==(const CharString& csFirst, const CharString& csSecond) {
  return csFirst.Compare(csSecond) == 0;
}

inline bool operator<=(const CharString& csFirst, const CharString& csSecond) {
  return csFirst.Compare(csSecond) <= 0;
}

inline bool operator>=(const CharString& csFirst, const CharString& csSecond) {
  return csFirst.Compare(csSecond) >= 0;
}

inline bool operator>(const CharString& csFirst, const CharString& csSecond) {
  return csFirst.Compare(csSecond) > 0;
}

inline bool operator<(const CharString& csFirst, const CharString& csSecond) {
  return csFirst.Compare(csSecond) < 0;
}

inline bool operator!=(const CharString& csFirst, const CharString& csSecond) {
  return csFirst.Compare(csSecond) != 0;
}

#endif  // _CHAR_STRING_H_