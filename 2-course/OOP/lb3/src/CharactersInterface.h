//
// Created by Любава on 12.11.2021.
//

#ifndef UNTITLED3_CHARACTERSINTERFACE_H
#define UNTITLED3_CHARACTERSINTERFACE_H
#include "Interior.h"
#include "IObservable.h"

class CharactersInterface: Interior{
public:
    virtual OBJECT GetObject() = 0;
    virtual void SetHealth(int a) = 0;
    virtual int GetHealth() = 0;
    virtual int GetAttack() = 0;
};


#endif //UNTITLED3_CHARACTERSINTERFACE_H
