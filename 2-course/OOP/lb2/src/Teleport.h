#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Item.h"
class Teleport: public Item{
public:
    Teleport(Coordinates points[2]);

    void interplay(Player& person) final;

    OBJECT GetObject() final;

private:
    OBJECT type;
    Coordinates firstplace;
    Coordinates secondplace;
};
