#include "hero1.h"

// 使用初始化成员列表来初始化 skill
Hero1::Hero1(const std::string& name, int life, int attack, int defend)
    : Hero(name, life, attack, defend), skill("skill1", 100, 5) {}

Hero1::~Hero1() {}