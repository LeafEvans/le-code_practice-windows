#pragma once
#include <string>

class Skill {
 public:
  Skill(const std::string &, int, int);
  ~Skill();
  std::string get_name() const;
  int get_damage() const;
  int get_cd() const;
  bool set_name(const std::string &);
  bool set_damage(int);
  bool set_cd(int);

 private:
  std::string _name;
  int _damage;
  int _cd;
};
