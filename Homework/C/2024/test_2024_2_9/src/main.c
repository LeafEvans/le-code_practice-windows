/* #include <stdio.h>

#define OFFSETOF(type, m_name) (size_t) & (((type*)0)->m_name) */

/* int main(int argc, char** argv) {
  printf("hello world!\n");
  return 0;
} */

/* struct S {
  char c1;
  int i;
  char c2;
};

int main(void) {
  struct S s = {0};
  printf("%zu\n", OFFSETOF(struct S, c2));
  return 0;
} */

/* #include <stdio.h>

int main(void) {
  int n;
  while (scanf("%d", &n) == 1) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n - i; ++j) {
        printf("  ");
      }
      for (int j = 0; j <= i; j++) {
        printf("*");
      }
      printf("\n");
    }
    for (int i = 0; i < n + 1; i++) {
      for (int j = 0; j < i; j++) {
        printf("  ");
      }
      for (int j = 0; j < n + 1 - i; j++) {
        printf("*");
      }
      printf("\n");
    }
  }
  return 0;
} */

/* #include <stdio.h>

int main(void) {
  int score = 0;
  int sum = 0;
  int n = 0;
  int max = 0;
  int min = 100;
  while (scanf("%d", &score) == 1) {
    ++n;
    if (score > max) max = score;
    if (score < min) min = score;
    sum += score;
    if (n == 7) {
      printf("%.2lf\n", (sum - max - min) / 5.0);
      n = 0;
      max = 0;
      min = 100;
      sum = 0;
    }
  }
  return 0;
} */

/* #include <stdio.h>

void findSingleDog(int arr[], int sz, int *pd1, int *pd2) {
  int ret = 0;  // 最后异或的数
  for (int i = 0; i < sz; ++i) {
    ret ^= arr[i];
  }

  int pos = 0;  // 找出第一个是 1 的位数
  for (pos = 0; pos < 32; ++pos) {
    if (((ret >> pos) & 1) == 1) break;
  }

  for (int i = 0; i < sz; ++i) {
    if (((arr[i] >> pos) & 1) == 1) {
      *pd1 ^= arr[i];  // 分组异或
    } else {
      *pd2 ^= arr[i];
    }
  }
}

int main(void) {
  int arr[] = {1, 2, 3, 4, 5, 1, 2, 3, 4, 6};
  int sz = sizeof(arr) / sizeof(arr[0]);
  int dog1 = 0;
  int dog2 = 0;
  findSingleDog(arr, sz, &dog1, &dog2);
  printf("%d %d\n", dog1, dog2);
  return 0;
} */

/*
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdio.h>


enum Status { VALID, INVALID } sta = INVALID;  // 定义状态，初始化为非法

int my_atoi(const char* str) {
  assert(str);        // 判断是否为合法的字符串
  long long ret = 0;  // 判断是否为合适的整数的数
  int flag = 1;       // 判断是否为正数

  if (*str == '\0') return 0;  // 如果是结束字符，就返回，此时依旧是非法状态
  while (isspace(*str)) str++;  // 是空格的话，就跳过
  if (*str == '+') {  // 是加号的话，就定义为正数，同时跳过这个符号字符
    flag = 1;
    ++str;
  } else if (*str == '-') {  // 对于负数，类似的
    flag = -1;               // 不过把符号定成负的
    ++str;
  }

  while (*str) {  // 当这个字符不是结束字符的时候，循环
    if (isdigit(*str)) {  // 如果是数字字符，就将它放进那个数，并加上符号
      ret = ret * 10 + flag * (*str - '0');
      if (ret > INT_MAX || ret < INT_MIN) return 0;  // 超出范围就非法
    } else
      return (int)ret;  // 如果不是数字字符，也是非法的
    ++str;
  }
  if (*str == '\0') sta = VALID;  // 前面的都通过了，说明合法，改变状态
  return (int)ret;  // 强制类型转换，转换成普通的整形
}

int main(void) {
  char arr[20] = "         -1234 56a";
  int ret = my_atoi(arr);
  if (sta == INVALID) {
    printf("非法返回：%d\n", ret);
  } else {
    printf("合法转换：%d\n", ret);
  }
  printf("%d\n", ret);
  return 0;
} */

/* #define INT_PTR int*
typedef int* int_ptr;

int *a, b;     // a 的类型是 int*，b 的类型是 int
int_ptr c, d;  // c 和 d 都是指针类型
 */

/* #include <stdio.h>
// 奇偶位交换
#define SWAP_BIT(n) (((n & 0x55555555) << 1) + ((n & 0xaaaaaaaa) >> 1))
// 通过分别保留奇数位和偶数位来达到目的，然后将两者相加
int main(void) {
  int n = 0;
  scanf("%d", &n);
  n = SWAP_BIT(n);
  printf("%d\n", n);
  return 0;
} */

/* #include <stdio.h>

int main(void) {
  unsigned char i = 7;
  int j = 0;
  for (; i > 0; i -= 3) {
    ++j;
  }
  printf("%d\n", j);
  return 0;
} */

/* #include <stdio.h>

int main(void) {
  char a = 0, ch;
  while ((ch = getchar()) != '\n') {
    if (a % 2 != 0 && (ch >= 'a' && ch <= 'z')) {
      ch = ch - 'a' + 'A';
    }
    a++;
    putchar(ch);
  }
  printf("\n");
  return 0;
} */

/* #include <stdio.h>
#include <stdlib.h>

int main(void) {
  int n = 0;          // 指定的数字
  int a = 0;          // 用于斐波那契的数字
  int b = 1;          // 第二个用于斐波那契的数字
  int c = 0;          // 第三个用于斐波那契的数字
  scanf("%d", &n);    // 输入数字
  while (1) {         // 先循环再说
    if (n == b) {     // 如果这个数与右边界相等，那最短就是 0
      printf("0\n");  // 打印 0 出来
      break;          // 跳出循环
    } else if (n < b) {  // 如果比右边界小，就要判断大小
      if (abs(a - n) > abs(b - n)) {  // 看看是离哪个边界近
        printf("%d\n", abs(b - n));
      } else {
        printf("%d\n", abs(a - n));
      }
      break;
    }
    c = a + b;  // 更新数列
    a = b;
    b = c;
  }
  return 0;
} */

