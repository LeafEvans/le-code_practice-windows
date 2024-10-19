#include <stdio.h>

int main(void) {
  int signal_num = 0;
  int n = 0;
  int num = 0;
  scanf("%d", &n);

  for (int i = 0; i < n; ++i) {
    scanf("%d", &num);
    signal_num ^= num;
  }

  printf("%d\n", signal_num);

  return 0;
}