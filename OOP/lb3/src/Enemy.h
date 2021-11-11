#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Characters.h"
class Enemy: public Characters{
public:
    void fight(Player& hero);
    void hit(Player& hero);
    void miss(Player& hero);
    
protected:
    int reward;
    int health;
    int attack;
    OBJECT type;
    int assailable[5];
    bool goon;
};