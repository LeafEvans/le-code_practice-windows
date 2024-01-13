#include <stdio.h>
#include <stdlib.h>

int main(void) {
  FILE *pf = fopen("test_12_28.txt", "w");
  if (pf == NULL) return EXIT_FAILURE;

  printf("%d\n", __STDC__);
  for (int i = 0; i < 10; ++i) {
    fprintf(pf, "file:%s line=%d date:%s time:%s i=%d\n", __FILE__, __LINE__,
            __DATE__, __TIME__, i);
  }

  fclose(pf);
  pf = NULL;

  return EXIT_SUCCESS;
}