#include <stdio.h>
#include <string.h>

void swap(char *a, char *b) {
  char tmp = *a;
  *a = *b;
  *b = tmp;
}

void reverse(char *left, char *right) {
  while (left < right) {
    swap(left, right);
    left++;
    right--;
  }
}

int main(void) {
  char str[257] = {0};

  fgets(str, 257, stdin);
  str[strcspn(str, "\n")] = '\0';

  int len = strlen(str);
  char *left = str;
  char *right = &str[len - 1];

  reverse(left, right);

  char *start = str;
  char *end = start;

  while (*start) {
    while (*end != ' ' && *end != '\0') {
      ++end;
    }

    reverse(start, end - 1);

    if (*end == '\0') {
      break;
    }

    start = ++end;
  }

  printf("%s\n", str);

  return 0;
}