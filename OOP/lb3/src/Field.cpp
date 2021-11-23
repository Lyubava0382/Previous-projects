//
// Created by Любава on 13.11.2021.
//

#include "Field.h"
#include "math.h"
Field::Field(int w, int h){
        width = w;
        height = h;
        monstercount = 0;
        observable = false;
        observer = nullptr;
        field = new Cellule*[height];
        for (int i = 0; i < height; i ++){
            field[i] = new Cellule[width];
            for (int j = 0; j < width; j ++){
                field[i][j].SetPoint(j, i);
            }
        }
        Monsters = new Coordinates[100];
    }
Field::~Field() {
        for (int i = 0; i < height; i ++) {
            delete[] field[i];
        }
        delete[] field;
        delete[] Monsters;
    }

Field::Field(const Field &other) :  width(other.width), height(other.height),
                                 in(other.in), out(other.out),  monstercount(other.monstercount), field(new Cellule*[height]),
                                 teleports(other.teleports){ // Конструктор копирования
        Monsters = new Coordinates[100];
        for (int i = 0; i < height; i ++) {
            field[i] = new Cellule[width];
            for (int j = 0; j < width; j ++){
                field[i][j] = other.field[i][j];
            }
        }
        for (int k = 0; k < monstercount; k ++){
            Monsters[k] = other.Monsters[k];
        }
        observable = other.observable;
        observer = other.observer;
    }

    Field& Field::operator = (const Field &other) { // Оператор присваивания копированием
        if (this != &other){
            for (int i = 0; i < height; i ++){
                delete[] field[i];
            }
            delete[] field;
            delete[] Monsters;
            width = other.width;
            height = other.height;
            in = other.in;
            out = other.out;
            observable = other.observable;
            observer = other.observer;
            teleports = other.teleports;
            monstercount = other.monstercount;
            field = new Cellule* [height];
            for (int i = 0; i < height; i ++) {
                field[i] = new Cellule[width];
                for (int j = 0; j < width; j ++){
                    field[i][j] = other.field[i][j];
                }
            }
            Monsters = new Coordinates[100];
            for (int k = 0; k < monstercount; k ++){
                Monsters[k] = other.Monsters[k];
            }
        }
        return *this;
    }

