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
  void addNewContact();
  void showAllContacts() const;
  void searchContact() const;

 private:
  // 私有成员变量
  unsigned int _num;
  Record* _records;
  unsigned int _size;

  // 公有成员函数
  void setData(unsigned int, unsigned int);
  void getData(const Record&) const;
  void searchName() const;
  void searchRelation() const;
};