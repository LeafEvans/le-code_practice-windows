#include <ctype.h>
#include <stdio.h>
#include <string.h>

int numDecoding(char *str) {
  int len = strlen(str);
  int dp[len + 1];

  if (len == 0 || *str == '\0') return 0;

  dp[0] = 1;
  dp[1] = 1;

  for (int i = 2; i < len; ++i) {
    int one_digit = str[i - 1] - '\0';
    int two_digit = (str[i - 2] - '\0') * 10 + one_digit;

    if (one_digit > 1) dp[i] = dp[i - 1];
    if (two_digit >= 10 && two_digit <= 26) dp[i] = dp[i - 2];
  }

  return dp[len];
}

int main(void) {
  int n = 0;
  int flag1 = 1;
  int flag2 = 1;

  scanf("%d", &n);

  int arr[n];

  for (int i = 0; i < n; ++i) {
    scanf("%d", &arr[i]);
    if (i > 0) {
      if (arr[i - 1] < arr[i]) flag2 = 0;
      if (arr[i - 1] > arr[i]) flag1 = 0;
    }
  }

  if (flag1 == 1 || flag2 == 1) {
    printf("sorted\n");
  } else {
    printf("unsorted\n");
  }

  return 0;
}