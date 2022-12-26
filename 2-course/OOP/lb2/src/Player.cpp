#include "Player.h"
    Player::Player() {
        location = {0,0};
        health = 10;
        key = false;
        attack = 1;
        type = NONE;
    }
    void Player::SetHealth(int a){
        this->health = a;
    }
    int Player::GetHealth() {
        return this->health;
    }
    int Player::GetAttack() {
        return this->attack;
    }
    void Player::SetKey(bool yes) {
        this->key = yes;
    }
    bool Player::GetKey() const{
        return this->key;
    }
    OBJECT Player::GetObject(){
        return this->type;
    }
    void Player::SetLocal(Coordinates place) {
        this->location = place;
    }
    Coordinates Player::GetLocal() {
        return this->location;
    }
    void Player::SetCoins(int number) {
        this->coins += number;
    }
    int Player::GetCoins() {
        return this->coins;
    }

