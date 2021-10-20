#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Item.h"
class Box: public Item{
public:
    Box(bool filled);
    void interplay(Player& person) final;
    OBJECT GetObject() final;
private:
    OBJECT type;
    bool full;
};
