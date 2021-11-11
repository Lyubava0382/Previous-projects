#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Interior.h"
#include "Player.h"
class Item: Interior, public IObservable{
public:
    OBJECT GetObject();
    void interplay(Player& person);
    ~Item(){};
protected:
    OBJECT type;
};