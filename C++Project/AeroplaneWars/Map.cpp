#include "Map.h"

Map::Map() {
  // 加载地图对象
  m_map1.load(MAP_PATH);
  m_map2.load(MAP_PATH);

  // 设置 Y 轴坐标
  m_map1_posY = -GAME_HEIGHT;
  m_map2_posY = 0;

  // 设置地图滚动速度
  m_scroll_speed = MAP_SCROLL_SPEED;
}

void Map::mapPosition() {
  // 处理图片 1 滚动
  m_map1_posY += m_scroll_speed;
  if (m_map1_posY >= 0) {
    m_map1_posY = -GAME_HEIGHT;
  }

  // 处理图片 2 滚动
  m_map2_posY += m_scroll_speed;
  if (m_map2_posY >= GAME_HEIGHT) {
    m_map2_posY = 0;
  }
}