Field::Field(Field&& other){ // Конструктор перемещения
        std::swap(this->width, other.width);
        std::swap(this->height, other.height);
        std::swap(this->in, other.in);
        std::swap(this->out, other.out);
        std::swap(this->Monsters, other.Monsters);
        std::swap(this->monstercount, other.monstercount);
        std::swap(this->field, other.field);
        std::swap(this->observable, other.observable);
        std::swap(this->observer, other.observer);
        std::swap(this->teleports, other.teleports);
    }

    Field& Field::operator=(Field&& other) { // Оператор присваивания перемещением
        if (this != &other) {
            std::swap(this->width, other.width);
            std::swap(this->height, other.height);
            std::swap(this->in, other.in);
            std::swap(this->out, other.out);
            std::swap(this->Monsters, other.Monsters);
            std::swap(this->monstercount, other.monstercount);
            std::swap(this->field, other.field);
            std::swap(this->observable, other.observable);
            std::swap(this->observer, other.observer);
            std::swap(this->teleports, other.teleports);
        }
        return *this;
    }
    void Field::MakeInOut() {
        in = {rand() % width, rand() % height};
        field[in.y][in.x].SetType(IN);
        out = {rand() % width, rand() % height};
        double distance_share = 0.2;
        while (abs(out.x - in.x) < round(distance_share * width) || abs(out.y - in.y) < round(distance_share * height) ){

            out = {rand() % width, rand() % height};
        }
        field[out.y][out.x].SetType(OUT);
        notify(__FUNCTION__, *this);
    }

    Coordinates Field::GetIn() {
        return this->in;
    }
    Coordinates Field::GetOut() {
        return this->out;
    }

    void Field::MakeObjects() {
        int chance = 10;
        int wall_appearance;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                Coordinates any = {j, i};
                wall_appearance = rand() % 100 + 1;
                if ((wall_appearance <= chance) && (field[any.y][any.x].GetType() != IN) && (field[any.y][any.x].GetType() != OUT)) //10% chance
                    field[any.y][any.x].SetType(NOPASS);
            }
        }
        notify(__FUNCTION__, *this);
    }

    void Field::MakeItems() {
        double share_of_field_for_items;
        teleports.first = {rand() % width, rand() % height};
        while (field[teleports.first.y][teleports.first.x].GetType() != PASSABLE)
            teleports.first = {rand() % width, rand() % height};
        teleports.second = {rand() % width, rand() % height};
        while (field[teleports.second.y][teleports.second.x].GetType() != PASSABLE)
            teleports.second = {rand() % width, rand() % height};

        field[teleports.first.y][teleports.first.x].SetObject(PORTAL);
        field[teleports.second.y][teleports.second.x].SetObject(PORTAL);

        share_of_field_for_items = 0.02;

        int number_of_items = round(share_of_field_for_items * width * height);
        Coordinates treasure;
        treasure = {rand() % width, rand() % height};
        while (field[treasure.y][treasure.x].GetType() != PASSABLE || field[treasure.y][treasure.x].GetObject() != NONE)
            treasure = {rand() % width, rand() % height};
        field[treasure.y][treasure.x].SetObject(BOX);
        field[treasure.y][treasure.x].SetKey(true);
        for (int i = 0; i < number_of_items - 1; i++) {
            treasure = {rand() % width, rand() % height};
            while (field[treasure.y][treasure.x].GetType() != PASSABLE ||
                   field[treasure.y][treasure.x].GetObject() != NONE)
                treasure = {rand() % width, rand() % height};
            field[treasure.y][treasure.x].SetKey(false);
            field[treasure.y][treasure.x].SetObject(BOX);
        }
        Coordinates healing;
        for (int i = 0; i < number_of_items; i++) {
            healing = {rand() % width, rand() % height};
            while (field[healing.y][healing.x].GetType() != PASSABLE || field[healing.y][healing.x].GetObject() != NONE)
                healing = {rand() % width, rand() % height};
            field[healing.y][healing.x].SetObject(FOOD);
        }
        notify(__FUNCTION__, *this);
    }
    void Field::MakeEnemies() {
        Coordinates monster;
        int number_of_monsters;
        double share_of_field_for_monsters;
        const int monster_categories = 3;
        OBJECT whichone;
        for (int monster_creation_stage = 0; monster_creation_stage < monster_categories; monster_creation_stage++){
            switch (monster_creation_stage) {
                case 0 :
                    share_of_field_for_monsters = 0.02;
                    number_of_monsters = round(share_of_field_for_monsters * width * height);
                    //number_of_monsters = 3;
                    whichone = SMALLMONSTER;
                    break;
                case 1:
                    share_of_field_for_monsters = 0.01;
                    number_of_monsters = round(share_of_field_for_monsters * width * height);
                    whichone = MEDIUMMONSTER;
                    break;
                case 2:
                    number_of_monsters = 1;
                    whichone = LARGEMONSTER;
                    break;
            }
            for (int i=0; i < number_of_monsters; i++) {
                monster = {rand() % width, rand() % height};
                while (field[monster.y][monster.x].GetType() != PASSABLE || field[monster.y][monster.x].GetObject() != NONE)
                    monster = {rand() % width, rand() % height};
                field[monster.y][monster.x].SetStep(START);
                Monsters[monstercount++] = {monster.x, monster.y};
                field[monster.y][monster.x].SetObject(whichone);
            }
        }
        notify(__FUNCTION__, *this);
    }

    bool Field::Access(Coordinates presentstate){
        switch (field[presentstate.y][presentstate.x].GetStep()) {
            case RIGHT:
                presentstate.x++;
                break;
            case LEFT:
                presentstate.x--;
                break;
            case UP:
                presentstate.y--;
                break;
            case DOWN:
                presentstate.y++;
                break;
        }
        if ((presentstate.x >= 0) && (presentstate.x < width) &&
            (presentstate.y >= 0) && (presentstate.y < height) &&
            (field[presentstate.y][presentstate.x].GetType() == PASSABLE) && (field[presentstate.y][presentstate.x].GetObject() == NONE))
            return true;
        else return false;
    }


    int Field::GetHeight() {
        return this->height;
    }

    int Field::GetWidth() {
        return this->width;
    }
    int Field::GetMonsterCount() {
        return this->monstercount;
    }

    Cellule** Field::GetField() {
        return this->field;
    }

    std::pair <Coordinates, Coordinates> Field::GetTeleports() {
        return this->teleports;
    }

    Coordinates* Field::GetMonsters() {
        return this->Monsters;
    }
