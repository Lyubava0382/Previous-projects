
#ifndef UNTITLED3_BOX_H
#define UNTITLED3_BOX_H

#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Item.h"
class Box: public Item{
public:
    Box(bool filled);
    OBJECT GetObject() final;
    bool GetOpen();
private:
    OBJECT type;
    bool full;
    bool open;
};



#endif //UNTITLED3_BOX_H
