#include "Player.h"
    Player::Player() {
        location = {0,0};
        health = 10;
        key = false;
        attack = 1;
        type = NONE;
        observable = false;
        observer = NULL;
    }
    void Player::SetKey(bool yes) {
        this->key = yes;
        notify(__FUNCTION__, yes);
    }
    bool Player::GetKey() const{
        return this->key;
    }
    void Player::SetLocal(Coordinates place) {
        this->location = place;
        notify(__FUNCTION__, place);
    }
    Coordinates Player::GetLocal() {
        return this->location;
    }
    void Player::SetCoins(int number) {
        this->coins += number;
        notify(__FUNCTION__, number);
    }
    int Player::GetCoins() {
        return this->coins;
    }
