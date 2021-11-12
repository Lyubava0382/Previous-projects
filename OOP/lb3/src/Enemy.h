//
// Created by Любава on 13.11.2021.
//

#ifndef UNTITLED3_ENEMY_H
#define UNTITLED3_ENEMY_H
#include "Player.h"
#include "fightView.h"
#include "HitMonsterPrint.h"
#include "MissMonsterPrint.h"

class Enemy: public Characters{
public:
    void fight(Player& hero);
    void SetHealth(int a);
    int GetHealth();
    int GetReward();
    bool GetGoing();
    int GetLimb(int index);
protected:
    void hit(Player& hero);
    void miss(Player& hero);
    int reward;
    int health;
    int attack;
    OBJECT type;
    int assailable[5];
    bool goon;
};


#endif //UNTITLED3_ENEMY_H
