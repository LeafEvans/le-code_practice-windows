#include <stdio.h>

int main(void) {
  float price = 0.0f;
  int m = 0;
  int d = 0;
  int flag = 0;

  scanf("%f %d %d %d", &price, &m, &d, &flag);
  if (m == 12 && d == 12) {
    price = price * 0.8 - flag * 50.0;
  } else if (m == 11 && d == 11) {
    price = price * 0.7 - flag * 50.0;
  }

  if (price <= 0.0f) {
    printf("%.2f\n", 0.00);
  } else {
    printf("%.2f\n", price);
  }

  return 0;
}