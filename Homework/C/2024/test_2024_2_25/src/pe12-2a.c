#define _CRT_SECURE_NO_WARNINGS
#include "../inc/pe12-2a.h"

#include <stdio.h>

void set_mode(int *p_mode) {
  int temp = 0;
  scanf("%d", &temp);
  if (temp == -1) {
    *p_mode = temp;
    return;
  }
  if (!(temp >= 0 && temp <= 1) ) {
    printf("Invalid mode specified. Mode ");
    printf(*p_mode == 0 ? "0(metric) used.\n" : "1(US) used.\n");
    return;
  }
}

void get_info(int mode, double *p_distance, double *p_fuel) {
  if (mode == 0) {
    printf("Enter distance traveled in killometers: ");
    scanf("%lf", p_distance);
    printf("Enter fuel consumed in liters: ");
    scanf("%lf", p_fuel);
  } else {
    printf("Enter distance traveled in miles: ");
    scanf("%lf", p_distance);
    printf("Enter fuel consumed in gallons: ");
    scanf("%lf", p_fuel);
  }
}

void show_info(int mode, double distance, double fuel) {
  if (mode == 1) {
    printf("Fuel consumption is %.1lf miles per gallon.\n", distance / fuel);
  } else {
    printf("Fuel consumption is %.2lf liters per 100 km.\n",
           fuel * 100 / distance);
  }
}
