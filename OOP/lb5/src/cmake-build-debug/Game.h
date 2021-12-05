//
// Created by Любава on 24.11.2021.
//

#ifndef UNTITLED6_GAME_H
#define UNTITLED6_GAME_H


#include "Testing/Views/ExitDoorPrint.h"
#include "Testing/Views/FieldView.h"
#include "Testing/Views/GameView.h"
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
        game_end = false;
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
        game_interface = GameView();
        Start();
    }

    Field * GetField() {
        return &(this->game);
    }
    Player * GetPlayer(){
        return &(this->person);
    }
    ~Game(){

    }
    void Over(){
        game_end = true;
    }
private:

    void monsterStep(Cellule& cell, int monster_count){
        Coordinates new_coord = {0,0};
        Enemy * monster;
        if (dynamic_cast<Enemy*>(cell.GetObj())) monster = dynamic_cast<Enemy*>(cell.GetObj());
        else return;
        new_coord = {cell.GetPoint().x + monster->GetStep().x, cell.GetPoint().y + monster->GetStep().y};
        if (&cell != &game.GetField()[new_coord.y][new_coord.x]){
            OBJECT swap_occupy = game.GetField()[new_coord.y][new_coord.x].GetObject();
            game.GetField()[new_coord.y][new_coord.x].SetObject(cell.GetObject());
            cell.SetObject(swap_occupy);
            Interior* swap_object = game.GetField()[new_coord.y][new_coord.x].GetObj();
            game.GetField()[new_coord.y][new_coord.x].SetObj(cell.GetObj());
            cell.SetObj(swap_object);
            game.SetMonsters(monster_count, new_coord);
        }
    }
/*
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
    } */

    void EnemyMove()
    {
        for (int k = 0; k < game.GetMonsterCount(); k++) {
            dynamic_cast<Enemy*>(game.GetField()[ game.GetMonsters()[k].y][ game.GetMonsters()[k].x].GetObj())->moving(game.GetField()[ game.GetMonsters()[k].y][ game.GetMonsters()[k].x], game, person);
            monsterStep(game.GetField()[ game.GetMonsters()[k].y][ game.GetMonsters()[k].x],k);
        }
    }

    bool GameMove(Coordinates motion) {
        Coordinates back;
        back = person.GetLocal();
        person.SetLocal(person.GetLocal().x + motion.x,person.GetLocal().y + motion.y);
        EnemyMove();
        switch (game.GetField()[person.GetLocal().y][person.GetLocal().x].GetType()) {
            case NOPASS:
            case IN:
                person.SetLocal(back.x,back.y);
                break;
            case OUT: {
                //person.SetKey(true);
                if (win_rules.Done(person)){
                        Over();
                    return false;
                }
            }
                break;
            case PASSABLE: {
                if (dynamic_cast<Item*>(game.GetField()[person.GetLocal().y][person.GetLocal().x].GetObj())){
                    Item* thing = dynamic_cast<Item*>(game.GetField()[person.GetLocal().y][person.GetLocal().x].GetObj());
                    thing ->interplay(person);
                    if (thing->remove()){
                        game.GetField()[person.GetLocal().y][person.GetLocal().x].SetObject(NONE);
                        delete dynamic_cast<Item*>(game.GetField()[person.GetLocal().y][person.GetLocal().x].GetObj());
                        game.GetField()[person.GetLocal().y][person.GetLocal().x].SetObj(new Empty);
                    }
                }
                else if(dynamic_cast<Enemy*>(game.GetField()[person.GetLocal().y][person.GetLocal().x].GetObj())){
                    Enemy* monster = dynamic_cast<Enemy*>(game.GetField()[person.GetLocal().y][person.GetLocal().x].GetObj());
                    monster->fight(person);
                    if(monster->GetHealth() <= 0) {
                        game.GetField()[person.GetLocal().y][person.GetLocal().x].SetObject(NONE);
                        monster->SetStep(STOP);
                        delete dynamic_cast<Enemy*>(game.GetField()[person.GetLocal().y][person.GetLocal().x].GetObj());
                       game.GetField()[person.GetLocal().y][person.GetLocal().x].SetObj(new Empty);
                    }
                    if(person.GetHealth() <= 0){
                        Over();
                        return false;
                    }

                }
            }
                break;
        }
        return true;
    }

    void Start() {
        //Logger log(person);
        //person.SetKey(true);
        //Logger log2(game);
        srand(time(NULL));
        game.MakeInOut();
        game.MakeObjects(field_rules.GetWallChance());
        person.SetLocal(game.GetIn().x,game.GetIn().y);
        game.MakeItems(number_of_items.GetPortalCount(), number_of_items.GetBoxCount(), number_of_items.GetHealCount());
        game.MakeEnemies(number_of_enemies.GetScount(), number_of_enemies.GetMcount(), number_of_enemies.GetLcount());
        game_interface.PrintMenu();
        FieldView(game, person).Print();
         while(game_interface.Goon() && !game_end){
             Coordinates motion = game_interface.GameInput();
            if (motion.x == 0 && motion.y == 0) {
               Over();
               return;
            }
           if (GameMove(motion)) FieldView(game, person).Print();
        }
        }



    Field game;
    Player person;
    T1 field_rules;
    T2 number_of_enemies;
    T3 number_of_items;
    T4 win_rules;
    GameView game_interface;
    bool game_end;
};




#endif //UNTITLED6_GAME_H
