#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_
#include <cctype>
#include <cmath>
#include <typeinfo>

#include "sq_list.h"
#include "sq_stack.h"

template <class ElemType>
class Calculator {
 public:
  Calculator();                      // 无参构造函数
  Calculator(const char* cszInfix);  // 有参构造函数
  ~Calculator();                     // 析构函数

  const char* GetInfix();    // 获取中缀表达式
  const char* GetPostfix();  // 获取后缀表达式
  bool InfixToPostfix();     // 转换中缀表达式为后缀表达式
  bool EvaluatePostfix(ElemType& tValue);  // 计算后缀表达式
  // 重载赋值运算符
  virtual Calculator<ElemType>& operator=(const char* cszInfix);

 private:
  SqList<char> m_slInfix;    // 中缀表达式
  SqList<char> m_slPostfix;  // 后缀表达式

  int IspPriority(char chOperator);  // 栈内优先数
  int IcpPriority(char chOperator);  // 栈外优先数
  bool IsOperator(char chOperator);  // 判断是否为运算符
};

template <class ElemType>
inline Calculator<ElemType>::Calculator() {}

template <class ElemType>
inline Calculator<ElemType>::Calculator(const char* cszInfix) {
  *this = cszInfix;
}

template <class ElemType>
inline Calculator<ElemType>::~Calculator() {}

template <class ElemType>
inline const char* Calculator<ElemType>::GetInfix() {
  return &m_slInfix[0];  // 返回中缀表达式
}

template <class ElemType>
inline const char* Calculator<ElemType>::GetPostfix() {
  return &m_slPostfix[0];  // 返回后缀表达式
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
      // 如果是数字或小数点，直接写入后缀表达式
      m_slPostfix[nPostfixIdx++] = chInfix;
      bLastWasOperator = false;          // 当前为操作数，设置为 false
    } else if (IsOperator(chInfix)) {    // 若为运算符
      m_slPostfix[nPostfixIdx++] = ' ';  // 插入空格以分隔
      // 如果是单目运算符且前面是运算符，需要加上 '0'
      if ((chInfix == '-' || chInfix == '+') && bLastWasOperator) {
        m_slPostfix[nPostfixIdx++] = '0';  // 插入 '0' 作为单目运算符的操作数
        m_slPostfix[nPostfixIdx++] = ' ';  // 插入空格分隔操作数
      }

      // 若为双目运算符，处理栈内优先级
      char chStackTop;  // 栈顶元素用于比较优先级
      while (ssOperator.Top(chStackTop) &&
             IspPriority(chStackTop) >= IcpPriority(chInfix)) {
        if (chStackTop == '=') {
          break;  // 栈顶为 '='，结束出栈
        }

        if (chStackTop != '(') {  // 弹出栈顶元素，直到遇到 '('
          m_slPostfix[nPostfixIdx++] = chStackTop;
          m_slPostfix[nPostfixIdx++] = ' ';  // 运算符之间留下空格
        }
        ssOperator.Pop();  // 弹出栈顶元素
      }

      ssOperator.Push(chInfix);  // 将当前运算符压入栈中
      bLastWasOperator = true;   // 刚处理完运算符，标记为 true
    } else if (chInfix == '(') {
      ssOperator.Push(chInfix);  // 遇到左括号，直接压入栈中
    } else if (chInfix == ')') {
      m_slPostfix[nPostfixIdx++] = ' ';  // 运算符之间留下空格
      // 遇到右括号，弹出栈顶运算符直到遇到左括号
      char chStackTop;
      while (ssOperator.Top(chStackTop) && chStackTop != '(') {
        m_slPostfix[nPostfixIdx++] = chStackTop;
        ssOperator.Pop();
      }
      ssOperator.Pop();  // 弹出左括号 '('
    } else {
      m_slPostfix[nPostfixIdx++] = ' '; // 遇到非法字符则增添空格
    }

    // 非法字符直接无视
    chInfix = m_slInfix[++nInfixIdx];  // 遍历下一个中缀表达式字符
  }

  // 遍历结束，弹出栈中剩余运算符
  char chStackTop;
  while (ssOperator.Top(chStackTop)) {  // 当栈顶不为空时
    if (chStackTop != '=' && chStackTop != '(') {
      m_slPostfix[nPostfixIdx++] = ' ';  // 在操作数、运算符之间添加空格
      m_slPostfix[nPostfixIdx++] = chStackTop;
    }
    ssOperator.Pop();  // 弹出栈顶元素
  }

  if (nPostfixIdx == 0) {
    return false;  // 若后缀表达式为空，返回 false
  }

  m_slPostfix[nPostfixIdx] = '\0';  // 添加字符串结束符 '\0'

  return true;
}

