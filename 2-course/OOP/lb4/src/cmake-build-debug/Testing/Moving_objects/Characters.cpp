
#include "Characters.h"
OBJECT Characters::GetObject(){
    return this->type;
}
int Characters::GetHealth() {
    return this->health;
}
int Characters::GetAttack() {
    return this->attack;
}