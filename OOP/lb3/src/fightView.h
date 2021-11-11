#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
class fightView{
public:
    explicit fightView(OBJECT monster_size, int hero_health, int monster_health);
    char GetWound() const;
private:
    char wound;
};