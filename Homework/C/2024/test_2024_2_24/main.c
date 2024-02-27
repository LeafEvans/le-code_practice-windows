#include <limits.h>

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void bubbleSort(int arr[], int size) {
  int i, j;
  
  for (i = 0; i < size - 1; ++i) {
  	for (j = 0; j < size - 1 - i; ++j) {
  		if (arr[j] > arr[j + 1]) swap(&arr[j], &arr[j + 1]);
    }
  }
}

int main(void) {
  int i;
  int arr[10] = {1, 23, 42, 78, 2, 9, 12, 54, 3, 21};
  
  bubbleSort(arr, sizeof(arr) / sizeof(arr[0]));
  
  for (i = 0; i < 10; ++i) {
  	printf("%d ", arr[i]);
  }
  putchar('\n');
  
  return 0;
}
