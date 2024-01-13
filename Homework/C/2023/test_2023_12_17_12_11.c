#include <stdio.h>

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int main(void) {
  int arr[10] = {0};
  int min = 0;
  int max = 9;

  for (int i = 0; i < 10; ++i) {
    scanf("%d", &arr[i]);
    if (arr[i] < arr[min]) min = i;
    if (arr[i] > arr[max]) max = i;
  }

  swap(&arr[0], &arr[min]);
  swap(&arr[9], &arr[max]);

  for (int i = 0; i < 10; ++i) printf("%d ", arr[i]);

  return 0;
}