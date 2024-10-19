#pragma once
#include "hero.h"
#include "skill2.h"

class Hero2 : public Hero {
 public:
  Hero2(const std::string&, int life = 100, int attack = 100, int defend = 100);
  ~Hero2();
  Skill2 skill;
};