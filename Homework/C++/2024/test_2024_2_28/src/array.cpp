#include "array.hpp"

#include <cstring>
#include <iostream>

using namespace std;

// 对定义的类内的非法坐标值进行初始化
int Array::INVALID_INDEX = 999999;

Array::Array(void)
    : _data(new int[DefaultLength]), _length(DefaultLength), _item_num(0) {
  // 不带参数的构造函数，用一些初始值来构造
  cout << "Array::Array(void)" << endl;
}

Array::Array(u32_t length)
    : _data(new int[length]), _length(length), _item_num(0) {
  // 带有参数的构造函数
  cout << "Array::Array(u32_t length)" << endl;
}

Array::Array(const Array& other)
    : _data(new int[other._length]),
      _length(other._length),
      _item_num(other._item_num) {
  cout << "Array::Array(const Array& other)" << endl;
  // 拷贝构造，用循环来
  for (int i = 0; i < _length; ++i) {
    _data[i] = other._data[i];
  }
}

Array::~Array() {
  cout << "~Array()" << endl;
  if (_data) delete[] _data;
}

u32_t Array::length(void) const { return _length; }

u32_t Array::item_num(void) const { return _item_num; }

int Array::get_data(u32_t index){
  if (index >= _length) {
    // 非法下标，给出提示语句，返回定义的非法坐标值
    cout << "Index out of range!" << endl;
    return INVALID_INDEX;
  }
  return _data[index];
}

void Array::extend(void) {
  // 定义一个临时变量 temp 来存储原来的地址
  int* temp = _data;
  // 扩容为原来的两倍
  _data = new int[2 * _length];
  // 使用 memcpy() 来进行数据的赋值
  memcpy(_data, temp, sizeof(int) * _length);
  // 数组长度两倍
  _length *= 2;
  // 释放原来的空间
  delete[] temp;
}

void Array::destroy(void) {
  // 先判断是否为空指针
  if (_data != nullptr) {
    delete[] _data;
    _data = nullptr;
    _length = 0;
    _item_num = 0;
  }
}

void Array::insert(u32_t index, int value) {
  // 数组已满，扩容
  if (_item_num == _length) {
    extend();
  }

  if (index < 0 || index > _item_num) {
    // 插入位置无效，直接插入到末尾
    _data[_item_num] = value;
  } else {
    // 将 index 之后的元素依次向后移动一位
    // 从后往前进行插值
    for (int i = _item_num; i > index; --i) {
      _data[i] = _data[i - 1];
    }
    _data[index] = value;
  }

  ++_item_num;
}

bool Array::remove_index(u32_t index) {
  // 判断这个下标是否合法
  if (index >= _item_num) {
    cout << "Index out of range!" << endl;
    return false;
  }

  // 将后面的值覆盖到前面
  for (int i = index; i < _item_num; ++i) {
    _data[i] = _data[i + 1];
  }
  --_item_num;
  return true;
}

bool Array::remove_data(int value) {
  // 记录下一个非指定值应写入的位置
  // 这样可以减少循环
  int write_index = 0;

  for (int read_index = 0; read_index < _item_num; ++read_index) {
    // 遍历数组
    if (_data[read_index] != value) {
      // 如果遇到非指定值，就写入，可将原来的覆盖
      // 同时还将 write_index 的值加 1
      _data[write_index++] = _data[read_index];
    }
  }

  // 移动的数字的个数
  int num_removed = _item_num - write_index;
  // 现在数组内元素的数量
  _item_num = write_index;

  if (num_removed == 0) {
    // 如果一直没有，说明指定值非法
    cout << "Invalid value!" << endl;
    return false;
  }

  return true;
}
