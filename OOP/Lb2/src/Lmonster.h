#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Enemy.h"

class Lmonster: public Enemy {
public:
    Lmonster();
    void SetHealth(int a) final;
    int GetHealth() final;
    int GetAttack() final;
    OBJECT GetObject() final;
    void fight(Player& hero);
private:
    int health;
    int attack;
    OBJECT type;
    int assailable[3];
    bool goon;
    void hit(Player& hero);
    void miss(Player& hero);
};
