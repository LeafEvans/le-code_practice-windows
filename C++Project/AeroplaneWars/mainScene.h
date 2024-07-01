#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QIcon>
#include <QKeyEvent>
#include <QPainter>
#include <QSoundEffect>
#include <QTimer>
#include <QWidget>
#include <cstdlib>
#include <ctime>

#include "Bomb.h"
#include "Bullet.h"
#include "EnemyPlane.h"
#include "HeroPlane.h"
#include "Map.h"
#include "config.h"

class MainScene : public QWidget {
  Q_OBJECT

 public:
  MainScene(QWidget *parent = nullptr);
  ~MainScene();

  void initScene();

  // 启动游戏
  void playGame();

  // 更新坐标
  void updatePosition();

  // 绘图对象
  void paintEvent(QPaintEvent *);

  void keyPressEvent(QKeyEvent *);

  // 敌机出现
  void enemyToScene();

  void collisionDetection();

 public:
  QTimer m_Timer;                  // 定时器对象
  Map m_map;                       // 地图对象
  HeroPlane m_hero;                // 飞机对象
  EnemyPlane m_enemys[ENEMY_NUM];  // 敌机数组
  int m_recorder = 0;              // 敌机出场间隔记录
  Bomb m_bombs[BOMB_NUM];
  QSoundEffect m_soundBomb;
  QSoundEffect m_soundBackground;
};
#endif  // MAINSCENE_H
