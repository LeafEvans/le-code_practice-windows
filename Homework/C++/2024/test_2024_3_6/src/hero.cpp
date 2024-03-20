#include "hero.h"

// 声明时有默认参数，在实现时就不用
Hero::Hero(const std::string& name, int life, int attack, int defend)
    : _name(name), _life(life), _attack(attack), _defend(defend) {}

Hero::~Hero() {}

std::string Hero::get_name() const { return _name; }

int Hero::get_attack() const { return _attack; }

int Hero::get_life() const { return _life; }

int Hero::get_defend() const { return _defend; }

bool Hero::set_defend(int defend) {
  if (defend > DEFEND_MAX || defend < DEFEND_MIN) return false;
  _defend = defend;
  return true;
}

bool Hero::set_attack(int attack) {
  if (attack > ATTACK_MAX || attack < ATTACK_MIN) return false;
  _attack = attack;
  return true;
}

bool Hero::set_life(int life) {
  if (life > LIFE_MAX || life < LIFE_MIN) return false;
  _life = life;
  return true;
}

bool Hero::set_name(const std::string& name) {
  _name = name;
  return true;
}
