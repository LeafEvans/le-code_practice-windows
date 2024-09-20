#pragma once

#include <QPixmap>
#include <QRect>

#include "Bullet.h"
#include "config.h"

class HeroPlane {
 public:
  HeroPlane();

  // 发射子弹
  void shoot();

  // 设置飞机位置
  void setPosition(int x, int y);

 public:
  // 飞机资源
  QPixmap m_Plane;

  // 飞机坐标
  int m_X;
  int m_Y;

  // 飞机矩形边框
  QRect m_Rect;

  // 弹匣
  Bullet m_bullets[BULLET_NUM];

  // 发射时间间隔
  int m_recoder;
};