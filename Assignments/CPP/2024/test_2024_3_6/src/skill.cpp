#include "skill.h"

#include <string>

Skill::Skill(const std::string &name, int damage, int cd)
    : _name(name), _damage(damage), _cd(cd) {}

Skill::~Skill() {}

std::string Skill::get_name() const { return _name; }

int Skill::get_damage() const { return _damage; }

int Skill::get_cd() const { return _cd; }

bool Skill::set_name(const std::string &name) {
  _name = name;
  return true;
}

bool Skill::set_damage(int damage) {
  _damage = damage;
  return true;
}

bool Skill::set_cd(int cd) {
  _cd = cd;
  return true;
}