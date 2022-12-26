//
// Created by Любава on 24.11.2021.
//

#ifndef UNTITLED6_GAME_H
#define UNTITLED6_GAME_H

#include "Testing/Static_Items/Teleport.h"
#include "Testing/Views/ExitDoorPrint.h"
#include "Testing/Views/FieldView.h"
#include "Testing/Views/Controller.h"
#include "Testing/Views/GameView.h"
#include "Testing/Rules/CanonNumberOfItems.h"
#include "Testing/Rules/CanonNumberOfEnemies.h"
#include "Testing/Rules/CanonRuleOfField.h"
#include "Testing/Rules/CanonRuleOfWin.h"
#include "Testing/Static_Items/Box.h"
#include "Testing/Static_Items/Heal.h"
#include "Testing/Moving_objects/Smonster.h"
#include "Testing/Moving_objects/Lmonster.h"
#include "Testing/Moving_objects/Mmonster.h"
#include "Except4Game.h"


template <typename T1 = CanonRuleOfField<10,15,10>, typename T2 = CanonNumberOfEnemies<nullptr,0>,
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

        T2 number_of_enemy;
        number_of_enemies = number_of_enemy;

        T3 number_of_item(field_rules.GetSize());
        number_of_items = number_of_item;

        T4 win_rule;
        win_rules = win_rule;

        Field game1( field_rules.GetWidth(),  field_rules.GetHeight());
        game = game1;
        game_interface = Controller();
        Start();
    }

    ~Game(){

    }
    void Over(){
        game_end = true;
         Saving();
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

    void EnemyMove()
    {
        for (int k = 0; k < game.GetMonsterCount(); k++) {
            dynamic_cast<Enemy*>(game.GetField()[ game.GetMonsters()[k].y][ game.GetMonsters()[k].x].GetObj())->moving(game.GetField()[ game.GetMonsters()[k].y][ game.GetMonsters()[k].x], game, person);
            monsterStep(game.GetField()[ game.GetMonsters()[k].y][ game.GetMonsters()[k].x],k);
        }
    }

  void Act(Item* thing){
      thing ->interplay(person);
    }
    void Act(Enemy* monster){
        monster->fight(person);
    }

    bool Remove(Item* thing){
        if (thing->remove()){
            delete (thing);
            return true;
        }
        return thing->remove();
    }
    bool Remove(Enemy* monster){
        if (monster->GetHealth() <= 0) {
            monster->SetStep(STOP);
            delete (monster);
            return true;
        }
        else return false;
    }

    bool GameMove(Coordinates motion) {
        EnemyMove();
        if (game.WithinField({person.GetLocal().x + motion.x, person.GetLocal().y + motion.y}))
            person.SetLocal(person.GetLocal().x + motion.x, person.GetLocal().y + motion.y);
        switch (game.GetField()[person.GetLocal().y][person.GetLocal().x].GetType()) {
            case OUT: {
                //person.SetKey(true);
                if (win_rules.Done(person)) {
                    Over();
                    return false;
                }
            }
                break;
            case PASSABLE: {
                bool removing = false;
                if (dynamic_cast<Item *>(game.GetField()[person.GetLocal().y][person.GetLocal().x].GetObj())) {
                    Act(dynamic_cast<Item*>(game.GetField()[person.GetLocal().y][person.GetLocal().x].GetObj()));
                    removing = Remove(dynamic_cast<Item *>(game.GetField()[person.GetLocal().y][person.GetLocal().x].GetObj()));
                } else if (dynamic_cast<Enemy *>(game.GetField()[person.GetLocal().y][person.GetLocal().x].GetObj())) {
                    Act(dynamic_cast<Enemy *>(game.GetField()[person.GetLocal().y][person.GetLocal().x].GetObj()));
                    removing = Remove(
                            dynamic_cast<Enemy *>(game.GetField()[person.GetLocal().y][person.GetLocal().x].GetObj()));
                }
                if (removing) {
                    game.GetField()[person.GetLocal().y][person.GetLocal().x].SetObject(NONE);
                    game.GetField()[person.GetLocal().y][person.GetLocal().x].SetObj(new Empty);
                }
                if (person.GetHealth() <= 0) {
                    Over();
                    return false;
                }

                break;
            }
        }
                return true;
    }

    void LoadGame(){
        std::string loading_name;
        GameView().Save_Load_text();
        std::cin >> loading_name;
        std::ifstream input_file("./Saves/"+loading_name);
        if (!input_file.is_open()){
            throw Except4Game(FILE_ERROR);
        }
            int width, height, minimum_value;
        minimum_value = 3;
        input_file >> height >> width;
        if (height < minimum_value || width < minimum_value)
            throw Except4Game(BORDER_ERROR);
        if (width != game.GetWidth() || height != game.GetHeight()){
            Field game2( width,  height);
            game = game2;
        }
        for (int i = 0; i < height; i ++){
            for (int j = 0; j < width; j ++){ 
                int x, y, type, interior;
                input_file >> x >> y >> type >> interior;
                if (x < 0 || y < 0)
                    throw Except4Game(BORDER_ERROR);
                game.GetField()[i][j].SetType(TYPE(type));
                game.GetField()[i][j].SetObject(OBJECT(interior));
                if (type == 2){
                    game.SetIn({j,i});
                }
                if (type == 3){
                    game.SetOut({j,i});
                }
                switch (interior) {
                    case 1: {
                        game.GetField()[i][j].SetObject(FOOD);
                        game.GetField()[i][j].SetObj(new Heal());
                        break;
                    }
                    case 2: {
                        int full;
                        input_file >> full;
                        game.GetField()[i][j].SetObject(BOX);
                        game.GetField()[i][j].SetObj(new Box(bool(full)));
                        break;
                    }
                    case 3: {
                        int one_x, one_y, two_x, two_y;
                        input_file >> one_x >> one_y >> two_x >>two_y;
                        game.SetTeleports({one_x, one_y}, {two_x, two_y});
                        game.GetField()[i][j].SetObject(PORTAL);
                        game.GetField()[i][j].SetObj(new Teleport(game.GetTeleports()));
                        break;
                    }
                    case 4:{
                        int hp;
                        input_file >> hp;
                        game.GetField()[i][j].SetObject(SMALLMONSTER);
                        game.GetField()[i][j].SetObj(new Smonster());
                        dynamic_cast<Smonster*>(game.GetField()[i][j].GetObj())->SetHealth(hp);
                        game.SetMonsters(game.GetMonsterCount(), {j,i});
                        game.SetMonsterCount();
                        break;
                    }
                    case 5:{
                        int hp;
                        input_file >> hp;
                        game.GetField()[i][j].SetObject(MEDIUMMONSTER);
                        game.GetField()[i][j].SetObj(new Mmonster());
                        dynamic_cast<Mmonster*>(game.GetField()[i][j].GetObj())->SetHealth(hp);
                        game.SetMonsters(game.GetMonsterCount(), {j,i});
                        game.SetMonsterCount();
                        break;
                    }
                    case 6:{
                        int hp;
                        input_file >> hp;
                        game.GetField()[i][j].SetObject(LARGEMONSTER);
                        game.GetField()[i][j].SetObj(new Lmonster());
                        dynamic_cast<Lmonster*>(game.GetField()[i][j].GetObj())->SetHealth(hp);
                        game.SetMonsters(game.GetMonsterCount(), {j,i});
                        game.SetMonsterCount();
                        break;
                    }
                }
            }
        }
        int p_x,p_y, health, ky, money;
        input_file >> p_x >> p_y >> health >>ky >> money;
        if (p_x < 0 || p_y < 0)
            throw Except4Game(BORDER_ERROR);
        person.SetLocal(p_x,p_y);
        person.SetHealth(health);
        person.SetKey(ky);
        person.SetCoins(money);
    }

    void NewGame(){
        game.MakeInOut();
        game.MakeObjects(field_rules.GetWallChance());
        person.SetLocal(game.GetIn().x,game.GetIn().y);
        game.MakeItems(number_of_items.GetPortalCount(), number_of_items.GetBoxCount(), number_of_items.GetHealCount());
        game.MakeEnemies(number_of_enemies.GetMonsterArray(field_rules.GetSize()), number_of_enemies.GetCount());

    }
    void FileSafety(GO act){
        switch (act) {
            case SAVE:{
                try {
                    Saving();
                }
                catch (Except4Game& exception){
                    std::cerr << exception.GetMessage() << std::endl;
                    game_end = true;
                }
                break;
            }
            case LOAD:{
                try {
                    LoadGame();
                }
                catch (Except4Game& exception){
                    std::cerr << exception.GetMessage()<< std::endl;
                    Over();
                }
                break;
            }
        }
    }

    void Start() {
        srand(time(NULL));
        GameView().GameLoading();
        char loading_game;
        std::cin >> loading_game;
        if (loading_game == 'y'){
            LoadGame();
        }
        else {
            NewGame();
        }
        game_interface.Menu();
        FieldView(game, person).Print();
         while(game_interface.Goon() && !game_end){
             Coordinates motion;
             GO step_player = game_interface.GameInput();
             switch (step_player) {
                 case UP:{
                     motion = {0,-1};
                     break;
                 }
                 case LEFT:{
                     motion = {-1,0};
                     break;
                 }
                 case DOWN:{
                     motion = {0,1};
                     break;
                 }
                 case RIGHT:{
                     motion = {1,0};
                     break;
                 }
                 case STOP:{
                     Over();
                     break;
                 }
                 default:{
                     FileSafety(step_player);
                     motion = {0,0};
                     break;
                 }
             }
           if (!game_end && GameMove(motion)) FieldView(game, person).Print();
        }
        }
void Saving(){
    std::string savename;
    GameView().Save_Load_text();
    std::cin >> savename;
    std::ofstream out("./Saves/"+savename);
    out << game.GetHeight() << ' ' << game.GetWidth() << std::endl;
    for (int i = 0; i < game.GetHeight(); i ++){
        for (int j = 0; j < game.GetWidth(); j ++){
            out << game.GetField()[i][j].GetPoint().x << ' ' << game.GetField()[i][j].GetPoint().y<< ' '
            << game.GetField()[i][j].GetType()<< ' ' << game.GetField()[i][j].GetObject() ;
                if (game.GetField()[i][j].GetObject() == int(BOX))  {
                            out << ' ' << dynamic_cast <Box*>(game.GetField()[i][j].GetObj())->GetFull() ;
                    }
                else if (game.GetField()[i][j].GetObject() == int(PORTAL)){
                    out << ' ' << game.GetTeleports().first.x  << ' ' << game.GetTeleports().first.y
                            << ' ' << game.GetTeleports().second.x << ' ' << game.GetTeleports().second.y ;
                }
                else if (game.GetField()[i][j].GetObject() >= int(SMALLMONSTER)){
                    out << ' ' << dynamic_cast <Enemy*>(game.GetField()[i][j].GetObj())->GetHealth() ;
                }
            out << std::endl;
                }
            }
    out << person.GetLocal().x << ' ' << person.GetLocal().y << ' ' << person.GetHealth()<< ' ' << person.GetKey()
    << ' ' << person.GetCoins()<< std::endl;
    out.close();
    }


    Field game;
    Player person;
    T1 field_rules;
    T2 number_of_enemies;
    T3 number_of_items;
    T4 win_rules;
    Controller game_interface;
    bool game_end;
};




#endif //UNTITLED6_GAME_H
