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
    virtual OBJECT GetObject() = 0;
    virtual void SetObject(OBJECT t)=0;
    virtual void SetKey(bool rich) = 0;
    virtual bool GetKey() = 0;
    virtual void SetStep(GO step) = 0;
    virtual GO GetStep( ) = 0;
    virtual ~Cell(){};
};
