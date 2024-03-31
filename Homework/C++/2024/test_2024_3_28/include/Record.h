#pragma once

#include <cstring>

class Record {
 private:
  char _name[50];      // 姓名
  char _relation[50];  // 关系
  char _tele[50];      // 电话

 public:
  Record();                            // 默认构造函数
  Record(const char *, const char *);  // 带参数的构造函数

  // 成员函数
  void set_name(const char *);       // 设置名字
  void set_relation(const char *);   // 设置关系
  void set_tele(const char *);       // 设置电话
  const char *get_name() const;      // 得到名字
  const char *get_relation() const;  // 得到关系
  const char *get_tele() const;      // 得到电话
};
