
#include "Heal.h"

Heal::Heal(){
    type = FOOD;
    observable = false;
    observer = nullptr;
    removing = true;
}

void Heal::interplay(Player& person){
    int max_health = 10;
    int add_lives = rand() % max_health;
    if(add_lives + person.GetHealth() < max_health){
        person.SetHealth(add_lives + person.GetHealth());
        ItemView().HealPrint(add_lives);
    }
    else {
        person.SetHealth(max_health);
        ItemView().HealPrint(max_health);
    }

    notify(*this, __FUNCTION__);
}
