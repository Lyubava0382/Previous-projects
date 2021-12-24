//
// Created by Любава on 24.11.2021.
//

#ifndef UNTITLED6_HEAL_H
#define UNTITLED6_HEAL_H


#include "Item.h"
#include "../Moving_objects/Player.h"

class Heal: public Item{
public:
    Heal();
    void interplay(Player& person);
};



#endif //UNTITLED6_HEAL_H
