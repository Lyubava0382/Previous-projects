//
// Created by Любава on 24.11.2021.
//

#ifndef UNTITLED6_BOX_H
#define UNTITLED6_BOX_H


#include "Item.h"
#include "../Moving_objects/Player.h"

class Box: public Item{
public:
    Box(bool filled);
    void interplay(Player& person);
    bool GetFull();
private:
    bool full;
};


#endif //UNTITLED6_BOX_H
