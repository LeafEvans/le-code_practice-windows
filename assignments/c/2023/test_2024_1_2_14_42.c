#include <stdio.h>

void isSeries(int arr[]) {
  if (2 * arr[1] == arr[0] + arr[2] && 2 * arr[2] == arr[1] + arr[3] &&
      2 * arr[3] == arr[2] + arr[4]) {
    printf("case one\n");
    for (int i = 5; i < 10; ++i) {
      arr[i] = arr[i - 1] + arr[1] - arr[0];
      printf("%d ", arr[i]);
    }
    printf("\n");
  }

  if (arr[1] * arr[1] == arr[0] * arr[2] &&
      arr[2] * arr[2] == arr[1] * arr[3] &&
      arr[3] * arr[3] == arr[2] * arr[4]) {
    printf("case two\n");
    for (int i = 5; i < 10; ++i) {
      arr[i] = arr[i - 1] * (arr[1] / arr[0]);
      printf("%d ", arr[i]);
    }
    printf("\n");
  }

  if (arr[2] == arr[1] + arr[0] && arr[3] == arr[2] + arr[1] &&
      arr[4] == arr[3] + arr[2]) {
    printf("case three\n");
    for (int i = 5; i < 10; ++i) {
      arr[i] = arr[i - 1] + arr[i - 2];
      printf("%d ", arr[i]);
    }
    printf("\n");
  }
}

int main(void) {
  int arr[10] = {0};

  while (1) {
    for (int i = 0; i < 5; ++i) {
      scanf("%d", &arr[i]);
    }
    if (arr[0] == 0 && arr[1] == 0 && arr[2] == 0 && arr[3] == 0 &&
        arr[4] == 0) {
      break;
    }
    isSeries(arr);
  }

  return 0;
}