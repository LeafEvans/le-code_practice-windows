#include <stdio.h>

int main(void) {
  float chinese = 0.0f;
  float math = 0.0f;
  float english = 0.0f;
  float avg = 0.0f;

  scanf("%f %f %f", &chinese, &math, &english);
  avg = (chinese + math + english) / 3.0;

  if (avg >= 0.0 && avg < 20.0) {
    printf("E\n");
  } else if (avg >= 20.0 && avg < 40.0) {
    printf("D\n");
  } else if (avg >= 40.0 && avg < 60.0) {
    printf("C\n");
  } else if (avg >= 60.0 && avg < 80.0) {
    printf("B\n");
  } else {
    printf("A\n");
  }

  return 0;
}