template <class ElemType>
inline bool Calculator<ElemType>::EvaluatePostfix(ElemType& tValue) {
  if (m_slPostfix.Length() == 0) {
    return false;  // 安全性检查
  }

  tValue = ElemType();          // 初始化输出值
  SqStack<ElemType> ssOperand;  // 存放操作数的栈
  int nPostfixIdx = 0;          // 后缀表达式当前位置索引
  char chPostfix = m_slPostfix[nPostfixIdx];  // 当前处理的字符
  bool bSuc = true;                           // 成功标志

  const std::type_info& tElemType = typeid(ElemType);  // 获取数据类型
  const char* cszTypeName = tElemType.name();          // 获取类型名称

  while (chPostfix != '\0') {  // 不为字符串末尾时进行遍历
    // 若为数字字符或小数点
    if (std::isdigit(chPostfix) || chPostfix == '.') {
      char* pStop = NULL;  // 字符串转换末尾

      ElemType tNum = ElemType();  // 初始化操作数

      if (std::strcmp(cszTypeName, "double") == 0) {
        // 处理 double 类型
        tNum = std::strtod(&m_slPostfix[nPostfixIdx], &pStop);
      } else if (std::strcmp(cszTypeName, "float") == 0) {
        // 处理 float 类型
        tNum = std::strtof(&m_slPostfix[nPostfixIdx], &pStop);
      } else {
        // 处理 int 类型
        tNum = std::strtol(&m_slPostfix[nPostfixIdx], &pStop, 10);
      }

      nPostfixIdx = static_cast<int>(pStop - &m_slPostfix[0]);
      ssOperand.Push(tNum);

    } else if (IsOperator(chPostfix)) {
      ElemType tNum1 = ElemType();  // 操作数 1
      ElemType tNum2 = ElemType();  // 操作数 2

      // 当弹出的数不足两个
      if (!ssOperand.Pop(tNum1) || !ssOperand.Pop(tNum2)) {
        bSuc = false;  // 标记错误
        break;
      }

      ElemType tResult = ElemType();  // 运算结果

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
          if (tNum1 == 0) {  // 排除 0 值
            bSuc = false;
            break;
          }
          tResult = tNum2 / tNum1;
          break;
        case '%':  // 转换为 int 类型
          tResult = static_cast<int>(tNum2) % static_cast<int>(tNum1);
          break;
        case '^':
          tResult = std::pow(tNum2, tNum1);
          break;
        default:  // 未知状况
          bSuc = false;
          break;
      }

      if (bSuc) {                 // 如果过程无误
        ssOperand.Push(tResult);  // 将运算结果压入栈中
        ++nPostfixIdx;            // 索引增加
      }
    } else {
      ++nPostfixIdx;  // 非法字符，直接跳过
    }
    chPostfix = m_slPostfix[nPostfixIdx];  // 更新字符
  }

  // 当过程无误并且栈不为空
  return bSuc && ssOperand.Pop(tValue);
}

template <class ElemType>
inline Calculator<ElemType>& Calculator<ElemType>::operator=(
    const char* cszInfix) {
  if (!cszInfix) {
    m_slInfix[0] = '\0';  // 安全性检测
    return *this;
  }

  int nIdx = 0;
  while (cszInfix[nIdx] != '\0') {
    m_slInfix[nIdx] = cszInfix[nIdx];  // 逐字符进行拷贝
    ++nIdx;
  }
  m_slInfix[nIdx] = '\0';  // 以 '\0' 结尾，标志字符串结束

  return *this;
}

template <class ElemType>
inline int Calculator<ElemType>::IspPriority(char chOperator) {
  int nPriority = -1;

  switch (chOperator) {
    case '=':
      nPriority = 0;
      break;
    case '(':
      nPriority = 1;
      break;
    case '+':
    case '-':
      nPriority = 3;
      break;
    case '*':
    case '/':
    case '%':
      nPriority = 5;
      break;
    case '^':
      nPriority = 7;
      break;
    case ')':
      nPriority = 8;
      break;
    default:
      nPriority = -1;
      break;
  }

  return nPriority;
}

template <typename ElemType>
inline int Calculator<ElemType>::IcpPriority(char chOperator) {
  int nPriority = 0;

  switch (chOperator) {
    case '=':
      nPriority = 0;
      break;
    case '(':
      nPriority = 8;
      break;
    case '+':
    case '-':
      nPriority = 2;
      break;
    case '*':
    case '/':
    case '%':
      nPriority = 4;
      break;
    case '^':
      nPriority = 6;
      break;
    case ')':
      nPriority = 1;
      break;
    default:
      nPriority = -1;
      break;
  }

  return nPriority;
}

template <class ElemType>
inline bool Calculator<ElemType>::IsOperator(char chOperator) {
  return chOperator == '+' || chOperator == '-' || chOperator == '/' ||
         chOperator == '=' || chOperator == '*' || chOperator == '^' ||
         chOperator == '%';
}

#endif  // _CALCULATOR_H_
