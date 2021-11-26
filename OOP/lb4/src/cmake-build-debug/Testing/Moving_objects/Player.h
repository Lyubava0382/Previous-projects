//
// Created by Любава on 24.11.2021.
//

#ifndef UNTITLED6_PLAYER_H
#define UNTITLED6_PLAYER_H

#include "Characters.h"

class Player: public Characters{
public:
    explicit Player();
    void SetKey(bool yes);
    bool GetKey();
    void SetHealth(int a);
    int GetHealth();
    void SetLocal(Coordinates place);
    Coordinates GetLocal();
    void SetCoins(int number);
    int GetCoins();
private:
    Coordinates location{};
    bool key;
    int coins;
};


#endif //UNTITLED6_PLAYER_H
