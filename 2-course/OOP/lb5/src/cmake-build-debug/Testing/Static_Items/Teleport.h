//
// Created by Ыўсртр on 24.11.2021.
//

#ifndef UNTITLED6_TELEPORT_H
#define UNTITLED6_TELEPORT_H


#include "Item.h"
#include "../Moving_objects/Player.h"

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


#endif //UNTITLED6_TELEPORT_H
