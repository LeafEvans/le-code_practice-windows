#include "../include/menu.h"

#include <windows.h>

#include <cstdio>
#include <iostream>

#include "../include/course.h"
#include "../include/student.h"

Menu::Menu(Course course) : _course(course) {}

void Menu::show() {
  std::cout << "===    选课系统    ===" << std::endl;
  std::cout << "   1. 显示课程名称；" << std::endl;
  std::cout << "   2. 添加学生信息；" << std::endl;
  std::cout << "   3. 删除学生信息；" << std::endl;
  std::cout << "   4. 打印学生列表；" << std::endl;
  std::cout << "   5. 打印学生数量; " << std::endl;
  std::cout << "   6. 退出学生系统；" << std::endl;
}

void Menu::interact() {
  // 选项
  int option = 0;
  // 学生成员
  Student student;
  // 学生名字
  std::string student_name;
  // 学生学号
  int student_number;

  do {
    show();
    // 每次循环更新
    // 学生列表
    Student* students = _course.getStudents();
    // 学生数量
    int number_of_students = _course.getNumberOfStudents();
    std::cout << "输入选项：" << std::endl;
    std::cin >> option;
    system("cls");
    switch (option) {
      case 1:
        std::cout << _course.getCourseName() << std::endl;
        system("pause");
        break;
      case 2:
        std::cout << "输入学生姓名：" << std::endl;
        std::cin >> student_name;
        while (getchar() != '\n') {
          continue;
        }
        std::cout << "输入学生学号：" << std::endl;
        std::cin >> student_number;
        student.setStudentName(student_name);
        student.setStudentNumber(student_number);
        _course.addStudent(student);
        system("pause");
        break;
      case 3:
        std::cout << "输入学生姓名：" << std::endl;
        std::cin >> student_name;
        std::cout << "输入学生学号：" << std::endl;
        std::cin >> student_number;
        student.setStudentName(student_name);
        student.setStudentNumber(student_number);
        _course.dropStudent(student);
        system("pause");
        break;
      case 4:
        for (int i = 0; i < number_of_students; ++i) {
          std::cout << "姓名：" << students[i].getStudentName() << std::endl;
          std::cout << "学号：" << students[i].getStudentNumber() << std::endl;
          std::cout << std::endl;
        }
        system("pause");
        break;
      case 5:
        std::cout << _course.getNumberOfStudents() << std::endl;
        system("pause");
        break;
      case 6:
        std::cout << "退出系统" << std::endl;
        break;
      default:
        std::cout << "输入错误，请重新输入" << std::endl;
        break;
    }
    system("cls");
  } while (option != 6);
}
