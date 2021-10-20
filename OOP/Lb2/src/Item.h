#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Interior.h"
#include "Player.h"
class Item: Interior{
public:
    virtual OBJECT GetObject() = 0;
    virtual void interplay(Player& person) = 0;
    virtual ~Item(){};
};
