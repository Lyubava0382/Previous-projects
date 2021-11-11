#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Characters.h"
class Player: Characters{
public:
    explicit Player();
    void SetKey(bool yes);
    bool GetKey() const;
    void SetLocal(Coordinates place);
    Coordinates GetLocal();
    void SetCoins(int number);
    int GetCoins();
    
private:
    Coordinates location{};
    bool key;
    int coins;
};