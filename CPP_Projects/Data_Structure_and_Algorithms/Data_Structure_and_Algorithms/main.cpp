#include <iostream>
#include <string>

#include "Calculator.h"
#include "simple_circle_list.h"

static void Josephus(int n, int m) {
  SimpleCircleList<int> scl;  // 定义空循环链表
  int nOut, nWiner = 0;

  for (int i = 0; i < n; ++i) {
    scl.Insert(i, i + 1);  // 建立数据为 1, 2,..., n 的循环链表
  }

  scl.Head();  // 让当前节点返回头节点

  for (int i = 0; i < n - 1; ++i) {
    // 循环 n - 1 次，让 n - 1 个人出列
    for (int j = 0; j < m; ++j) {
      // 报数 m 次
      int nData;
      scl.Next(nData);
    }
    // 删除当前节点
    scl.DeleteCur(nOut);
    std::cout << nOut << std::endl;
  }

  // 得到这个元素
  scl.GetElem(0, nWiner);
  std::cout << std::endl << "优胜者: " << nWiner << std::endl;
}

int main() {
  Calculator<double> calc;
  char chChoice = '\0';
  std::string strInfix;
  double dblResult = .0;
  do {
    std::cout << "输入表达式:" << std::endl;
    std::getline(std::cin, strInfix);

    if (strInfix.empty()) {
      break;
    }

    calc = strInfix.c_str();

    // 转换为后缀表达式
    if (calc.InfixToPostfix()) {
      std::cout << "后缀表达式: " << std::endl
                << calc.GetPostfix() << std::endl;

      if (calc.EvaluatePostfix(dblResult)) {
        std::cout << "计算结果: " << dblResult << std::endl;
      } else {
        std::cerr << "后缀表达式计算失败!" << std::endl;
      }
    } else {
      std::cerr << "中缀表达式转换失败!" << std::endl;
    }

    std::cout << "是否继续(y/n)?";
    std::cin >> chChoice;
    std::cin.ignore();  // 忽略换行符

  } while (chChoice != 'n');

  return 0;
}
