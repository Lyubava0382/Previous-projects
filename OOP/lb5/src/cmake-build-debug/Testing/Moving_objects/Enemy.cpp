

#include "Enemy.h"
#include "Lmonster.h"
#include "Mmonster.h"
#include "Smonster.h"

void Enemy::fight(Player& hero){
    if (dynamic_cast<Lmonster*>(this)) {
        dynamic_cast<Lmonster*>(this)->fight(hero);
        return;
    }
     if (dynamic_cast<Mmonster*>(this)) {
        dynamic_cast<Mmonster*>(this)->fight(hero);
        return;
    }
    if (dynamic_cast<Smonster*>(this)) {
        dynamic_cast<Smonster*>(this)->fight(hero);
        return;
    }
}
void Enemy::SetHealth(int a){
    this->health = a;
    notify(*this, __FUNCTION__);
}
int Enemy::GetHealth() {
    return this->health;
}
int Enemy::GetReward(){
    return this->reward;
}
bool Enemy::GetGoing(){
    return this->goon;
}
int Enemy::GetLimb(int index){
    return this->assailable[index];
}
void Enemy::hit(Player& hero) {
    this->health = health - hero.GetAttack();
    if (health <= 0){
        goon = false;
        hero.SetCoins(reward);
    }
    notify(*this, __FUNCTION__);
}
void Enemy::miss(Player& hero){
    hero.SetHealth(hero.GetHealth() - attack);
    MissMonsterPrint(hero.GetHealth());
    if (hero.GetHealth() <= 0){
        goon = false;
        GameView().GameOver();
    }
    notify(*this, __FUNCTION__);
}
void Enemy::moving(Cellule& locate, Field& game, Player& person){
    if (dynamic_cast<Lmonster*>(this)) {
        dynamic_cast<Lmonster*>(this)->moving(locate,game, person);
    }
    else if (dynamic_cast<Mmonster*>(this)) {
        dynamic_cast<Mmonster*>(this)->moving(locate,game, person);
    }
    else if (dynamic_cast<Smonster*>(this)) {
        dynamic_cast<Smonster*>(this)->moving(locate,game, person);
    }
};

Coordinates Enemy::GetStep(int length) {
    switch (nextstep) {
        case START:
        case STOP:
            return {0,0};
        case RIGHT:
            return {length,0};
        case LEFT:
            return {-length,0};
        case UP:
            return {0,-length};
        case DOWN:
            return {0,length};
    }
}

void Enemy::SetStep(GO step) {
    this->nextstep = step;
    notify(*this, __FUNCTION__);
}