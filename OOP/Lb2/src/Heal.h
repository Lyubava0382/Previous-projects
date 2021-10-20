#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Item.h"
class Heal: public Item{
public:
    Heal();
    void interplay(Player& person) final;
    OBJECT GetObject() final;
private:
    OBJECT type;
};
