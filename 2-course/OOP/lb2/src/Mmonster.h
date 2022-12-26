#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Enemy.h"

class Mmonster: public Enemy {
public:
    Mmonster();
    void SetHealth(int a) final;
    int GetHealth() final;
    int GetAttack() final;
    OBJECT GetObject() final;
    void fight(Player& hero);
private:
     int health;
    int attack;
    OBJECT type;
    int assailable[5];
    bool goon;
    void hit(Player& hero);
    void miss(Player& hero);
};
