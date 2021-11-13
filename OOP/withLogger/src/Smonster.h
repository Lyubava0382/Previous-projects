//
// Created by Любава on 13.11.2021.
//

#ifndef UNTITLED3_SMONSTER_H
#define UNTITLED3_SMONSTER_H
#include "Enemy.h"


class Smonster: public Enemy {
public:
    Smonster();
private:
    int assailable[5];
    const int number_of_limbs = 5;
};


#endif //UNTITLED3_SMONSTER_H
