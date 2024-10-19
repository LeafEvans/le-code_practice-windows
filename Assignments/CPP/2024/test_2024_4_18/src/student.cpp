#include "../include/student.h"

Student::Student(const std::string student_name, const int &student_number)
    : _student_name(student_name), _student_number(student_number) {}

Student::~Student() {}

std::string Student::getStudentName() const { return _student_name; }

int Student::getStudentNumber() const { return _student_number; }

void Student::setStudentName(const std::string &student_name) {
  _student_name = student_name;
}

void Student::setStudentNumber(const int &student_number) {
  _student_number = student_number;
}
