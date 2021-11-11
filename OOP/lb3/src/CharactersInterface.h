#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Interior.h"
class CharactersInterface: Interior{
public:
    virtual OBJECT GetObject() = 0;
    virtual void SetHealth(int a) = 0;
    virtual int GetHealth() = 0;
    virtual int GetAttack() = 0;
};