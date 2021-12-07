//
// Created by Любава on 24.11.2021.
//

#ifndef UNTITLED6_LMONSTER_H
#define UNTITLED6_LMONSTER_H



#include "Enemy.h"

class Lmonster: public Enemy{
public:
    Lmonster();
    void fight(Player& hero) ;
    void moving(Cellule& locate, Field& game, Player& person);
private:
    const int number_of_limbs = 3;
    void hit(Player& hero);
    void miss(Player& hero);
};


#endif //UNTITLED6_LMONSTER_H
