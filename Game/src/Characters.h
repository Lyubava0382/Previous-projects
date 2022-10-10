//
// Created by Serg on 10.10.2022.
//

#ifndef UNTITLED3_CHARACTERS_H
#define UNTITLED3_CHARACTERS_H

#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Interior.h"
class Characters: Interior{
public:
    virtual OBJECT GetObject() = 0;
};



#endif //UNTITLED3_CHARACTERS_H
