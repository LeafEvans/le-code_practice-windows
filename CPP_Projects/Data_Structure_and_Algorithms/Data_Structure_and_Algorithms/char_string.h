#ifndef _CHAR_STRING_H_
#define _CHAR_STRING_H_
#pragma warning(disable : 4996)  // 禁用不安全警告

#include <cstdarg>
#include <iostream>

#include "sq_list.h"

const int kForceANSI = 0x10000;     // 使用 ANSI 编码
const int kForceUnicode = 0x20000;  // 使用 Unicode 编码
const int kForceInt64 = 0x40000;    // 使用 64 位整数类型

inline const char* NextChar(const char* cszInput) { return cszInput + 1; }

class CharString : public SqList<char> {
 public:
  CharString();                         // 默认构造函数
  CharString(const char* cszSrc);       // C 字符串构造
  CharString(const CharString& csSrc);  // 拷贝构造函数
  ~CharString();
  CharString& operator=(const CharString& csSrc);   // 重载赋值运算符
  CharString& operator+=(const CharString& csSrc);  // 重载 += 运算符
  CharString& operator+=(const char* cszSrc);       // 重载 += 运算符
  const char& operator[](int nIdx) const;           // 重载 [] 运算符
  CharString& CopyN(const char* cszSrc, int n);  // 拷贝 C 风格字符串 n 个字符
  int Index(const CharString& csPattern, int nIdx = 0);  // 匹配模式串
  // 使用 KMP 算法匹配模式串
  int KMPIndex(const CharString& csPattern, int nIdx = 0);
  const char* ToCStr() const;               // 将字符串转换为 C 风格
  void Format(const char* cszFormat, ...);  // 格式化输入数据
  int Compare(const CharString& csSrc) const;  // 比对源字符串和目的字符串
  int AddTail(const char& chElem);             // 末尾需要添加 0，重载
  bool Delete(int nIdx, char& chElem);         // 末尾需要添加 0，重载
  bool Insert(int nIdx, const char& chElem);  // 末尾需要添加 0，重载

 private:
  int SaveData(char* pData, int nDataLen);  // 需要末尾添加 0，重载
  // KMP 算法求 Next 数组
  void GetNextVal(const CharString& csPattern, int* pNextVal) const;
  void AppendZero();  // 追加字符串末尾结束字符 '\0'
};

// 串相关操作
CharString Read(std::istream& istrInput);  // 从输入流读入串
// 从输入流读入串，并用 chTerminalChar 返回串结束字符
CharString Read(std::istream& istrInput, char chTerminalChar);
void Write(const CharString& csInput);  // 输出串
// 将 csSrc 连接到 csDes
void Concat(CharString& csDes, const CharString& csSrc);
// 将 csSrc 复制到 csDes
void Copy(CharString& csDes, const CharString& csSrc);
// 将 csSrc 复制 n 个字符到 csDes
void Copy(CharString& csDes, const CharString& csSrc, int n);
// 查找模式串 csPattern 第一次在目标串 csDes 中从第 nIdx 个字符开始出现的位置
int Index(const CharString& csDes, const CharString& csPattern);
// 求 csSrc 的第 nIdx 个字符开始的长度为 nLen 的子串
CharString SubString(const CharString& csSrc, int nIdx, int nLen);
bool operator==(const CharString& csFirst, const CharString& csSecond);
bool operator<(const CharString& csFirst, const CharString& csSecond);
bool operator>(const CharString& csFirst, const CharString& csSecond);
bool operator<=(const CharString& csFirst, const CharString& csSecond);
bool operator>=(const CharString& csFirst, const CharString& csSecond);
bool operator!=(const CharString& csFirst, const CharString& csSecond);

// 默认构造，空字符串，添加末尾结束符 '\0'
inline CharString::CharString() { AppendZero(); }

// 由 C 风格字符串构造
inline CharString::CharString(const char* cszSrc) {
  size_t nSrcLen = std::strlen(cszSrc);          // 获取源字符串长度
  SaveData(const_cast<char*>(cszSrc), nSrcLen);  // 调用父类接口存入数据
  AppendZero();                                  // 末尾添加结束符 '\0'
}

// 重载 = 运算符，可以直接拷贝赋值
inline CharString::CharString(const CharString& csSrc) { *this = csSrc; }

inline CharString::~CharString() {}

inline CharString& CharString::operator=(const CharString& csSrc) {
  int nSrcLen = csSrc.Length();  // 调用基类函数，获取字符串长度
  Clear();                       // 调用基类长度，清空原有数据
  SaveData(csSrc.m_pData, nSrcLen);  // 调用父类接口存入数据
  AppendZero();                      // 添加末尾结束符 '\0'
  return *this;
}

