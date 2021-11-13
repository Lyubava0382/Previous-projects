//
// Created by Любава on 12.11.2021.
//

#ifndef UNTITLED3_HEAL_H
#define UNTITLED3_HEAL_H
#include "Item.h"
#include "Player.h"

class Heal: public Item{
public:
    Heal();
    void interplay(Player& person);
};


#endif //UNTITLED3_HEAL_H
