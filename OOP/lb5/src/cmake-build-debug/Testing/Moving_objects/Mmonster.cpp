
#include "Mmonster.h"
#include "../Gaming_Space/Cellule.h"
#include "../../Game.h"
Mmonster::Mmonster(){
    health = 3;
    attack = 2;
    observable = false;
    reward = 1;
    observer = nullptr;
    type = MEDIUMMONSTER;
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

void Mmonster::fight(Player& hero){
    int body;
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
            assailable[body] = 0;
            hit(hero);
            HitMonsterPrint(type, health, shot);
        }
        else {
            if (goon) miss(hero);
        }
    }
}
void Mmonster::moving(Cellule& locate, Field& game, Player& person){
    const int number_of_directions = 4;
    GO array[number_of_directions] = {RIGHT, DOWN, LEFT, UP};
    switch (nextstep) {
        case START:
            for (int i = 0; i < number_of_directions; i += 2) {
                nextstep = array[i];
                if (game.Access({locate.GetPoint().x + GetStep(1).x,locate.GetPoint().y + GetStep(1).y }))
                    break;
            }
            if (!game.Access({locate.GetPoint().x + GetStep(1).x,locate.GetPoint().y + GetStep(1).y }))
                nextstep = STOP;
            break;
        default:
            if (!game.Access({locate.GetPoint().x + GetStep(1).x,locate.GetPoint().y + GetStep(1).y })) {
                if (nextstep == array[0])
                    nextstep = array[2];
                else if (nextstep == array[2])
                    nextstep = array[0];
            }
            break;
    }
}