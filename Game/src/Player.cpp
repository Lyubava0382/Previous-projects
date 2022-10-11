//
// Created by Serg on 10.10.2022.
//

#include "Player.h"
Player::Player() {
    location = {0,0};
    keys = 0;
    keyCount = 0;
    type = NONE;
}

bool Player::Done() const{
    return keys == keyCount;
}
OBJECT Player::GetObject(){
    return this->type;
}
void Player::SetLocal(int placex, int placey) {
    this->location.x = placex;
    this->location.y = placey;
}

void Player::SetCountKeys(int count){
    keyCount = count;
}
void Player::Key(){
    keys++;
}

Coordinates Player::GetLocal() {
    return this->location;
}


