
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
    notify(*this, __FUNCTION__);
}
bool Player::GetKey() {
    return this->key;
}
void Player::SetHealth(int a){
    this->health = a;
    notify(*this, __FUNCTION__);
}
void Player::SetLocal(int a, int b) {
    this->location.x = a;
    this->location.y = b;
    notify(*this, __FUNCTION__);
}
Coordinates Player::GetLocal() {
    return this->location;
}
void Player::SetCoins(int number) {
    this->coins += number;
    notify(*this, __FUNCTION__);
}
int Player::GetCoins() {
    return this->coins;
}