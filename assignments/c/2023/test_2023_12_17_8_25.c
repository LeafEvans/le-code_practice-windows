#include <stdio.h>

struct Note {
  int date;
  struct Note* next;
};

struct Point {
  int x;
  int y;
} p1 = {2, 3};

struct Stu {
  char name[20];
  int age;
  struct Sco s;
};

struct Sco {
  int n;
  char ch;
};

int main(void) {
  int i = 0;
  struct Point p2 = {3, 4, {3, "hello"}};
  struct Stu s1 = {"张三", 29};
  return 0;
}