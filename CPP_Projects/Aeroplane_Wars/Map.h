#pragma once

#include <QPixmap>

#include "config.h"

class Map {
 public:
  Map();  // 默认构造函数

  void mapPosition();  // 地图滚动坐标计算

 public:
  // 地图图片对象
  QPixmap m_map1;
  QPixmap m_map2;

  // 地图 Y 轴坐标
  int m_map1_posY;
  int m_map2_posY;

  // 地图滚动幅度
  int m_scroll_speed;
};