
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