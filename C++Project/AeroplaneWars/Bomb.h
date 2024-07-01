#pragma once

#include <QPixmap>
#include <QVector>

#include "config.h"

class Bomb {
 public:
  Bomb();

  void updataInfo();

 public:
  // 爆炸资源数组
  QVector<QPixmap> m_pixArr;

  // 爆炸位置
  int m_X;
  int m_Y;

  // 爆炸状态
  bool m_Free;

  // 爆炸切图时间
  int m_Recoder;

  // 爆炸加载图片下标
  int m_index;
};