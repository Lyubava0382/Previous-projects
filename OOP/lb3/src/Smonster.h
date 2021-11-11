#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Enemy.h"
class Smonster: public Enemy {
public:
    Smonster()
private:
    int assailable[5];
    const int number_of_limbs = 5;
};