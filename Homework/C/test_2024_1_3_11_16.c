#include <math.h>
#include <stdio.h>

void printAvgAndVar(double arr[]) {
  double avg = 0.0;
  double var = 0.0;

  for (int i = 0; i < 6; ++i) {
    avg += arr[i];
  }
  avg /= 6.0;

  for (int i = 0; i < 6; ++i) {
    var += pow((arr[i] - avg), 2);
  }
  var /= 6.0;

  printf("%.2lf %.2lf\n", avg, var);
}

int main(void) {
  int n = 0;
  double arr[6] = {0.0};

  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 6; ++j) {
      scanf("%lf", &arr[j]);
    }
    printAvgAndVar(arr);
  }

  return 0;
}