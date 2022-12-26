//
// Created by Любава on 13.11.2021.
//

#ifndef UNTITLED3_MMONSTER_H
#define UNTITLED3_MMONSTER_H
#include "Enemy.h"

class Mmonster: public Enemy {
public:
    Mmonster();
private:
    int assailable[5];
    const int number_of_limbs = 5;
};


#endif //UNTITLED3_MMONSTER_H
