//
// Created by Любава on 12.11.2021.
//

#ifndef UNTITLED3_BOX_H
#define UNTITLED3_BOX_H
#include "Item.h"
#include "Player.h"

class Box: public Item{
public:
    Box(bool filled);
    void interplay(Player& person);
    bool GetFull();
private:
    bool full;
};


#endif //UNTITLED3_BOX_H
