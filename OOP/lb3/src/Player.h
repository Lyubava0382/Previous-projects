//
// Created by Любава on 12.11.2021.
//

#ifndef UNTITLED3_PLAYER_H
#define UNTITLED3_PLAYER_H
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


#endif //UNTITLED3_PLAYER_H
