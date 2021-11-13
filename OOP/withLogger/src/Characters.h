//
// Created by Любава on 12.11.2021.
//

#ifndef UNTITLED3_CHARACTERS_H
#define UNTITLED3_CHARACTERS_H
#include "CharactersInterface.h"

class Characters: CharactersInterface, public IObservable{
public:
    OBJECT GetObject();
    int GetHealth();
    int GetAttack();
protected:
    int health;
    int attack;
    OBJECT type;
};

#endif //UNTITLED3_CHARACTERS_H
