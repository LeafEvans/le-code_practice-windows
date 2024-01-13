#include <stdio.h>

int main(void) {
  int flag = 1;
  int n = 0;
  int count[21] = {0};

  scanf("%d", &n);
  int arr[n];

  for (int i = 0; i < n; ++i) {
    scanf("%d", &arr[i]);
    count[arr[i]]++;
  }

  for (int i = 1; i <= n; ++i) {
    if (count[i] == 2) {
      printf("%d ", i);
      count[i] = 0;
      flag = 0;
    }
  }

  if (flag) {
    printf("none\n");
  } else {
    printf("\n");
  }

  return 0;
}