//
// Created by Serg on 10.10.2022.
//

#ifndef UNTITLED3_ITEM_H
#define UNTITLED3_ITEM_H
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
    virtual ~Item(){};
};

#endif //UNTITLED3_ITEM_H
