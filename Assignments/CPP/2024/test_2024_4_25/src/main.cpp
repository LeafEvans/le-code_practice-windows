// #include <iostream>
//
// using namespace std;
//
// template <class T>
// void my_swap(T &a, T &b) {
//   const T temp = a;
//   a = b;
//   b = temp;
// }
//
// template <class T>
// void bubble_sort(T *arr, const int len) {
//   for (int i = 0; i < len - 1; ++i) {
//     for (int j = 0; j < len - 1 - i; ++j) {
//       if (arr[j] > arr[j + 1]) my_swap(arr[j], arr[j + 1]);
//     }
//   }
// }
//
// int main() {
//   int arr[10] = {32, 32, 44, 55, 22, 12, 2131, 323, 232, 23};
//   bubble_sort(arr, 10);
//   for (const int item : arr) {
//     cout << item << " ";
//   }
//   cout << '\n';
//   return 0;
// }
