#include "Bomb.h"

Bomb::Bomb() {
  for (int i = 1; i <= BOMB_MAX; ++i) {
    QString str = QString(BOMB_PATH).arg(i);
    m_pixArr.push_back(QPixmap(str));
  }

  // 设置坐标
  m_X = 0;
  m_Y = 0;

  // 设置空闲状态
  m_Free = true;

  // 当前播放图片下标
  m_index = 0;

  // 爆炸间隔记录
  m_Recoder = 0;
}

void Bomb::updataInfo() {
  if (m_Free) {
    return;
  }

  ++m_Recoder;

  if (m_Recoder < BOMB_INTERVAL) {
    return;
  }

  m_Recoder = 0;

  m_index++;

  if (m_index > BOMB_MAX - 1) {
    m_index = 0;
    m_Free = true;
  }
}