
#include "Lmonster.h"
#include "../Gaming_Space/Cellule.h"
#include "../../Game.h"

Lmonster::Lmonster(){
    health = 100;
    reward = 2;
    attack = 4;
    observable = false;
    observer = nullptr;
    type = LARGEMONSTER;
    goon = true;
    assailable = new int[number_of_limbs];
    for (int i = 0; i < number_of_limbs; i++) {
        assailable[i] = 0;
    }
    assailable[rand() % number_of_limbs] = 1;
}

void Lmonster::fight(Player& hero){
    int body;
    while (health > 0 && goon){
        char shot = fightView(LARGEMONSTER, hero.GetHealth(), this->health).GetWound();
        std::cout <<shot<< std::endl;
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
        GameView().GameOver();
    }
}

void Lmonster::moving(Cellule& locate, Field& game, Player& person){
    if (abs(person.GetLocal().x - locate.GetPoint().x) < abs(person.GetLocal().y - locate.GetPoint().y)){
        if(person.GetLocal().y > locate.GetPoint().y) nextstep = DOWN;
        if(person.GetLocal().y < locate.GetPoint().y) nextstep = UP;
    }
    else{
        if(person.GetLocal().x > locate.GetPoint().x) nextstep = RIGHT;
        if(person.GetLocal().x < locate.GetPoint().x) nextstep = LEFT;
    }
    if (!game.Access({locate.GetPoint().x + GetStep(1).x,locate.GetPoint().y + GetStep(1).y }))
        nextstep = STOP;
}