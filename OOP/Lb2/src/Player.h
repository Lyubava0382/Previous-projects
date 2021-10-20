#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Characters.h"
class Player: Characters{
public:
    explicit Player();
    void SetHealth(int a);
    int GetHealth();
    int GetAttack();
    void SetKey(bool yes);
    bool GetKey() const;
    OBJECT GetObject();
    void SetLocal(Coordinates place);
    Coordinates GetLocal();
    void SetCoins(int number);
    int GetCoins();
    
private:
    int health;
    int attack;
    Coordinates location{};
    bool key;
    OBJECT type;
    int coins;
};
