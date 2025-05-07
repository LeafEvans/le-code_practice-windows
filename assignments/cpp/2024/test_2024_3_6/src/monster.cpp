#include "monster.h"

Monster::Monster(const std::string& name, int life, int attack, int defend)
    : _name(name), _life(life), _attack(attack), _defend(defend) {}

Monster::~Monster() {}

std::string Monster::get_name() const { return _name; }

int Monster::get_attack() const { return _attack; }

int Monster::get_defend() const { return _defend; }

int Monster::get_life() const { return _life; }

bool Monster::set_name(const std::string& name) {
  _name = name;
  return true;
}

bool Monster::set_attack(int attack) {
  _attack = attack;
  return true;
}

bool Monster::set_defend(int defend) {
  _defend = defend;
  return true;
}

bool Monster::set_life(int life) {
  _life = life;
  return true;
}