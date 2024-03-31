#pragma once

#include "Record.h"

class ContactsManagement {
 public:
  // 构造与析构
  ContactsManagement();
  ContactsManagement(unsigned int);
  ContactsManagement(ContactsManagement&);
  ~ContactsManagement();

  // 公共成员函数
  void add_new_contact();
  void show_all_contacts() const;
  void search_contact() const;

 private:
  // 私有成员变量
  unsigned int _num;
  Record* _records;
  unsigned int _size;

  // 公有成员函数
  void set_data(unsigned int, unsigned int);
  void get_data(const Record&) const;
  void search_name() const;
  void search_relation() const;
};