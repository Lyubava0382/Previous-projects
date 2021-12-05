
#include "Smonster.h"
#include "../Gaming_Space/Cellule.h"
#include "../../Game.h"

Smonster::Smonster(){
    health = 5;
    attack = 1;
    reward = 1;
    observable = false;
    observer = nullptr;
    type = SMALLMONSTER;
    goon = true;
    for (int i = 0; i < number_of_limbs; i++) {
        assailable[i] = 1;
    }
    int random = rand() % number_of_limbs;
    assailable[random] = 0;
    while (assailable[random] == 0){
        random = rand() % number_of_limbs;
    }
    assailable[random] = 0;
}
void Smonster::fight(Player& hero){
    int body;
    if (dynamic_cast<Lmonster*>(this)) {
        dynamic_cast<Lmonster*>(this)->fight(hero);
        return;
    }
    while (health > 0 && goon){
        char shot = fightView(type, hero.GetHealth(), this->health).GetWound();
        switch (shot) {
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
            case '4':
                body = 3;
                break;
            case '5':
                body = 4;
                break;
            default:
                body = -1;
                break;
        }
        notify(*this, __FUNCTION__);
        if (goon && body >= 0 && assailable[body] == 1) {
            hit(hero);
            HitMonsterPrint(type, health, shot);
        }
        else {
            if (goon) miss(hero);
        }
    }
}
void Smonster::moving(Cellule& locate, Field& game, Player& person){
    const int number_of_directions = 4;
    GO array[number_of_directions ] = {RIGHT, DOWN, LEFT, UP};
    switch (nextstep) {
        case START:
            for (int i = 0; i < number_of_directions; i++) {
                nextstep = array[i];
                if (game.Access({locate.GetPoint().x + GetStep(1).x,locate.GetPoint().y + GetStep(1).y }))
                    break;
            }
            if (!game.Access({locate.GetPoint().x + GetStep(1).x,locate.GetPoint().y + GetStep(1).y }))
                nextstep = STOP;
            break;
        default:
            do{
                for (int i = 0; i < number_of_directions; i++){
                    if (array[i] == nextstep){
                        if (i  < number_of_directions-1) nextstep = array[i+1];
                        else nextstep = array[i-number_of_directions+1];
                        break;
                    }
                }
            } while (!game.Access({locate.GetPoint().x + GetStep(1).x,locate.GetPoint().y + GetStep(1).y }));
            break;
    }
}