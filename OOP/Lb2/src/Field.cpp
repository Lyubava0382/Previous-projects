#include "Field.h"
#include <cmath>
     Field::Field(int w = 10, int h = 10){
        width = w;
        height = h;
        monstercount = 0;
        field = new Cellule*[height];
        for (int i = 0; i < height; i ++){
            field[i] = new Cellule[width];
            for (int j = 0; j < width; j ++){
                field[i][j].SetPoint(j, i);
            }
        }
        Monsters = new Coordinates[10];
    }
    Field::~Field() {
        for (int i = 0; i < height; i ++) {
            delete[] field[i];
        }
        delete[] field;
        delete[] Monsters;
    }


    Field::Field(const Field &other) :  width(other.width), height(other.height),
                                in(other.in), out(other.out), Monsters(new Coordinates[monstercount]), monstercount(other.monstercount), field(new Cellule*[height]) { // Конструктор копирования
        for (int i = 0; i < height; i ++) {
            field[i] = new Cellule[width];
            for (int j = 0; j < width; j ++){
                field[i][j] = other.field[i][j];
            }
        }
        for (int k = 0; k < monstercount; k ++){
            Monsters[k] = other.Monsters[k];
        }
    }

     Field & Field:: operator = (const Field &other) { // Оператор присваивания копированием
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
            monstercount = other.monstercount;
            field = new Cellule* [height];
            for (int i = 0; i < height; i ++) {
                field[i] = new Cellule[width];
                for (int j = 0; j < width; j ++){
                    field[i][j] = other.field[i][j];
                }
            }
            Monsters = new Coordinates[monstercount];
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
    }

    Field & Field:: operator=(Field&& other) { // Оператор присваивания перемещением
        if (this != &other) {
            std::swap(this->width, other.width);
            std::swap(this->height, other.height);
            std::swap(this->in, other.in);
            std::swap(this->out, other.out);
            std::swap(this->Monsters, other.Monsters);
            std::swap(this->monstercount, other.monstercount);
            std::swap(this->field, other.field);
        }
        return *this;
    }
    
    void Field::MakeInOut() {
        in = {rand() % width, rand() % height};
        field[in.y][in.x].SetType(IN);
        out = {rand() % width, rand() % height};
        while (abs(out.x - in.x) < round(0.2* width) || abs(out.y - in.y) < round(0.2* height) ){

            out = {rand() % width, rand() % height};
        }
        field[out.y][out.x].SetType(OUT);
    }

    Coordinates Field::GetIn() {
        return this->in;
    }

    void Field::MakeObjects() {
        int chance;
        for (int i = 0; i < height; i ++) {
            for (int j = 0; j < width; j ++) {
                Coordinates any = {j, i};
                chance = rand() % 100 + 1;
                if ((chance <= 10) && (field[any.y][any.x].GetType() != IN) && (field[any.y][any.x].GetType() != OUT)) //10% chance
                    field[any.y][any.x].SetType(NOPASS);
            }
        }
    }
void Field::MakeItems() {
        teleports[0] = {rand() % width, rand() % height};
        while (field[teleports[0].y][teleports[0].x].GetType() != PASSABLE)
            teleports[0] = {rand() % width, rand() % height};
        teleports[1] = {rand() % width, rand() % height};
        while (field[teleports[1].y][teleports[1].x].GetType() != PASSABLE)
            teleports[1] = {rand() % width, rand() % height};

        field[teleports[0].y][teleports[0].x].SetObject(PORTAL);
        field[teleports[1].y][teleports[1].x].SetObject(PORTAL);

        int number = round(0.02 * width * height);
        Coordinates treasure;
        treasure = {rand() % width, rand() % height};
        while (field[treasure.y][treasure.x].GetType() != PASSABLE || field[treasure.y][treasure.x].GetObject() != NONE)
            treasure = {rand() % width, rand() % height};
        field[treasure.y][treasure.x].SetObject(BOX);
        field[treasure.y][treasure.x].SetKey(true);
        for (int i = 0; i < number - 1; i++) {
            treasure = {rand() % width, rand() % height};
            while (field[treasure.y][treasure.x].GetType() != PASSABLE ||
                   field[treasure.y][treasure.x].GetObject() != NONE)
                treasure = {rand() % width, rand() % height};
            field[treasure.y][treasure.x].SetKey(false);
            field[treasure.y][treasure.x].SetObject(BOX);
        }
        Coordinates healing;
        for (int i = 0; i < number; i++) {
            healing = {rand() % width, rand() % height};
            while (field[healing.y][healing.x].GetType() != PASSABLE || field[healing.y][healing.x].GetObject() != NONE)
                healing = {rand() % width, rand() % height};
            field[healing.y][healing.x].SetObject(FOOD);
        }

    }
    void Field::MakeEnemies() {
        Coordinates monster;
        int number;
        OBJECT whichone;
        for (int j = 0; j < 3; j++){
            switch (j) {
                case 0 :
                    number = round(0.02 * width * height);
                    whichone = SMALLMONSTER;
                    break;
                case 1:
                    number = round(0.01 * width * height);
                    whichone = MEDIUMMONSTER;
                    break;
                case 2:
                    number = 1;
                    whichone = LARGEMONSTER;
                    break;
            }
            for (int i=0; i < number; i++) {
                monster = {rand() % width, rand() % height};
                while (field[monster.y][monster.x].GetType() != PASSABLE || field[monster.y][monster.x].GetObject() != NONE)
                    monster = {rand() % width, rand() % height};
                field[monster.y][monster.x].SetStep(START);
                Monsters[monstercount++] = {monster.x, monster.y};
                field[monster.y][monster.x].SetObject(whichone);
            }
        }
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

    Coordinates* Field::GetTeleports() {
        return this->teleports;
    }

    Coordinates* Field::GetMonsters() {
        return this->Monsters;
    }
