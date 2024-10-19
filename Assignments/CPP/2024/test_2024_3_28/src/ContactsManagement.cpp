#include "../include/ContactsManagement.h"

#include <cstring>
#include <iostream>

#include "../include/Record.h"

using namespace std;

// 默认的通讯录大小
#define DEFAULT_SIZE 10

// 默认构造函数
ContactsManagement::ContactsManagement() {
  _num = 0;                      // 一开始为 0 个
  _size = DEFAULT_SIZE;          // 没有参数就默认大小
  _records = new Record[_size];  // 存储记录的指针
}

// 给了指定通讯录大小的构造函数
ContactsManagement::ContactsManagement(unsigned int num) {
  _num = num;                    // 输入指定的通讯录人数
  _size = num * 2;               // 通讯录大小为通讯录人数的两倍
  _records = new Record[_size];  // 存储通讯录的指针赋值
  setData(0, _num);             // 输入这些人的数据
}

// 析构函数
ContactsManagement::~ContactsManagement() {
  // 如果为非空指针，便删除那块空间
  // 避免重复删除
  if (_records) {
    delete[] _records;
  }
}

// 拷贝构造函数
ContactsManagement::ContactsManagement(ContactsManagement& other) {
  _num = other._num;
  _size = other._size;
  // 开辟一块新的空间
  _records = new Record[_size];
  for (int i = 0; i < _num; ++i) {
    _records[i] = other._records[i];
  }
}

// 添加成员
void ContactsManagement::addNewContact() {
  // 要增加的数量
  unsigned int add_num = 0;
  cout << "输入要增加的数量:>";
  cin >> add_num;

  // 新的人数为原来的人数加上新增的人数
  unsigned int new_num = _num + add_num;

  if (new_num > _size) {
    // 如果新的大于通讯录大小，就扩充这个通讯录
    // 新的大小为原来的空间加上新增的
    _size += add_num;
    // 分配新的记录数组
    Record* new_records = new Record[_size];

    // 拷贝原有数据到新的空间
    for (unsigned int i = 0; i < _num; ++i) {
      new_records[i] = _records[i];
    }

    delete[] _records;       // 释放原来的记录数组
    _records = new_records;  // 更新指向
  }

  // 设置通讯录的数据
  setData(_num, new_num);
  _num = new_num;  // 更改已有的数值
}

// 输出全部通讯录成员
void ContactsManagement::showAllContacts() const {
  if (_num == 0) {
    // 如果没有成员
    // 输出下列语句
    cout << "抱歉，当前成员数量为 0" << endl;
    return;
  }
  for (int i = 0; i < _num; ++i) {
    // 输出
    getData(_records[i]);
  }
}

// 查找通讯录成员
void ContactsManagement::searchContact() const {
  int choice = 0;
  while (true) {
    cout << "输入查找方式:>" << endl;
    cout << "1. 名字" << endl;
    cout << "2. 关系" << endl;
    cin >> choice;  // 输入选择
    if (choice != 1 && choice != 2) {
      cout << "无效选项，请重新选择。" << endl;
    } else {
      break;
    }
  }
  switch (choice) {
    case 1:
      searchName();
      break;
    case 2:
      searchRelation();
      break;
  }
}

// 以名字查找
void ContactsManagement::searchName() const {
  if (_num == 0) {
    // 如果没有成员
    // 输出下列语句
    cout << "抱歉，当前成员数量为 0" << endl;
    return;
  }

  bool flag = false;  // 是否找到
  char name[20] = {0};
  cout << "输入要查找的名字:>" << endl;
  cin >> name;

  for (int i = 0; i < _num; ++i) {
    if (strcmp(name, _records[i].getName()) == 0) {
      getData(_records[i]);
      flag = true;  // 找到了
    }
  }

  if (!flag) {
    cout << "抱歉，联系人中没有指定成员" << endl;
  }
}

// 以关系查找
void ContactsManagement::searchRelation() const {
  if (_num == 0) {
    // 如果没有成员
    // 输出下列语句
    cout << "抱歉，当前成员数量为 0" << endl;
    return;
  }
  char relation[20] = {0};
  bool flag = false;  // 是否找到
  cout << "输入要查找的关系:>" << endl;
  cin >> relation;

  for (int i = 0; i < _num; ++i) {
    if (strcmp(relation, _records[i].getRelation()) == 0) {
      getData(_records[i]);
      flag = true;  // 找到了
    }
  }

  if (!flag) {
    cout << "抱歉，联系人中没有指定成员" << endl;
  }
}

// 输入数据的函数，为私有的
void ContactsManagement::setData(unsigned int start, unsigned int end) {
  char name[50];
  char relation[50];
  char tele[50];

  for (int i = start; i < end; ++i) {
    cout << "输入第" << i + 1 << "个用户姓名:>" << endl;
    cin >> name;
    cout << "输入第" << i + 1 << "个用户关系:>" << endl;
    cin >> relation;
    cout << "输入第" << i + 1 << "个用户电话:>" << endl;
    cin >> tele;
    _records[i].setName(name);          // 输入名字
    _records[i].setRelation(relation);  // 输入关系
    _records[i].setTele(tele);          // 输入电话
  }
}

// 输出数据的函数，为私有的只读函数
void ContactsManagement::getData(const Record& record) const {
  cout << "姓名：" << record.getName() << "\t    \t"
       << "关系：" << record.getRelation() << "\t    \t"
       << "电话：" << record.getTele() << endl;
}
