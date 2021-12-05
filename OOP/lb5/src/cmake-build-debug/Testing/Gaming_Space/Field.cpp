
#include "Field.h"
#include "math.h"
#include "../Static_Items/Teleport.h"
#include "../Static_Items/Box.h"
#include "../Static_Items/Heal.h"
#include "../Moving_objects/Smonster.h"
#include "../Moving_objects/Mmonster.h"
#include "../Moving_objects/Lmonster.h"

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
            field[i][j] =  Cellule();
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
    notify(*this, __FUNCTION__);
}

Coordinates Field::GetIn() {
    return this->in;
}
Coordinates Field::GetOut() {
    return this->out;
}
void Field::MakeObjects(int chance) {
    int wall_appearance;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Coordinates any = {j, i};
            wall_appearance = rand() % 100 + 1;
            if ((wall_appearance <= chance) && (field[any.y][any.x].GetType() != IN) && (field[any.y][any.x].GetType() != OUT)) //10% chance
                field[any.y][any.x].SetType(NOPASS);
        }
    }
    notify(*this, __FUNCTION__);
}

void Field::MakeItems(int portals_count, int box_count, int heal_count) {
    for (int i = 0; i<portals_count; i++){
        teleports.first = {rand() % width, rand() % height};
        while (field[teleports.first.y][teleports.first.x].GetType() != PASSABLE)
            teleports.first = {rand() % width, rand() % height};
        teleports.second = {rand() % width, rand() % height};
        while (field[teleports.second.y][teleports.second.x].GetType() != PASSABLE)
            teleports.second = {rand() % width, rand() % height};
        field[teleports.first.y][teleports.first.x].SetObject(PORTAL);
        field[teleports.second.y][teleports.second.x].SetObject(PORTAL);
        field[teleports.first.y][teleports.first.x].SetObj(new Teleport(teleports));
        field[teleports.second.y][teleports.second.x].SetObj(new Teleport(teleports));
    }

    Coordinates treasure;
   treasure = {rand() % width, rand() % height};
    while (field[treasure.y][treasure.x].GetType() != PASSABLE || field[treasure.y][treasure.x].GetObject() != NONE)
        treasure = {rand() % width, rand() % height};
    field[treasure.y][treasure.x].SetObject(BOX);
    field[treasure.y][treasure.x].SetObj(new Box(true));

    for (int i = 0; i < box_count - 1; i++) {
        treasure = {rand() % width, rand() % height};
        while (field[treasure.y][treasure.x].GetType() != PASSABLE ||
               field[treasure.y][treasure.x].GetObject() != NONE)
            treasure = {rand() % width, rand() % height};
        field[treasure.y][treasure.x].SetObject(BOX);
       field[treasure.y][treasure.x].SetObj(new Box(false));
    }

    Coordinates healing;
    for (int i = 0; i < heal_count; i++) {
        healing = {rand() % width, rand() % height};
        while (field[healing.y][healing.x].GetType() != PASSABLE || field[healing.y][healing.x].GetObject() != NONE)
            healing = {rand() % width, rand() % height};
        field[healing.y][healing.x].SetObject(FOOD);
        field[healing.y][healing.x].SetObj(new Heal());
    }
    notify(*this, __FUNCTION__);
}
void Field::MakeEnemies(int countS, int countM, int countL) {
    Coordinates monster;
    int number_of_monsters;
    Enemy* enemy;
    const int monster_categories = 3;
    OBJECT whichone;
    for (int monster_creation_stage = 0; monster_creation_stage < monster_categories; monster_creation_stage++){
        switch (monster_creation_stage) {
            case 0 :{
                number_of_monsters = countS;
                whichone = SMALLMONSTER;
                enemy = new Smonster();
                break;
            }
            case 1:{
                number_of_monsters = countM;
                whichone = MEDIUMMONSTER;
                enemy = new Mmonster();
                break;
            }
            case 2:{
                number_of_monsters = countL;
                whichone = LARGEMONSTER;
                enemy = new Lmonster();
            }
                break;
        }
        for (int i=0; i < number_of_monsters; i++) {
            monster = {rand() % width, rand() % height};
            while (field[monster.y][monster.x].GetType() != PASSABLE || field[monster.y][monster.x].GetObject() != NONE)
                monster = {rand() % width, rand() % height};
            enemy->SetStep(START);
            Monsters[monstercount++] = {monster.x, monster.y};
            field[monster.y][monster.x].SetObject(whichone);
            field[monster.y][monster.x].SetObj(enemy);
        }
        }

    notify(*this, __FUNCTION__);
}

bool Field::Access(Coordinates state){
    if ((state.x >= 0) && (state.x < width) &&
        (state.y >= 0) && (state.y < height) &&
        (field[state.y][state.x].GetType() == PASSABLE) && (field[state.y][state.x].GetObject() == NONE))
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
void Field::SetMonsters(int k, Coordinates m) {
     Monsters[k].x = m.x;
    Monsters[k].y = m.y;
}
