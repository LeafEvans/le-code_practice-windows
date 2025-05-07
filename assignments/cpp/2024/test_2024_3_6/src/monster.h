#pragma once

#include <string>

class Monster {
 public:
  Monster(const std::string&, int life = 100, int attack = 100,
          int defend = 100);
  ~Monster();
  std::string get_name() const;
  int get_life() const;
  int get_attack() const;
  int get_defend() const;

  bool set_name(const std::string&);
  bool set_life(int);
  bool set_attack(int);
  bool set_defend(int);

 private:
  std::string _name;
  int _life;
  int _attack;
  int _defend;
};