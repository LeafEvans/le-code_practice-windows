#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include <cctype>
#include <cmath>
#include <cstring>
#include <typeinfo>

#include "sq_list.h"
#include "sq_stack.h"

template <class ElemType>
class Calculator {
 public:
  Calculator();                      // 默认构造函数
  Calculator(const char* pszInfix);  // 带参数构造函数，初始化中缀表达式
  ~Calculator();                     // 析构函数

  const char* GetInfix();    // 获取中缀表达式字符串
  const char* GetPostfix();  // 获取后缀表达式字符串
  bool InfixToPostfix();     // 将中缀表达式转换为后缀表达式
  bool EvaluatePostfix(ElemType& tValue);  // 计算后缀表达式的值
  // 重载赋值运算符，用于设置中缀表达式
  virtual Calculator<ElemType>& operator=(const char* pszInfix);

 private:
  SqList<char> m_slInfix;    // 存储中缀表达式的顺序表
  SqList<char> m_slPostfix;  // 存储后缀表达式的顺序表

  int IspPriority(char chOperator);  // 获取运算符在栈内的优先级
  int IcpPriority(char chOperator);  // 获取运算符在栈外的优先级
  bool IsOperator(char chOperator);  // 判断字符是否为运算符
};

template <class ElemType>
inline Calculator<ElemType>::Calculator() {}

template <class ElemType>
inline Calculator<ElemType>::Calculator(const char* pszInfix) {
  *this = pszInfix;
}

template <class ElemType>
inline Calculator<ElemType>::~Calculator() {}

template <class ElemType>
inline const char* Calculator<ElemType>::GetInfix() {
  return &m_slInfix[0];  // 返回中缀表达式字符串的首地址
}

template <class ElemType>
inline const char* Calculator<ElemType>::GetPostfix() {
  return &m_slPostfix[0];  // 返回后缀表达式字符串的首地址
}

template <typename ElemType>
inline bool Calculator<ElemType>::InfixToPostfix() {
  int nPostfixIdx = 0;                  // 后缀表达式索引
  int nInfixIdx = 0;                    // 中缀表达式索引
  SqStack<char> ssOperator;             // 运算符栈
  char chInfix = m_slInfix[nInfixIdx];  // 当前处理的中缀表达式字符
  bool bLastWasOperator = true;  // 标记前一个字符是否为运算符

  ssOperator.Push('=');  // 使用 '=' 作为栈底标识符

  while (chInfix != '\0') {
    if (std::isdigit(chInfix) || chInfix == '.') {
      // 处理数字和小数点
      m_slPostfix[nPostfixIdx++] = chInfix;
      bLastWasOperator = false;
    } else if (IsOperator(chInfix)) {
      // 处理运算符
      m_slPostfix[nPostfixIdx++] = ' ';  // 插入空格分隔
      // 处理单目运算符
      if ((chInfix == '-' || chInfix == '+') && bLastWasOperator) {
        m_slPostfix[nPostfixIdx++] = '0';
        m_slPostfix[nPostfixIdx++] = ' ';
      }

      // 处理双目运算符的优先级
      char chStackTop;
      while (ssOperator.Top(chStackTop) &&
             IspPriority(chStackTop) >= IcpPriority(chInfix)) {
        if (chStackTop == '=') break;
        if (chStackTop != '(') {
          m_slPostfix[nPostfixIdx++] = chStackTop;
          m_slPostfix[nPostfixIdx++] = ' ';
        }
        ssOperator.Pop();
      }

      ssOperator.Push(chInfix);
      bLastWasOperator = true;
    } else if (chInfix == '(') {
      ssOperator.Push(chInfix);
    } else if (chInfix == ')') {
      // 处理右括号
      m_slPostfix[nPostfixIdx++] = ' ';
      char chStackTop;
      while (ssOperator.Top(chStackTop) && chStackTop != '(') {
        m_slPostfix[nPostfixIdx++] = chStackTop;
        ssOperator.Pop();
      }
      ssOperator.Pop();  // 弹出左括号
    } else {
      m_slPostfix[nPostfixIdx++] = ' ';  // 处理非法字符
    }

    chInfix = m_slInfix[++nInfixIdx];  // 处理下一个字符
  }

  // 处理栈中剩余的运算符
  char chStackTop;
  while (ssOperator.Top(chStackTop)) {
    if (chStackTop != '=' && chStackTop != '(') {
      m_slPostfix[nPostfixIdx++] = ' ';
      m_slPostfix[nPostfixIdx++] = chStackTop;
    }
    ssOperator.Pop();
  }

  if (nPostfixIdx == 0) return false;

  m_slPostfix[nPostfixIdx] = '\0';  // 添加字符串结束符

  return true;
}

