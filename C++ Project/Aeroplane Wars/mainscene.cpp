#include "mainscene.h"

MainScene::MainScene(QWidget *parent) : QWidget(parent) {
  srand((unsigned int)time(nullptr));
  initScene();
  playGame();

  // 初始化背景音乐
  m_soundBackground.setSource(QUrl::fromLocalFile(SOUND_BACKGROUNE));
  m_soundBackground.setLoopCount(-1);  // 设置无限循环
  m_soundBackground.play();

  // 初始化爆炸音效
  m_soundBomb.setSource(QUrl::fromLocalFile(SOUND_BOMB));
}

MainScene::~MainScene() {}

void MainScene::initScene() {
  setFixedSize(GAME_WIDTH, GAME_HEIGHT);  // 设置窗口大小
  setWindowTitle(GAME_TITLE);             // 设置窗口标题
  setWindowIcon(QIcon(GAME_ICON));        // 设置窗口图标
  m_Timer.setInterval(GAME_RATE);         // 设置定时器
}

void MainScene::playGame() {
  // 启动定时器
  m_Timer.start();

  // 监听定时器
  connect(&m_Timer, &QTimer::timeout, [=]() {
    enemyToScene();        // 敌机出场
    updatePosition();      // 更新元素坐标
    update();              // 程序绘制图片
    collisionDetection();  // 碰撞检测
  });
}

void MainScene::updatePosition() {
  // 更新地图坐标
  m_map.mapPosition();
  // 发射子弹
  m_hero.shoot();
  // 计算子弹坐标
  for (int i = 0; i < BULLET_NUM; ++i) {
    if (!m_hero.m_bullets[i].m_Free) {
      m_hero.m_bullets[i].updatePosition();
    }
  }
  // 计算敌机坐标
  for (int i = 0; i < ENEMY_NUM; ++i) {
    if (m_enemys[i].m_Free == false) {
      m_enemys[i].updataPosition();
    }
  }

  for (int i = 0; i < BOMB_NUM; ++i) {
    if (m_bombs[i].m_Free == false) {
      m_bombs[i].updataInfo();
    }
  }
}

void MainScene::paintEvent(QPaintEvent *event) {
  QPainter painter(this);

  // 绘制地图
  painter.drawPixmap(0, m_map.m_map1_posY, m_map.m_map1);
  painter.drawPixmap(0, m_map.m_map2_posY, m_map.m_map2);
  painter.drawPixmap(m_hero.m_X, m_hero.m_Y, m_hero.m_Plane);

  for (int i = 0; i < BULLET_NUM; ++i) {
    if (!m_hero.m_bullets[i].m_Free) {
      painter.drawPixmap(m_hero.m_bullets[i].m_X, m_hero.m_bullets[i].m_Y,
                         m_hero.m_bullets[i].m_Bullet);
    }
  }

  for (int i = 0; i < ENEMY_NUM; ++i) {
    if (m_enemys[i].m_Free == false) {
      painter.drawPixmap(m_enemys[i].m_X, m_enemys[i].m_Y, m_enemys[i].m_enemy);
    }
  }

  for (int i = 0; i < BOMB_NUM; ++i) {
    if (m_bombs[i].m_Free == false) {
      painter.drawPixmap(m_bombs[i].m_X, m_bombs[i].m_Y,
                         m_bombs[i].m_pixArr[m_bombs[i].m_index]);
    }
  }
}

void MainScene::keyPressEvent(QKeyEvent *event) {
  int x = m_hero.m_X;
  int y = m_hero.m_Y;

  if (event->key() == Qt::Key_Left) {
    x -= HERO_MOVE_SPEED;
  } else if (event->key() == Qt::Key_Right) {
    x += HERO_MOVE_SPEED;
  }

  if (x <= 0) {
    x = 0;
  } else if (x >= GAME_WIDTH) {
    x = GAME_WIDTH;
  }

  if (event->key() == Qt::Key_Up) {
    y -= HERO_MOVE_SPEED;
  } else if (event->key() == Qt::Key_Down) {
    y += HERO_MOVE_SPEED;
  }

  if (y <= 0) {
    y = 0;
  } else if (y >= GAME_HEIGHT) {
    y = GAME_HEIGHT;
  }

  m_hero.setPosition(x, y);
}

void MainScene::enemyToScene() {
  ++m_recorder;
  if (m_recorder < ENEMY_INTERVAL) {
    return;
  }

  m_recorder = 0;

  for (int i = 0; i < ENEMY_NUM; ++i) {
    if (m_enemys[i].m_Free) {
      m_enemys[i].m_Free = false;
      m_enemys[i].m_X = rand() % (GAME_WIDTH - m_enemys[i].m_Rect.width());
      m_enemys[i].m_Y = -m_enemys[i].m_Rect.height();
      break;
    }
  }
}

void MainScene::collisionDetection() {
  for (int i = 0; i < ENEMY_NUM; ++i) {
    if (m_enemys[i].m_Free) {
      continue;
    }

    for (int j = 0; j < BULLET_NUM; ++j) {
      if (m_hero.m_bullets[j].m_Free) {
        continue;
      }

      if (m_enemys[i].m_Rect.intersects(m_hero.m_bullets[j].m_Rect)) {
        m_enemys[i].m_Free = true;
        m_hero.m_bullets[j].m_Free = true;

        for (int k = 0; k < BOMB_NUM; ++k) {
          if (m_bombs[k].m_Free) {
            m_soundBomb.play();
            m_bombs[k].m_Free = false;
            m_bombs[k].m_X = m_enemys[i].m_X;
            m_bombs[k].m_Y = m_enemys[i].m_Y;
            break;
          }
        }
      }
    }
  }
}