inline CharString& CharString::operator+=(const CharString& csSrc) {
  int nSaveLen = csSrc.Length();      // 获取源字符串长度
  SaveData(csSrc.m_pData, nSaveLen);  // 调用父类接口存入数据
  AppendZero();                       // 添加末尾结束符 '\0'
  return *this;
}

inline CharString& CharString::operator+=(const char* cszSrc) {
  int nSrcLen = std::strlen(cszSrc);             // 获取源字符串长度
  SaveData(const_cast<char*>(cszSrc), nSrcLen);  // 调用父类接口追加存入数据
  AppendZero();                                  // 添加末尾结束符 '\0'
  return *this;
}

inline const char& CharString::operator[](int nIdx) const {
  if (nIdx < 0 || nIdx >= m_nDataLen) {  // 非法索引
    throw std::runtime_error("Index out of range.");
  }
  return m_pData[nIdx];
}

inline CharString& CharString::CopyN(const char* cszSrc, int n) {
  Clear();                            // 先清空内部缓冲
  int nSrcLen = std::strlen(cszSrc);  // 获取源字符串的长度
  if (n > nSrcLen) {
    n = nSrcLen;  // 拷貝數大於字符串長度，取字符串長度
  }
  SaveData(const_cast<char*>(cszSrc), n);
  AppendZero();  // 添加末尾結束符 '\0'
  return *this;
}

inline const char* CharString::ToCStr() const { return m_pData; }

