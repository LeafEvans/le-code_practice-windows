#include <stdio.h>
#include <string.h>

void reverseStr(char *left, char *right) {
  while (left < right) {
    char tmp = *left;
    *left = *right;
    *right = tmp;
    left++;
    right--;
  }
}

void leftRotateA(char str[], int k) {
  int len = strlen(str);
  k %= len;
  reverseStr(str, str + k - 1);
  reverseStr(str + k, str + len - 1);
  reverseStr(str, str + len - 1);
}

int isLeftRotateA(char str1[], char str2[]) {
  int len1 = strlen(str1);
  int len2 = strlen(str2);

  if (len1 != len2) {
    return 0;
  } else {
    while (len1) {
      if (strcmp(str1, str2) == 0) {
        return 1;
      }
      leftRotateA(str1, 1);
      len1--;
    }
  }

  return 0;
}

int isLeftRotateB(char str1[], char str2[]) {
  int len1 = strlen(str1);
  int len2 = strlen(str2);
  if (len1 != len2) {
    return 0;
  } else {
    strncat(str1, str1, len1);  // 直接用 strcat 会导致 \0 被覆盖，从而陷入死循环
  }

  return strstr(str1, str2) == NULL ? 0 : 1;
}

int main(void) {
  char str1[20] = "abcdef";
  char str2[20] = "cdecde";
  int ret = isLeftRotateB(str1, str2);
  printf(ret ? "yes\n" : "no\n");
  return 0;
}