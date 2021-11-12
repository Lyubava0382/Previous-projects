//
// Created by Любава on 12.11.2021.
//

#include "Player.h"
Player::Player() {
    location = {0,0};
    health = 10;
    key = false;
    attack = 1;
    type = NONE;
    observable = false;
    observer = nullptr;
    coins = 0;
}
int Player::GetHealth() {
    return this->health;
}
void Player::SetKey(bool yes) {
    this->key = yes;
    notify(__FUNCTION__, *this);
}
bool Player::GetKey() {
    return this->key;
}
void Player::SetHealth(int a){
    this->health = a;
    notify(__FUNCTION__, *this);
}
void Player::SetLocal(Coordinates place) {
    this->location = place;
    notify(__FUNCTION__, *this);
}
Coordinates Player::GetLocal() {
    return this->location;
}
void Player::SetCoins(int number) {
    this->coins += number;
    notify(__FUNCTION__, *this);
}
int Player::GetCoins() {
    return this->coins;
}