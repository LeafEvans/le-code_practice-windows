// #include <stdio.h>
//
// int function(int a, int b) { return 1 + a + b; }
//
// int main(void) {
//   int n = 0;
//   scanf_s("%d", &n);
//   printf("%d", n);
//   return 0;
// }
// #include <stdio.h>
// #include <stdlib.h>
//
// int main() {
//  int arr[10] = {0};
//  srand(120);
//  for (int i = 0; i < 10; ++i) {
//    ++arr[rand() % 10];
//  }
//  for (int i = 0; i < 10; ++i) {
//    printf("%d ", arr[i]);
//  }
//  printf("\n");
//  return 0;
//}
// #define _CRT_SECURE_NO_WARNINGS
// #include <stdio.h>
// #include <stdlib.h>
// int *make_array(int elem, int val);
// void show_array(const int ar[], int n);
// int main() {
//  int *pa;
//  int size;
//  int value;
//
//  printf("Enter the number of elements: ");
//  while (scanf("%d", &size) == 1 && size > 0) {
//    printf("Enter the initialization value: ");
//    scanf("%d", &value);
//    pa = make_array(size, value);
//    if (pa) {
//      show_array(pa, size);
//      free(pa);
//    }
//    printf("Enter the number of elements (<1 to quit): ");
//  }
//  printf("Done.\n");
//  return 0;
//}
//
// int *make_array(int elem, int val) {
//  int *ar = (int *)malloc(sizeof(int) * elem);
//  if (ar) {
//    for (int i = 0; i < elem; ++i) {
//      ar[i] = val;
//    }
//  }
//  return ar;
//}
//
// void show_array(const int ar[], int n) {
//  for (int i = 0; i < n; ++i) {
//    printf("%d ", ar[i]);
//  }
//  printf("\n");
//}
// #define _CRT_SECURE_NO_WARNINGS
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
//
// int main() {
//  int n;
//  char temp[50];
//  printf("How many words do you want to enter? ");
//  scanf("%d", &n);
//  char(*ar)[100];
//  ar = malloc(sizeof(char(*)[100]) * n);
//  if (!ar) return EXIT_FAILURE;
//  printf("Enter %d words now:\n", n);
//  for (int i = 0; i < n; ++i) {
//    scanf("%s", temp);
//    strcpy(ar[i], temp);
//  }
//  for (int i = 0; i < n; ++i) {
//    printf("%s\n", ar[i]);
//  }
//  return 0;
//}

