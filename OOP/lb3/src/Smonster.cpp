#include "Smonster.h"
    Smonster::Smonster(){
        health = 5;
        attack = 1;
        type = SMALLMONSTER;
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