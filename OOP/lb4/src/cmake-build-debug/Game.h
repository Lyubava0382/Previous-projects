//
// Created by Любава on 24.11.2021.
//

#ifndef UNTITLED6_GAME_H
#define UNTITLED6_GAME_H


#include "Testing/Views/ExitDoorPrint.h"
#include "Testing/Views/FieldView.h"
#include "Testing/Rules/CanonNumberOfItems.h"
#include "Testing/Rules/CanonNumberOfEnemies.h"
#include "Testing/Rules/CanonRuleOfField.h"
#include "Testing/Rules/CanonRuleOfWin.h"
#include "Testing/Static_Items/Box.h"
#include "Testing/Static_Items/Teleport.h"
#include "Testing/Static_Items/Heal.h"
#include "Testing/Moving_objects/Smonster.h"
#include "Testing/Moving_objects/Lmonster.h"
#include "Testing/Moving_objects/Mmonster.h"

template <typename T1 = CanonRuleOfField<10,15,10>, typename T2 = CanonNumberOfEnemies<2, 1, 1>,
        typename T3 = CanonNumberOfItems<2, 2, 1>, typename T4 = CanonRuleOfWin<true,0,0>>
class Game: public IObservable {
public:
    explicit Game(){
        Player p1;
        person = p1;
        observable = false;
        observer = nullptr;

        T1 field_rule;
        field_rules =  field_rule;

        T2 number_of_enemy(field_rules.GetSize());
        number_of_enemies = number_of_enemy;

        T3 number_of_item(field_rules.GetSize());
        number_of_items = number_of_item;

        T4 win_rule;
        win_rules = win_rule;

        Field game1( field_rules.GetWidth(),  field_rules.GetHeight());
        game = game1;
        //Logger log2(game.GetField()[1][1]);
        Start();
    }

    Field * GetField() {
        return &(this->game);
    }
    Player * GetPlayer(){
        return &(this->person);
    }
private:
    void NextCondition(Cellule& locate){
        const int number_of_directions = 3;
        GO array[number_of_directions + 1] = {RIGHT, DOWN, LEFT, UP};
        switch (locate.GetObject()) {
            case SMALLMONSTER: {
                switch (locate.GetStep()) {
                    case START:
                        for (int i = 0; i <= number_of_directions; i++) {
                            locate.SetStep(array[i]);
                            if (game.Access(locate.GetPoint()))
                                break;
                        }
                        if (!game.Access(locate.GetPoint()))
                            locate.SetStep(STOP);
                        break;
                    default:
                        do{
                            for (int i = 0; i <= number_of_directions; i++){
                                if (array[i] == locate.GetStep()){
                                    if (i  < number_of_directions) locate.SetStep(array[i+1]);
                                    else locate.SetStep(array[i-number_of_directions]);
                                    break;
                                }
                            }
                        } while (!game.Access(locate.GetPoint()));
                        break;
                }
            }
            case MEDIUMMONSTER:{
                switch (locate.GetStep()) {
                    case START:
                        for (int i = 0; i <= number_of_directions; i += 2) {
                            locate.SetStep(array[i]);
                            if (game.Access(locate.GetPoint()))
                                break;
                        }
                        if (!game.Access(locate.GetPoint()))
                            locate.SetStep(STOP);
                        break;
                    default:
                        if (!game.Access(locate.GetPoint())) {
                            if (locate.GetStep() == array[0])
                                locate.SetStep(array[2]);
                            else if (locate.GetStep() == array[2])
                                locate.SetStep(array[0]);
                        }
                        break;
                }
                break;
            }
            case LARGEMONSTER:{
                if (abs(person.GetLocal().x - locate.GetPoint().x) < abs(person.GetLocal().y - locate.GetPoint().y)){
                    if(person.GetLocal().y > locate.GetPoint().y) locate.SetStep(DOWN);
                    if(person.GetLocal().y < locate.GetPoint().y) locate.SetStep(UP);
                }
                else{
                    if(person.GetLocal().x > locate.GetPoint().x) locate.SetStep(RIGHT);
                    if(person.GetLocal().x < locate.GetPoint().x) locate.SetStep(LEFT);
                }
                if (!game.Access(locate.GetPoint()))
                    locate.SetStep(STOP);
                break;
            }
        }
    }

