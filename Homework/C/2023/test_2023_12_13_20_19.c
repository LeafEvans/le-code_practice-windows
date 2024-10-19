#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

void encryption(char *str, const char *key) {
  int i = 0;
  int j = 0;
  int str_len = strlen(str);
  int key_len = strlen(key);

  while (i < str_len) {
    while (j < key_len && str[i] != '\0') {
      str[i] = (str[i] + key[j]) % 26 + 'A';
      ++i;
      ++j;
    }
    j = 0;
  }
}

void decrypt(char *str, const char *key) {
  int i = 0;
  int j = 0;
  int str_len = strlen(str);
  int key_len = strlen(key);

  while (i < str_len) {
    while (j < key_len && str[i] != '\0') {
      str[i] = (str[i] - key[j] + 26) % 26 + 'A';
      // +26 可以防止负数的产生，理论上可以 +26 的任意倍数，因为取模都会取掉
      ++i;
      ++j;
    }
    j = 0;
  }
}

int main(void) {
  char str[MAX_LEN] = {0};
  char key[MAX_LEN] = {0};

  scanf("%s", str);
  scanf("%s", key);

  encryption(str, key);
  printf("%s\n", str);
  decrypt(str, key);
  printf("%s\n", str);

  return 0;
}