#include <stdio.h>

int main(void) {
  int n = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int a = 0;
    scanf("%d", &a);
    int arr[5] = {0};
    for (int i = 0; i < 5; ++i) {
      arr[i] = a + i;
    }
    for (int k1 = 0; k1 < 5; ++k1) {
      for (int k2 = 0; k2 < 5; ++k2) {
        for (int k3 = 0; k3 < 5; ++k3) {
          for (int k4 = 0; k4 < 5; ++k4) {
            for (int k5 = 0; k5 < 5; ++k5) {
              if (arr[k1] != arr[k2] && arr[k1] != arr[k3] &&
                  arr[k1] != arr[k4] && arr[k1] != arr[k5] &&
                  arr[k2] != arr[k3] && arr[k2] != arr[k4] &&
                  arr[k2] != arr[k5] && arr[k3] != arr[k4] &&
                  arr[k3] != arr[k5] && arr[k4] != arr[k5]) {
                printf("%d%d%d%d%d\n", arr[k1], arr[k2], arr[k3], arr[k4],
                       arr[k5]);
              }
            }
          }
        }
      }
    }
  }
  return 0;
}