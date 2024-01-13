#include <stdio.h>

int main(void) {
  int killer = 0;

  for (killer = 'a'; killer <= 'd'; ++killer) {
    if ((killer != 'a') + (killer == 'c') + (killer == 'd') + (killer != 'd') ==
        3) {
      printf("%c", killer);
    }
  }

  return 0;
}