inline void CharString::Format(const char* cszFormat, ...) {
  // 定义两个 va_list 变量，用于处理可变参数列表
  std::va_list argList, argListSave;

  // 初始化 argList，指向 cszFormat 后的第一个可变参数
  va_start(argList, cszFormat);

  // 将 argList 的初始状态保存到 argListSave
  // 计算完所需长度后，可以重新遍历参数列表进行格式化
  va_start(argListSave, cszFormat);

  int nMaxLen = 0;  // 预估最终字符床的最大长度
  for (const char* cszCurr = cszFormat; *cszCurr != '\0';
       cszCurr = NextChar(cszCurr)) {
    // 若当前字符不为 '%' 或者当前字符的下一字符（此时已经更新至下一字符）为 '%'
    if (*cszCurr != '%' || *(cszCurr = NextChar(cszCurr)) == '%') {
      nMaxLen += std::strlen(cszCurr);  // 从当前字符开始的字符串长度加上去
      continue;
    }

    int nItemLen = 0;  // 记录当前格式项的长度
    int nWidth = 0;    // 格式说明符指定最小输出宽度

    // 解析格式说明符中的标志字符
    while (*cszCurr != '\0') {
      if (*cszCurr == '#') {
        // '#' 表示特殊格式，如在十六进制中添加 '0x' 前缀，或保留小数点等
        nMaxLen += 2;  // 增加 2 以预留额外空间
      } else if (*cszCurr == '*') {
        // '*' 表示宽度是动态的，从参数列表中获取宽度值
        nWidth = va_arg(argList, int);  // 使用 va_arg 获取并存储到 nWidth 中
      } else if (*cszCurr == '-' || *cszCurr == '+' || *cszCurr == '0' ||
                 *cszCurr == ' ') {  // 部分标志字符，暂不做处理
      } else {
        break;  // 当前字符为非标志字符，退出处理循环
      }

      cszCurr = NextChar(cszCurr);  // 更新到下一字符
    }

    if (nWidth == 0) {         // 若指定宽度为 0，说明是静态数值
      nWidth = atoi(cszCurr);  // 将静态数值解析为整形
      while (*cszCurr != '\0' && std::isdigit(*cszCurr)) {
        // 检查当前字符是否为数字，并且未达到字符床结束
        cszCurr = NextChar(cszCurr);  // 跳过这个数字字符
      }
    }

    // 解释格式说明符中的精度
    int nPrecision = 0;  // 格式说明符指定精度
    if (*cszCurr == '.') {
      // 跳过 '.' 到下一字符
      cszCurr = NextChar(cszCurr);

      if (*cszCurr == '*') {                // 动态长度
        nPrecision = va_arg(argList, int);  // 获取相应参数
        cszCurr = NextChar(cszCurr);        // 跳转到下一字符
      } else {
        nPrecision = atoi(cszCurr);  // 检测数字
        while (*cszCurr != '\0' && std::isdigit(*cszCurr)) {
          cszCurr = NextChar(cszCurr);  // 跳过剩下数字字符
        }
      }
    }

    // 解释并处理格式说明符中的修饰符
    int nModifier = 0;  // 格式说明符指定类型修饰符
    if (std::memcmp(cszCurr, "I64", 3) == 0) {
      cszCurr += 3;             // 跳过三个字符
      nModifier = kForceInt64;  // 更新指定类型
    } else {
      switch (*cszCurr) {
        case 'h':  // 解释成 short 类型
          nModifier = kForceANSI;
          cszCurr = NextChar(cszCurr);
          break;
        case 'l':  // 解释成 long 类型
          nModifier = kForceUnicode;
          cszCurr = NextChar(cszCurr);
          break;

        case 'F':  // 部分不兼容修饰符
        case 'N':
        case 'L':
          cszCurr = NextChar(cszCurr);
          break;
      }
    }

    // 处理格式说明符
    switch (*cszCurr | nModifier) {
        // 字符
      case 'c':
      case 'C':
      case 'c' | kForceANSI:
      case 'C' | kForceANSI:
      case 'c' | kForceUnicode:
      case 'C' | kForceUnicode:
        nItemLen = 2;
        va_arg(argList, short);  // 提取 short 类型的字符数据
        break;

        // 字符串
      case 's':
      case 'S':
      case 's' | kForceUnicode:
      case 'S' | kForceUnicode:
      case 's' | kForceANSI:
      case 'S' | kForceANSI:
        const char* cszNextArg = va_arg(argList, const char*);
        if (cszNextArg == NULL) {
          nItemLen = 6;  // "(null)"
        } else {         // 确保输出的最小长度为 1
          nItemLen = std::max(1, static_cast<int>(std::strlen(cszNextArg)));
        }
        break;
    }

    // 如果当前项的长度不为 0，则根据精度和最小宽度进行调整
    if (nItemLen != 0) {      // 输出长度不为 0 时
      if (nPrecision != 0) {  // 如果精度不为 0，表示有精度限制
        // 将长度限制为精度指定的最大值
        nItemLen = std::min(nItemLen, nPrecision);
      }
      // 设定输出长度至少不低于最小输出宽度
      nItemLen = std::max(nItemLen, nWidth);
    } else {  // 如果当前项的长度为 0，处理不同类型的格式说明符
      switch (*cszCurr) {
        // 处理整型类型格式说明符
        case 'd':
        case 'i':
        case 'u':
        case 'x':
        case 'X':
        case 'o':
          // 如果存在 64 位整数修饰符，则提取 long long 类型，否则提取 int 类型
          if (nModifier & kForceInt64) {
            va_arg(argList, long long);
          } else {
            va_arg(argList, int);
          }
          // 设置最小输出长度，取 32 和 (nWidth + nPrecision) 的最大值
          nItemLen = std::max(32, nWidth + nPrecision);
          break;

        // 处理科学计数法和通用浮点类型格式说明符
        case 'e':
        case 'g':
        case 'G':
          // 提取 double 类型的数据
          va_arg(argList, double);
          // 设置最小输出长度，取 128 和 (nWidth + nPrecision) 的最大值
          nItemLen = std::max(128, nWidth + nPrecision);
          break;

        // 处理浮点数格式说明符
        case 'f': {
          double fNum;
          char* pszTemp;

          // 为浮点数分配临时缓冲区，大小取 nWidth 和 (312 + nPrecision + 6)
          // 中的最大值
          pszTemp = new char[std::max(nWidth, 312 + nPrecision + 6)];

          // 提取 double 类型的数据
          fNum = va_arg(argList, double);
          // 格式化浮点数为字符串，并计算输出长度
          std::sprintf(pszTemp, "%*.*f", nWidth, nPrecision + 6, fNum);
          nItemLen = std::strlen(pszTemp);  // 获取格式化后的字符串长度
          delete[] pszTemp;                 // 释放临时缓冲区
          break;
        }

        // 处理指针类型格式说明符
        case 'p':
          // 提取 void* 类型的指针数据
          va_arg(argList, void*);
          // 设置最小输出长度为 32，并确保长度不小于 (nWidth + nPrecision)
          nItemLen = std::max(32, nWidth + nPrecision);
          break;

        // 处理计数器类型格式说明符
        case 'n':
          // 提取 int* 类型的指针数据，通常用于存储已输出的字符数
          va_arg(argList, int*);
          break;

        // 默认情况，未处理的格式说明符直接跳过
        default:
          break;
      }
    }

    nMaxLen += nItemLen;
  }

  Resize(nMaxLen + 1);
  m_nDataLen = vsprintf(m_pData, cszFormat, argListSave);

  m_pData[m_nDataLen] = 0;

  va_end(argListSave);
}
#endif  // _CHAR_STRING_H_