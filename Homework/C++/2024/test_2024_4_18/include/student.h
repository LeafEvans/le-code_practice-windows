#pragma once
#include <string>

const std::string DEFAULT_NAME = "Zhang San";
const int DEFAULT_NUMBER = 123456;

class Student {
 public:
  // 构造函数
  Student(const std::string student_name = DEFAULT_NAME,
          const int &student_number = DEFAULT_NUMBER);

  ~Student();

  // 得到姓名
  std::string getStudentName() const;

  // 得到学号
  int getStudentNumber() const;

  // 设置姓名
  void setStudentName(const std::string &student_name);

  // 设置学号
  void setStudentNumber(const int &student_number);

 private:
  // 学生名字
  std::string _student_name;
  // 学生学号
  int _student_number;
};