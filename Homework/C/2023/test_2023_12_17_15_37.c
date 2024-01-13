#include <stdio.h>

int main(void) {
  int n = 0;
  scanf("%d", &n);
  char *str[n];
  int arr[2][n];

  for (int i = 0; i < n; ++i) {
    scanf("%s", str[i]);
    sscanf(str, "%d/%d", &arr[0][i], &arr[1][i]);
  }
 
}