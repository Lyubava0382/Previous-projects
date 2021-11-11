#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Enemy.h"
class Lmonster: public Enemy {
public:
    Lmonster();
    void fight(Player& hero);
private:
    int assailable[3];
    const int number_of_limbs = 3;

    void hit(Player& hero);
    void miss(Player& hero);
};