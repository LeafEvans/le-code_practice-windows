#include "skill1.h"

// 因为 Skill 里的私有成员变量派生类无法访问，
// 所以要手动调用基类中的构造函数
Skill1::Skill1(const std::string& name, int damage, int cd)
    : Skill(name, damage, cd) {}

Skill1::~Skill1() {}