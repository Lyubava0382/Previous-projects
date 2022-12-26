//
// Created by Любава on 12.11.2021.
//

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