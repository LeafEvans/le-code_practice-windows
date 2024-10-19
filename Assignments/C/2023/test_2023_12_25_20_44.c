#include <stdio.h>

int reverseNum(int num) {
  int reverse_num = 0;
  while (num) {
    reverse_num = reverse_num * 10 + num % 10;
    num /= 10;
  }
  return reverse_num;
}

int isPalindrome(int num) { return reverseNum(num) == num ? 1 : 0; }

int main(void) {
  while (1) {
    int n = 0;
    scanf("%d", &n);
    if (n == 0) break;

    while (1) {
      ++n;
      if (isPalindrome(n)) {
        printf("%d\n", n);
        break;
      }
    }
  }
  return 0;
}