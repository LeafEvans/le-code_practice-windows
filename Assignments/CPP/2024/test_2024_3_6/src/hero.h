#pragma once

#include <string>
#define LIFE_MAX 1000
#define LIFE_MIN -100
#define ATTACK_MAX 1000
#define ATTACK_MIN 0
#define DEFEND_MAX 500
#define DEFEND_MIN 0

class Hero {
 public:
  Hero(const std::string&, int life = 100, int attack = 100, int defend = 100);
  ~Hero();
  std::string get_name() const;
  int get_life() const;
  int get_attack() const;
  int get_defend() const;

  bool set_name(const std::string&);
  bool set_life(int);
  bool set_attack(int);
  bool set_defend(int);

 private:
  // 名字
  std::string _name;
  // 生命值
  int _life;
  // 攻击力
  int _attack;
  // 防御力
  int _defend;
};