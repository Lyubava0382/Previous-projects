//
// Created by Любава on 24.11.2021.
//

#ifndef UNTITLED6_CHARACTERSINTERFACE_H
#define UNTITLED6_CHARACTERSINTERFACE_H


#include "../../Interior.h"
#include "../Logging/IObservable.h"

class CharactersInterface: Interior{
public:
    virtual OBJECT GetObject() = 0;
    virtual void SetHealth(int a) = 0;
    virtual int GetHealth() = 0;
    virtual int GetAttack() = 0;
};


#endif //UNTITLED6_CHARACTERSINTERFACE_H
