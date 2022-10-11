//
// Created by Serg on 10.10.2022.
//

#ifndef UNTITLED3_CELL_H
#define UNTITLED3_CELL_H
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
    virtual ~Cell(){};
};

#endif //UNTITLED3_CELL_H
