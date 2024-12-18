#ifndef CHAR_STRING_H_
#define CHAR_STRING_H_

#include <cctype>    // 字符处理函数库
#include <cstdarg>   // 可变参数处理库
#include <cstdio>    // 标准输入输出库
#include <cstring>   // 字符串处理库
#include <iostream>  // 输入输出流库

#include "sq_list.h"  // 顺序表基类

// 字符编码相关常量定义
const int kForceANSI = 0x10000;     // 强制使用ANSI编码格式
const int kForceUnicode = 0x20000;  // 强制使用Unicode编码格式
const int kForceInt64 = 0x40000;    // 强制使用64位整数类型

// 返回指向下一个字符的指针
inline const char* NextChar(const char* pszInput) {
  return pszInput + 1;
}

/**
 * @brief CharString类 - 实现字符串的基本操作
 * 继承自SqList<char>顺序表类,提供字符串的各种操作功能
 */
class CharString : public SqList<char> {
 public:
  // 构造与析构函数
  CharString();                         // 默认构造函数,创建空字符串
  CharString(const char* pszSrc);       // 使用C风格字符串构造
  CharString(const CharString& csSrc);  // 拷贝构造函数
  ~CharString();                        // 析构函数

  // 运算符重载
  CharString& operator=(const CharString& csSrc);  // 赋值运算符
  CharString& operator+=(const CharString& csSrc);  // 字符串拼接(CharString)
  CharString& operator+=(const char* pszSrc);  // 字符串拼接(C风格字符串)
  const char& operator[](int nIdx) const;      // 下标访问运算符

  // 字符串操作方法
  CharString& CopyN(const char* pszSrc, int n);  // 复制指定长度的字符串
  int Index(const CharString& csPat,
            int nIdx = 0) const;  // 朴素模式匹配查找子串
  int KMPIndex(const CharString& csPat, int nIdx = 0) const;  // KMP算法查找子串
  const char* ToCStr() const;                  // 转换为C风格字符串
  void Format(const char* pszFormat, ...);     // 格式化字符串
  int Compare(const CharString& csSrc) const;  // 字符串比较

  // 顺序表基本操作的重写
  int AddTail(const char& chElem);            // 在尾部添加字符
  bool Delete(int nIdx, char& chElem);        // 删除指定位置的字符
  bool Insert(int nIdx, const char& chElem);  // 在指定位置插入字符

 private:
  int SaveData(const char* pData, int nDataLen);  // 保存字符串数据
  void GetNext(const CharString& csPat,
               int* arrNext) const;  // KMP算法的Next数组计算
  void AppendZero();                 // 在字符串末尾添加'\0'
};

// 辅助函数声明
CharString Read(std::istream& istrInput);  // 从输入流读取字符串
CharString Read(std::istream& istrInput,
                char& chTerminal);       // 从输入流读取直到终止字符
void Write(const CharString& csOutput);  // 输出字符串到标准输出
void Concat(CharString& csDes, const CharString& csSrc);  // 字符串连接
void Copy(CharString& csDes, const CharString& csSrc);    // 字符串复制
void Copy(CharString& csDes, const CharString& csSrc,
          int n);  // 复制指定长度字符串
int Index(const CharString& csDes, const CharString& csPat,
          int nIdx = 0);  // 子串查找
CharString SubString(const CharString& csStr, int nIdx, int nLen);  // 子串提取

// 比较运算符重载声明
bool operator==(const CharString& csFirst, const CharString& csSecond);  // 相等
bool operator<(const CharString& csFirst, const CharString& csSecond);  // 小于
bool operator>(const CharString& csFirst, const CharString& csSecond);  // 大于
bool operator<=(const CharString& csFirst,
                const CharString& csSecond);  // 小于等于
bool operator>=(const CharString& csFirst,
                const CharString& csSecond);  // 大于等于
bool operator!=(const CharString& csFirst,
                const CharString& csSecond);  // 不等于

// 内联函数实现

inline CharString::CharString() : SqList() {
  AppendZero();
}

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
    return -1;  // 模式串长度超出主串剩余长度
  } else if (nPatLen == 0) {
    return nIdx;  // 空模式串匹配任意位置
  }

  const char* cszPat = csPat.ToCStr();
  int* arrNext = new int[nPatLen];  // 分配next数组空间
  GetNext(csPat, arrNext);          // 计算next数组

  int i = nIdx, j = 0;  // i为主串指针,j为模式串指针
  while (i < m_nDataLen) {
    if (j == -1 || m_pData[i] == cszPat[j]) {
      ++i;  // 字符匹配,两个指针都前进
      ++j;
    } else {
      j = arrNext[j];  // 字符不匹配,模式串指针回退
    }

    if (j == nPatLen) {  // 完全匹配
      delete[] arrNext;
      return i - j;
    }
  }

  delete[] arrNext;
  return -1;  // 未找到匹配
}

inline const char* CharString::ToCStr() const {
  return m_pData;
}

