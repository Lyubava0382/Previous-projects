
#include "Heal.h"

Heal::Heal(){
        type = FOOD;
        observable = false;
        observer = nullptr;
    }

    void Heal::interplay(Player& person){
        int add_lives = rand() % 10;
        if(add_lives + person.GetHealth() < 10)
            person.SetHealth(add_lives + person.GetHealth());
        else person.SetHealth(10);
        notify(__FUNCTION__, *this);
    }
