#include "Characters.h"

OBJECT Characters::GetObject(){
        return this->type;
    }
    void Characters::SetHealth(int a){
        this->health = a;
        notify(__FUNCTION__, a);
    }
    int Characters::GetHealth() {
        return this->health;
    }
    int Characters::GetAttack() {
        return this->attack;
    }