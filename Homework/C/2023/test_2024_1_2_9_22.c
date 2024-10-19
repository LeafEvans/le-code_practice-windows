#include <stdio.h>
#include <string.h>

int numDecode(const char *str) {
  int i = 0;              // 遍历用的变量
  int dp[71] = {0};       // 初始化，表示 dp[i] 表示 i 位置的解法
  int len = strlen(str);  // 计算字符串长度

  dp[0] = 1;  // 假设长度为 0 的字符串解法一种
  dp[1] = 1;  // 长度为 1 的字符串解法一种
  if (len == 0 || str[0] == '0')
    return 0;  // 当为空字符串或者首字符为 0，就跳出

  for (i = 2; i <= len; ++i) {
    // 因为字符串的 i 会比 dp 的 i 少一个，i - 1 代表第 i 个
    int one_digit = str[i - 1] - '0';
    int two_digit = 10 * (str[i - 2] - '0') + one_digit;  // 计算两位数的可能性

    if (one_digit >= 1 && one_digit <= 9) {
      dp[i] += dp[i - 1];  // 存在就增加
    }

    if (two_digit >= 10 && two_digit <= 26) {
      dp[i] += dp[i - 2];
    }
  }

  return dp[len];
}

int main(void) {
  int n = 0;
  char str[71] = {0};
  scanf("%d", &n);

  for (int i = 0; i < n; ++i) {
    scanf("%s", str);
    printf("%d\n", numDecode(str));
  }

  return 0;
}