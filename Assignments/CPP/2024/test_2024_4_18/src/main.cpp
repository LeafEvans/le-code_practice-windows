#include "../include/course.h"
#include "../include/menu.h"

int main() {
  Course course("C++");
  Menu menu(course);
  menu.interact();
  return 0;
}
