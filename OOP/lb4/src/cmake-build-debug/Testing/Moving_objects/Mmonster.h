//
// Created by Любава on 24.11.2021.
//

#ifndef UNTITLED6_MMONSTER_H
#define UNTITLED6_MMONSTER_H

#include "Enemy.h"

class Mmonster: public Enemy {
public:
    Mmonster();
private:
    int assailable[5];
    const int number_of_limbs = 5;
};



#endif //UNTITLED6_MMONSTER_H
