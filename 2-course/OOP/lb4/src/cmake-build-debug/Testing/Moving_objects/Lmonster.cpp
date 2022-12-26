
#include "Lmonster.h"

Lmonster::Lmonster(){
    health = 100;
    attack = 4;
    observable = false;
    observer = nullptr;
    type = LARGEMONSTER;
    goon = true;
    for (int i = 0; i < number_of_limbs; i++) {
        assailable[i] = 0;
    }
    assailable[rand() % number_of_limbs] = 1;
}

void Lmonster::fight(Player& hero){
    int body;
    while (health > 0 && goon){
        char shot = fightView(LARGEMONSTER, hero.GetHealth(), this->health).GetWound();
        switch (shot){
            case '0':
                goon = false;
                break;
            case '1':
                body = 0;
                break;
            case '2':
                body = 1;
                break;
            case '3':
                body = 2;
                break;
            default:
                body = -1;
                break;
        }
        notify(*this, __FUNCTION__);
        if (goon && body >= 0 && assailable[body] == 1) {
            hit(hero);
            HitMonsterPrint(LARGEMONSTER, health, shot);
        }
        else {
            if (goon) miss(hero);
        }
    }
}
void Lmonster::hit(Player& hero){
    this->health = 0;
    goon = false;
    hero.SetCoins(reward);
    notify(*this, __FUNCTION__);
}
void Lmonster::miss(Player& hero){
    hero.SetHealth(hero.GetHealth() - attack);
    MissMonsterPrint(hero.GetHealth());
    if (hero.GetHealth() <= 0){
        goon = false;
        notify(*this, __FUNCTION__);
        //Game Over
    }
}