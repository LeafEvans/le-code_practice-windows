#include "box.hpp"

#include <iostream>

using namespace std;

bool Box::set_length(int length) {
  if (length <= 0 || length > 100) {
    cout << "length error" << endl;
    return false;
  }
  _length = length;
  // 没有外部访问，因为这个成员函数是类的一部分
  return true;
}

bool Box::set_width(int width) {
  if (width <= 0 || width > 100) {
    cout << "width error" << endl;
    // 对形参进行合法性检查
    return false;
  }
  _width = width;
  return true;
}

bool Box::set_height(int height) {
  if (height <= 0 || height > 100) {
    cout << "height error" << endl;
    return false;
  }
  _height = height;
  return true;
}

int Box::get_length(void) { return _length; }
int Box::get_width(void) { return _width; }
int Box::get_height(void) { return _height; }

int Box::get_area(void) {
  _area = _length * _width;
  return _area;
}

int Box::get_volumn(void) {
  _volume = get_area() * _height;
  return _volume;
}