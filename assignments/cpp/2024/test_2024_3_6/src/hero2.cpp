#include "hero2.h"

Hero2::Hero2(const std::string& name, int life, int attack, int defend)
    : Hero(name, life, attack, defend), skill("skill2", 50, 2) {}

Hero2::~Hero2() {}
