//
// Created by Любава on 24.11.2021.
//

#ifndef UNTITLED6_CHARACTERS_H
#define UNTITLED6_CHARACTERS_H

#include "../../Empty.h"
#include "CharactersInterface.h"

class Characters: public CharactersInterface, public Empty{
public:
    OBJECT GetObject();
    int GetHealth();
    int GetAttack();
protected:
    int health;
    int attack;
    OBJECT type;
};



#endif //UNTITLED6_CHARACTERS_H
