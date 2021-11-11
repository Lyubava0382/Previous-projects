#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "structs.h"
class Interior{
public:
    virtual OBJECT GetObject() = 0;
};