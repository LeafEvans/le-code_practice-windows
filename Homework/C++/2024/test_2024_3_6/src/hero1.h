#pragma once
#include "hero.h"
#include "skill1.h"

class Hero1 : public Hero {
 public:
  Hero1(const std::string&, int life = 100, int attack = 100, int defend = 100);
  ~Hero1();
  Skill1 skill;
};