//
// Created by Любава on 13.11.2021.
//

#ifndef UNTITLED3_LMONSTER_H
#define UNTITLED3_LMONSTER_H
#include "Enemy.h"

class Lmonster: public Enemy{
public:
    Lmonster();
    void fight(Player& hero) ;
private:
    int assailable[3];
    const int number_of_limbs = 3;
    void hit(Player& hero);
    void miss(Player& hero);
};


#endif //UNTITLED3_LMONSTER_H