    void Step(GO side, Coordinates begin, int k){
        const int stride_length = 1;
        switch (side) {
            case RIGHT:
                game.GetMonsters()[k] = {begin.x + stride_length, begin.y};
                break;
            case LEFT:
                game.GetMonsters()[k] = {begin.x - stride_length, begin.y};
                break;
            case UP:
                game.GetMonsters()[k] = {begin.x, begin.y - stride_length};
                break;
            case DOWN:
                game.GetMonsters()[k] = {begin.x, begin.y + stride_length};
                break;
        }
        if (side != START && side != STOP){
            game.GetField()[ game.GetMonsters()[k].y][ game.GetMonsters()[k].x].SetObject(game.GetField()[begin.y][begin.x].GetObject());
            game.GetField()[ game.GetMonsters()[k].y][ game.GetMonsters()[k].x].SetStep(game.GetField()[begin.y][begin.x].GetStep());
            game.GetField()[begin.y][begin.x].SetStep(STOP);
            game.GetField()[begin.y][begin.x].SetObject(NONE);
        }
    }

    void EnemyMove()
    {
        for (int k = 0; k < game.GetMonsterCount(); k++) {
            NextCondition(game.GetField()[ game.GetMonsters()[k].y][ game.GetMonsters()[k].x]);
            Step(game.GetField()[ game.GetMonsters()[k].y][ game.GetMonsters()[k].x].GetStep(),  game.GetMonsters()[k], k);
        }
    }

    void GameMove() {
        Coordinates back;
        EnemyMove();
        back = person.GetLocal();
        /*
         *
         */

        switch (game.GetField()[person.GetLocal().y][person.GetLocal().x].GetType()) {
            case NOPASS:
                person.SetLocal(back);
                break;
            case IN:
                person.SetLocal(back);
                break;
            case OUT: {
                ExitDoorPrint door;
                if (person.GetKey() < win_rules.KeyNeeded()) {
                    door.KeyPrint();
                } else if (person.GetCoins() < win_rules.MinimumMoneyNeeded()) {
                    door.CoinsPrint();
                } else if (person.GetHealth() < win_rules.MinimumHealthNeeded()) {
                    door.HealthPrint();
                } else {
                    door.OpenPrint();
                    //Game Complite
                }
            }
                break;
            case PASSABLE: {
                if (game.GetField()[person.GetLocal().y][person.GetLocal().x].GetObject() != NONE)
                    switch (game.GetField()[person.GetLocal().y][person.GetLocal().x].GetObject()) {
                        case BOX: {
                            Box keybox(game.GetField()[person.GetLocal().y][person.GetLocal().x].GetKey());
                            keybox.interplay(person);
                            game.GetField()[person.GetLocal().y][person.GetLocal().x].SetObject(NONE);
                            game.GetField()[person.GetLocal().y][person.GetLocal().x].SetKey(false);
                            break;
                        }
                        case FOOD: {
                            Heal healing;
                            healing.interplay(person);
                            game.GetField()[person.GetLocal().y][person.GetLocal().x].SetObject(NONE);
                            break;
                        }
                        case PORTAL: {
                            Teleport teleportation(game.GetTeleports());
                            teleportation.interplay(person);
                            break;
                        }
                        case SMALLMONSTER: {
                            Smonster enemy;
                            enemy.fight(person);
                            if(enemy.GetHealth() <= 0) {
                                game.GetField()[person.GetLocal().y][person.GetLocal().x].SetObject(NONE);
                            }
                            break;
                        }
                        case MEDIUMMONSTER: {
                            Mmonster enemy;
                            enemy.fight(person);
                            if(enemy.GetHealth() <= 0) {
                                game.GetField()[person.GetLocal().y][person.GetLocal().x].SetObject(NONE);
                            }
                            break;
                        }
                        case LARGEMONSTER: {
                            Lmonster enemy;
                            enemy.fight(person);
                            if(enemy.GetHealth() <= 0) {
                                game.GetField()[person.GetLocal().y][person.GetLocal().x].SetObject(NONE);
                            }
                            break;
                        }
                    }
            }
                break;
        }
    }

    void Start() {
        Logger log(person);
        person.SetKey(true);
        Logger log2(game);
        srand(time(NULL));
        game.MakeInOut();
        game.MakeObjects(field_rules.GetWallChance());
        person.SetLocal(game.GetIn());
        game.MakeItems(number_of_items.GetPortalCount(), number_of_items.GetBoxCount(), number_of_items.GetHealCount());
        game.MakeEnemies(number_of_enemies.GetScount(), number_of_enemies.GetMcount(), number_of_enemies.GetLcount());

        FieldView(game, person).Print();
        for (int k = 0; k < 3; k++){
            GameMove();
            FieldView(game, person).Print();
        }

        }
    Field game;
    Player person;
    T1 field_rules;
    T2 number_of_enemies;
    T3 number_of_items;
    T4 win_rules;
};



#endif //UNTITLED6_GAME_H
