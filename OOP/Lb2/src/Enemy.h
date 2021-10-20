#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Characters.h"
#include "Player.h"
class Enemy: Characters{
public:
    virtual void fight(Player& hero) = 0;
    virtual void hit(Player& hero) = 0;
    virtual void miss(Player& hero) = 0;
    virtual void SetHealth(int a) = 0;
    virtual int GetHealth() = 0;
    virtual int GetAttack() = 0;
    virtual OBJECT GetObject() = 0;
    virtual ~Enemy() {};
};
