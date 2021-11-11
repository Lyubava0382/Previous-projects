#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Item.h"
class Teleport: public Item{
public:
    Teleport(std::pair <Coordinates, Coordinates> points);

    void interplay(Player& person) final;

private:
    OBJECT type;
    Coordinates firstplace;
    Coordinates secondplace;
};