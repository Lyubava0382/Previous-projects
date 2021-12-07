
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
    assailable = new int[number_of_limbs];
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