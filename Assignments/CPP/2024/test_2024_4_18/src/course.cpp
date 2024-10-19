#include "../include/course.h"

#include <string>

#include "../include/student.h"

// 构造函数
Course::Course(const std::string course_name)
    : _course_name(course_name), _students(nullptr), _number_of_students(0) {}

// 析构函数
Course::~Course() {
  // 不为空指针时，进行删除
  // 为了防止没有添加学生而做的判断
  if (_students) {
    // 删除对应空间
    delete[] _students;
    // 置为空指针
    _students = nullptr;
  }
}

// 获得课程姓名
std::string Course::getCourseName() const { return _course_name; }

// 添加学生
void Course::addStudent(Student& student) {
  // 如果学生数量为零，就初始化一个新指针
  if (!_students) {
    //
    _students = new Student[1];
    _students[0] = student;
    // 数量增加
    ++_number_of_students;
    // 然后可以直接退出
    return;
  }

  // 创建一个临时变量放新的数据，比原来数量大一
  Student* temp = new Student[_number_of_students + 1];

  // 拷贝原有数据到新的堆区段
  for (int i = 0; i < _number_of_students; ++i) {
    temp[i] = _students[i];
  }

  // 添加新增的学生信息
  temp[_number_of_students] = student;

  // 增加学生数量
  ++_number_of_students;

  delete[] _students;
  // 导向新的空间
  _students = temp;
  // 将暂时的置为空指针
  temp = nullptr;
}

// 删除学生
void Course::dropStudent(Student& student) {
  if (!_number_of_students) {
    std::cout << "学生数量为零，无法删除。" << std::endl;
  }
  // 读取的索引和写入的索引
  // 复制的时候使用
  int read_index = 0;
  int write_index = 0;

  // 是否找到的标志
  bool flag = false;

  for (read_index = 0; read_index < _number_of_students; ++read_index) {
    // 如果找到了
    if (student.getStudentName() == _students[read_index].getStudentName() &&
        student.getStudentNumber() ==
            _students[read_index].getStudentNumber()) {
      // 标志找到
      flag = true;
      // 将当前的写入指针赋值
      write_index = read_index;
      // 跳出循环
      ++read_index;
      break;
    }
  }

  // 如果标志依旧为 false，说明没找到
  // 打印提示性语句并退出
  if (!flag) {
    std::cout << "指定学生不在列表中……" << std::endl;
    return;
  }

  while (read_index < _number_of_students) {
    _students[write_index] = _students[read_index];
    // 更新写入指针
    ++write_index;
    ++read_index;
  }

  // 学生数量减少
  --_number_of_students;
}

// 返回学生列表
Student* Course::getStudents() const { return _students; }

// 返回学生数量
int Course::getNumberOfStudents() const { return _number_of_students; }