template <class ElemType>
inline bool Calculator<ElemType>::EvaluatePostfix(ElemType& tValue) {
  if (m_slPostfix.Length() == 0) return false;

  tValue = ElemType();
  SqStack<ElemType> ssOperand;
  int nPostfixIdx = 0;
  char chPostfix = m_slPostfix[nPostfixIdx];
  bool bSuc = true;

  const std::type_info& tElemType = typeid(ElemType);
  const char* pszTypeName = tElemType.name();

  while (chPostfix != '\0') {
    if (std::isdigit(chPostfix) || chPostfix == '.') {
      // 处理数字
      char* pStop = NULL;
      ElemType tNum = ElemType();

      if (std::strcmp(pszTypeName, "double") == 0) {
        tNum = std::strtod(&m_slPostfix[nPostfixIdx], &pStop);
      } else if (std::strcmp(pszTypeName, "float") == 0) {
        tNum = std::strtof(&m_slPostfix[nPostfixIdx], &pStop);
      } else {
        tNum = std::strtol(&m_slPostfix[nPostfixIdx], &pStop, 10);
      }

      nPostfixIdx = static_cast<int>(pStop - &m_slPostfix[0]);
      ssOperand.Push(tNum);
    } else if (IsOperator(chPostfix)) {
      // 处理运算符
      ElemType tNum1 = ElemType(), tNum2 = ElemType();

      if (!ssOperand.Pop(tNum1) || !ssOperand.Pop(tNum2)) {
        bSuc = false;
        break;
      }

      ElemType tResult = ElemType();

      switch (chPostfix) {
        case '+':
          tResult = tNum2 + tNum1;
          break;
        case '-':
          tResult = tNum2 - tNum1;
          break;
        case '*':
          tResult = tNum2 * tNum1;
          break;
        case '/':
          if (tNum1 == 0) {
            bSuc = false;
            break;
          }
          tResult = tNum2 / tNum1;
          break;
        case '%':
          tResult = static_cast<int>(tNum2) % static_cast<int>(tNum1);
          break;
        case '^':
          tResult = std::pow(tNum2, tNum1);
          break;
        default:
          bSuc = false;
          break;
      }

      if (bSuc) {
        ssOperand.Push(tResult);
        ++nPostfixIdx;
      }
    } else {
      ++nPostfixIdx;  // 跳过非法字符
    }
    chPostfix = m_slPostfix[nPostfixIdx];
  }

  return bSuc && ssOperand.Pop(tValue);
}

template <class ElemType>
inline Calculator<ElemType>& Calculator<ElemType>::operator=(
    const char* pszInfix) {
  if (!pszInfix) {
    m_slInfix[0] = '\0';
    return *this;
  }

  int nIdx = 0;
  while (pszInfix[nIdx] != '\0') {
    m_slInfix[nIdx] = pszInfix[nIdx];
    ++nIdx;
  }
  m_slInfix[nIdx] = '\0';

  return *this;
}

template <class ElemType>
int Calculator<ElemType>::IspPriority(char chOperator) {
  // 返回运算符在栈内的优先级
  switch (chOperator) {
    case '=':
      return 0;
    case '(':
      return 1;
    case '+':
    case '-':
      return 3;
    case '*':
    case '/':
    case '%':
      return 5;
    case '^':
      return 7;
    case ')':
      return 8;
    default:
      return -1;
  }
}

template <typename ElemType>
inline int Calculator<ElemType>::IcpPriority(char chOperator) {
  // 返回运算符在栈外的优先级
  switch (chOperator) {
    case '=':
      return 0;
    case '(':
      return 8;
    case '+':
    case '-':
      return 2;
    case '*':
    case '/':
    case '%':
      return 4;
    case '^':
      return 6;
    case ')':
      return 1;
    default:
      return -1;
  }
}

template <class ElemType>
inline bool Calculator<ElemType>::IsOperator(char chOperator) {
  // 判断字符是否为有效运算符
  return chOperator == '+' || chOperator == '-' || chOperator == '/' ||
         chOperator == '=' || chOperator == '*' || chOperator == '^' ||
         chOperator == '%';
}

#endif  // _CALCULATOR_H_
