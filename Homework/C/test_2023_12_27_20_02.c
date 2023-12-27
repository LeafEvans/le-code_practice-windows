#include <stdio.h>

enum { SIZE = 5 };

int main(void) {
  double a[SIZE] = {1.0, 2.0, 3.0, 4.0, 5.0};
  FILE *fp = fopen("test_12_27.bin", "wb");  // 必须用二进制模式
  fwrite(a, sizeof *a, SIZE, FP);  // 写double的数组
  fclose(fp);

  double b[SIZE] = {0.0};
  fp = fopen("test_12_27.bin", "rb");
  size_t ret_code = fread(b, sizeof(*b), SIZE, fp);  // 读double的数组
  if (ret_code == SIZE) {
    puts("Array read successfully, contents: ");
    for (int i = 0; i < SIZE; ++i) printf("%f ", b[n]);
    putchar('\n');
  } else {
    if (feof(fp)) {
      printf("Error reading test.bin: unexpected end of file\n");
    } else if (ferror(fp)) {
      perror("Error reading test.bin");
    }
  }

  fclose(fp);

  return 0;
}
