#pragma once

#define DEFAULT_LENGTH 4

typedef unsigned int u32_t;

/**
 * @brief 动态数组类
 */
class Array {
  // 方法
 public:
  /**
   * @brief 默认构造函数
   */
  Array(void);

  /**
   * @brief 拷贝构造函数
   * @param other 要拷贝的数组对象
   */
  Array(const Array &other);

  /**
   * @brief 带参数的构造函数
   * @param size 数组大小
   */
  Array(u32_t size);

  /**
   * @brief 析构函数
   */
  ~Array(void);

  /**
   * @brief 返回数组的长度
   * @return u32_t 数组的长度
   */
  u32_t length(void) const;

  /**
   * @brief 返回元素的个数
   * @return u32_t 元素的个数
   */
  u32_t item_num(void) const;

  /**
   * @brief 返回指定位置的元素
   * @param index 下标
   * @return int 下标对应的元素
   */
  int get_data(u32_t index);

  /**
   * @brief 销毁动态数组
   */
  void destroy(void);

  /**
   * @brief 在指定位置插入元素
   * @param index 要插入元素的位置
   * @param value 要插入的值
   */
  void insert(u32_t index, int value);

  /**
   * @brief 删除指定位置的元素
   * @param index 要删除元素的位置
   * @return bool 代表是否成功
   */
  bool remove_index(u32_t index);

  /**
   * @brief 删除指定的元素
   * @param value 要删除的值
   * @return bool 代表是否成功
   */
  bool remove_data(int value);

 private:
  /**
   * @brief 自动扩容函数
   */
  void extend(void);

  // 属性
 private:
  /**
   * @brief 存储数据的指针
   */
  int *_data;

  /**
   * @brief 数组的长度：空间的大小
   */
  u32_t _length;

  /**
   * @brief 记录存储数据的个数
   */
  u32_t _item_num;

 public:
  /**
   * @brief 静态成员变量，表示无效索引
   */
  static int INVALID_INDEX;
};
