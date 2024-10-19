#include "array.h"

int Array::INVALID_INDEX = 9999999;

Array::Array(void)
    : _data(new int[DefaultSize]), _size(DefaultSize), _item_num(0) {
  cout << "Array(void);" << endl;
}

Array::Array(uint size) : _data(new int[size]), _size(size), _item_num(0) {
  cout << "Array(uint size);" << endl;
}

Array::Array(const Array& other)
    : _data(new int[other._size]),
      _size(other._size),
      _item_num(other._item_num) {
  cout << "Array::Array(const Array& other)" << endl;
  for (uint i = 0; i < _size; ++i) {
    _data[i] = other._data[i];
  }
}

Array::~Array() {
  cout << "~Array();" << endl;
  if (_data != nullptr) {
    delete[] _data;
  }
}

void Array::extend(void) {
  int* temp = _data;
  _data = new int[_size + 1];
  memcpy(_data, temp, sizeof(int) * _size);
  ++_size;
  delete[] temp;
}

int Array::data(uint pos) const {
  if (pos >= _item_num) {
    cout << "Index out of range!" << endl;
    return INVALID_INDEX;
  }
  return _data[pos];
}

void Array::destory(void) {
  if (_data != nullptr) {
    delete[] _data;
    _item_num = 0;
    _size = 0;
    _data = nullptr;
  }
}

uint Array::size(void) const { return _size; }

uint Array::item_num(void) const { return _item_num; }

void Array::insert(uint pos, int value) {
  if (_item_num == _size) {
    extend();
  }

  if (pos >= _item_num) {
    _data[_item_num] = value;
  } else {
    for (uint i = _item_num; i > pos; --i) {
      _data[i] = _data[i - 1];
    }
    _data[pos] = value;
  }

  ++_item_num;
}

void Array::remove_index(uint pos) {
  if (pos >= _item_num) {
    cout << "Index out of range!" << endl;
  }

  for (uint i = pos; i < _item_num; ++i) {
    _data[i] = _data[i + 1];
  }
  --_item_num;
}

void Array::remove_value(int value) {
  int write_index = 0;
  for (uint read_index = 0; read_index < _item_num; ++read_index) {
    if (_data[read_index] != value) {
      _data[write_index++] = _data[read_index];
    }
  }

  int num_removed = _item_num - write_index;
  _item_num = write_index;

  if (num_removed == 0) {
    cout << "Invalid value!" << endl;
  }
}