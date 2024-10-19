#pragma once

#include "config.h"

#include <QPixmap>
#include <QRect>

class EnemyPlane {
 public:
  EnemyPlane();

  // 更新坐标
  void updataPosition();

 public:
  // 敌机对象
  QPixmap m_enemy;

  // 位置
  int m_X;
  int m_Y;

  // 敌机矩形边框
  QRect m_Rect;

  // 状态
  bool m_Free;

  // 速度
  int m_Speed;
};