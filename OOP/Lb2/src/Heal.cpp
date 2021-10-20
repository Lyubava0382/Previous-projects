#include "Heal.h"
    Heal::Heal(): type(FOOD){}

    void Heal::interplay(Player& person){
        person.SetHealth(rand() % 10 + person.GetHealth());
    };

    OBJECT Heal::GetObject(){
        return this->type;
    }

