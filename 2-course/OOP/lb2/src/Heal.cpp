#include "Heal.h"
    Heal::Heal(): type(FOOD){}

    void Heal::interplay(Player& person){
        int a = rand() % 10;
                if (a + person.GetHealth() > 10)
                    person.SetHealth(10);
                else person.SetHealth(a + person.GetHealth());
    };

    OBJECT Heal::GetObject(){
        return this->type;
    }

