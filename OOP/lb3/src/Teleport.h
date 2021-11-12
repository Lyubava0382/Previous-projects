//
// Created by Любава on 12.11.2021.
//

#ifndef UNTITLED3_TELEPORT_H
#define UNTITLED3_TELEPORT_H
#include "Item.h"
#include "Player.h"

class Teleport: public Item{
public:
    Teleport(std::pair <Coordinates, Coordinates> points);
    void interplay(Player& person);
    Coordinates GetFirstPlace();
    Coordinates GetSecondPlace();
private:
    Coordinates firstplace;
    Coordinates secondplace;
};


#endif //UNTITLED3_TELEPORT_H
