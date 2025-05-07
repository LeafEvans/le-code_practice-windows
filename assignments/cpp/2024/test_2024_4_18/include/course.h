#pragma once
#include <iostream>
#include <string>

#include "../include/student.h"

class Course {
 public:
  // 构造函数
  Course(std::string course_name);

  // 析构函数
  ~Course();

  // 获得课程名称
  std::string getCourseName() const;

  // 添加学生
  void addStudent(Student& student);

  // 删除学生
  void dropStudent(Student& student);

  // 获得学生列表
  Student* getStudents() const;

  // 获得学生数量
  int getNumberOfStudents() const;

 private:
  // 课程名称
  const std::string _course_name;
  // 学生列表
  Student* _students;
  // 学生数量
  int _number_of_students;
};