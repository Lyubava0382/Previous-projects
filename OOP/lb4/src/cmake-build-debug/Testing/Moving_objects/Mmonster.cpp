
#include "Mmonster.h"
Mmonster::Mmonster(){
    health = 3;
    attack = 2;
    observable = false;
    observer = nullptr;
    type = MEDIUMMONSTER;
    goon = true;
    for (int i = 0; i < number_of_limbs; i++) {
        assailable[i] = 1;
    }
    assailable[rand() % number_of_limbs] = 0;
    int random = rand() % number_of_limbs;
    while (assailable[random] == 0){
        random = rand() % number_of_limbs;
    }
    assailable[random] = 0;
}