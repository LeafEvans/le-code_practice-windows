#pragma once

#include <cstring>
#include <iostream>

#define DefaultSize 4

using namespace std;

typedef unsigned int uint;

/**
 * @brief 动态数组类
 */
class Array {
 public:
  /**
   * @brief 默认构造函数
   */
  Array(void);

  /**
   * @brief 有参构造函数
   */
  Array(uint size);

  /**
   * @brief 拷贝构造函数
   */
  Array(const Array &other);

  /**
   * @brief 自动析构函数
   */
  ~Array();

  /**
   * @brief 自动扩容函数
   */
  void extend(void);

  /**
   * @brief 自动销毁函数
   */
  void destory(void);

  /**
   * @brief 插入函数
   * @param pos 插入的位置
   * @param value 插入的数值
   */
  void insert(uint pos, int value);

  /**
   * @brief 读取数据的函数
   * @param pos 读取的位置
   * @return int 代表具体的整形元素
   */
  int data(uint pos) const;

  /**
   * @brief 读取大小的函数
   * @return uint 代表数组的大小
   */
  uint size(void) const;

  /**
   * @brief 读取物体个数的函数
   * @return uint 代表物品的个数
   */
  uint item_num(void) const;

  /**
   * @brief 去除指定下标的元素
   * @param uint 代表下标
   */
  void remove_index(uint pos);

  /**
   * @brief 去除指定的数
   * @param int 指定的数
   */
  void remove_value(int value);

 private:
  /**
   * @brief 存储数据的指针
   */
  int *_data;

  /**
   * 数组的大小
   */
  uint _size;

  /**
   * @brief 物品的个数
   */
  uint _item_num;

 public:
  /**
   * @brief
   */
  static int INVALID_INDEX;
};