inline void CharString::Format(const char* pszFormat, ...) {
  va_list pvaList, pvaListSave;
  va_start(pvaList, pszFormat);
  va_copy(pvaListSave, pvaList);

  // 计算格式化后的字符串长度
  int nMaxLen = 0;
  for (const char* pszCurr = pszFormat; *pszCurr != '\0';
       pszCurr = NextChar(pszCurr)) {
    const char* pszNext = NextChar(pszCurr);

    if (*pszCurr != '%' || *pszNext == '%') {
      nMaxLen += 1;
      continue;
    }

    int nItemLen = 0;

    // 解析格式说明符的各个组成部分
    int nWidth = 0;
    while (*pszCurr != '\0') {
      if (*pszCurr == '#') {
        nMaxLen += 2;
      } else if (*pszCurr == '*') {
        nWidth = va_arg(pvaList, int);
      } else if (*pszCurr == '-' || *pszCurr == '+' || *pszCurr == '0') {
        // 跳过标志字符
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

    // 根据格式说明符类型计算所需空间
    switch (*pszCurr | nModifier) {
      case 'c':
      case 'C':
      case 'c' | kForceANSI:
      case 'C' | kForceANSI:
      case 'c' | kForceUnicode:
      case 'C' | kForceUnicode: {
        nItemLen = 2;
        va_arg(pvaList, int);
      } break;

      case 's':
      case 'S':
      case 's' | kForceANSI:
      case 'S' | kForceANSI:
      case 's' | kForceUnicode:
      case 'S' | kForceUnicode: {
        const char* pszNextArg = va_arg(pvaList, const char*);
        if (!pszNextArg) {
          nItemLen = 6;  // "(null)"的长度
        } else {
          nItemLen = static_cast<int>(strlen(pszNextArg));
          nItemLen = std::max(1, nItemLen);
        }
        break;
      }

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
          break;
        }

        case 'e':
        case 'g':
        case 'G': {
          va_arg(pvaList, double);
          nItemLen = std::max(128, nWidth + nPrecision);
          break;
        }

        case 'f': {
          double fNum = va_arg(pvaList, double);
          int nBufferLen = std::max(nWidth, 312 + nPrecision + 6);
          char* pszTemp = new char[nBufferLen];
          std::snprintf(pszTemp, nBufferLen, "%*.*f", nWidth, nPrecision + 6,
                        fNum);
          nItemLen = static_cast<int>(strlen(pszTemp));
          delete[] pszTemp;
          break;
        }

        case 'p': {
          va_arg(pvaList, void*);
          nItemLen = std::max(32, nWidth + nPrecision);
          break;
        }

        case 'n': {
          va_arg(pvaList, int*);
          break;
        }

        default:
          break;
      }
    }
    nMaxLen += nItemLen;
  }

  // 格式化字符串
  Reserve(nMaxLen + 1);
  m_nDataLen = vsnprintf(m_pData, nMaxLen + 1, pszFormat, pvaListSave);
  m_pData[m_nDataLen] = 0;  // 确保字符串以空字符结尾

  va_end(pvaListSave);
}

inline int CharString::Compare(const CharString& csSrc) const {
  const char* pDes = this->ToCStr();
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

inline void CharString::GetNext(const CharString& csPat, int* arrNext) const {
  int nPatLen = csPat.Length();
  const char* cszPat = csPat.ToCStr();

  // KMP算法的Next数组计算
  arrNext[0] = -1;  // 首字符的Next值为-1
  arrNext[1] = 0;   // 第二个字符的Next值为0
  int i = 2;        // 当前计算位置
  int k = 0;        // 前缀位置

  while (i < nPatLen) {
    if (k == -1 || cszPat[i - 1] == cszPat[k]) {
      arrNext[i] = k + 1;  // 找到匹配,更新Next值
      ++i;
      ++k;
    } else {
      k = arrNext[k];  // 失配时回退
    }
  }
}

inline void CharString::AppendZero() {
  if (m_nDataLen >= m_nBufferLen)
    Reserve(m_nDataLen * 2 + 8);
  m_pData[m_nDataLen] = '\0';  // 添加字符串结束符
}

inline CharString Read(std::istream& istrInput) {
  CharString csResult;
  char chCurrent;

  // 读取直到遇到换行或文件结束
  while (istrInput.peek() != EOF &&
         (chCurrent = static_cast<char>(istrInput.get())) != '\n') {
    csResult.AddTail(chCurrent);
  }
  return csResult;
}

inline CharString Read(std::istream& istrInput, char& chTerminal) {
  CharString csResult;
  char chCurrent;

  // 读取直到遇到终止字符
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

inline void Copy(CharString& csDes, const CharString& csSrc) {
  csDes = csSrc;
}

inline void Copy(CharString& csDes, const CharString& csSrc, int n) {
  csDes.CopyN(csSrc.ToCStr(), n);
}

inline int Index(const CharString& csDes, const CharString& csPat, int nIdx) {
  return csDes.Index(csPat, nIdx);
}

inline CharString SubString(const CharString& csStr, int nIdx, int nLen) {
  CharString csSub;

  // 参数合法性检查
  if (nIdx >= 0 && nIdx < csStr.Length() && nLen >= 0) {
    nLen = std::min(nLen, csStr.Length() - nIdx);  // 确保不越界
    csSub.CopyN(csStr.ToCStr() + nIdx, nLen);
  }

  return csSub;
}

// 比较运算符实现
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

#endif  // CHAR_STRING_H_