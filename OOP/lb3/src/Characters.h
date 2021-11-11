#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "CharactersInterface.h"
#include "IObservable.h"

class Characters: CharactersInterface, public IObservable{
public:
    OBJECT GetObject();
    void SetHealth(int a);
    int GetHealth();
    int GetAttack();

protected:
    int health;
    int attack;
    OBJECT type;
};