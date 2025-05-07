#include <stdio.h>
#include <string.h>

double calculator(char *ptr) {
  double num1 = 0.0;
  double num2 = 0.0;
  char op = 0;

  if (sscanf(ptr, "%lf%c%lf", &num1, &op, &num2) != 3) {
    return 0.0;
  }

  switch (op) {
    case '*':
      return num1 * num2;
    case '-':
      return num1 - num2;
    case '+':
      return num1 + num2;
    case '/':
      if (num2 == 0) {
        return 0.0;
      } else {
        return num1 / num2;
      }
    default:
      return 0.0;
  }
}

int main(void) {
  char str[10] = {0};
  scanf("%s", str);
  printf(calculator(str) == 0.0 ? "Input Error\n" : "%.2lf", calculator(str));
  return 0;
}