#pragma once

#include "../include/course.h"

class Menu {
 public:
  Menu(Course course);

  void interact();

 private:
  void show();
  Course _course;
};