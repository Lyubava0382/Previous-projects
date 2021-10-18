#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
class Cell{
public:
    virtual TYPE GetType() = 0;
    virtual void SetType(TYPE t) = 0;
    virtual void SetPoint(int x, int y)=0;
    virtual Coordinates GetPoint() = 0;
    virtual ~Cell(){};
};
