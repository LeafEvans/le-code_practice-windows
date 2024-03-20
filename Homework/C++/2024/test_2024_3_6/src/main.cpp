#include <iostream>

#include "hero1.h"

int main(int argc, char** argv) {
  Hero1 libai("libai");
  std::cout << libai.get_name() << std::endl;
  std::cout << libai.skill.get_damage() << std::endl;
  std::cout << libai.skill.get_cd() << std::endl;
  return 0;
}