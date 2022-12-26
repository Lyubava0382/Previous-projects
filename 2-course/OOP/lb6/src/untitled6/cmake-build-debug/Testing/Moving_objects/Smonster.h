//
// Created by Любава on 24.11.2021.
//

#ifndef UNTITLED6_SMONSTER_H
#define UNTITLED6_SMONSTER_H

#include "Enemy.h"


class Smonster: public Enemy {
public:
    Smonster();
    void moving(Cellule& locate, Field& game, Player& person);
    void fight(Player& hero);
private:
    const int number_of_limbs = 5;
};


#endif //UNTITLED6_SMONSTER_H
