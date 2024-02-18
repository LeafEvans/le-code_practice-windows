#ifndef CODE_BOX_HPP
#define CODE_BOX_HPP

class Box {
 public:
  // 声明方法
  bool set_length(int length);
  bool set_width(int width);
  bool set_height(int height);

  int get_length(void);
  int get_width(void);
  int get_height(void);

  int get_area(void);
  int get_volumn(void);

 private:
  int _length;  // 长度
  int _width;   // 宽度
  int _height;  // 高度
  int _area;    // 面积
  int _volume;  // 体积
};

#endif  // CODE_BOX_HPP