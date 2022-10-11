
#include "Field.h"
#include <cmath>
Field::Field(int w, int h, double cnt_wll, double itm_k, double itm_b){
    width = w;
    height = h;
    field = new Cellule*[height];
    for (int i = 0; i < height; i ++){
        field[i] = new Cellule[width];
        for (int j = 0; j < width; j ++){
            field[i][j].SetPoint(j, i);
        }
    }
    count_wall = cnt_wll;
    item_key = itm_k;
    item_box = itm_b;

}
Field::~Field() {
    for (int i = 0; i < height; i ++) {
        delete[] field[i];
    }
    delete[] field;
}


bool Field::WithinField(Coordinates state){
    if ((state.x >= 0) && (state.x < width) &&
        (state.y >= 0) && (state.y < height)&&
        (field[state.y][state.x].GetType() != NOPASS))
        return true;
    else return false;
}

Field::Field(const Field &other) :  width(other.width), height(other.height),
                                    in(other.in), out(other.out),  field(new Cellule*[height]) { // Конструктор копирования
    for (int i = 0; i < height; i ++) {
        field[i] = new Cellule[width];
        for (int j = 0; j < width; j ++){
            field[i][j] = other.field[i][j];
        }
    }
}

Field & Field:: operator = (const Field &other) { // Оператор присваивания копированием
    if (this != &other){
        for (int i = 0; i < height; i ++){
            delete[] field[i];
        }
        delete[] field;
        width = other.width;
        height = other.height;
        in = other.in;
        out = other.out;
        field = new Cellule* [height];
        for (int i = 0; i < height; i ++) {
            field[i] = new Cellule[width];
            for (int j = 0; j < width; j ++){
                field[i][j] = other.field[i][j];
            }
        }
    }
    return *this;
}
Field & Field:: operator=(Field&& other) { // Оператор присваивания перемещением
    if (this != &other) {
        std::swap(this->width, other.width);
        std::swap(this->height, other.height);
        std::swap(this->in, other.in);
        std::swap(this->out, other.out);
        std::swap(this->field, other.field);
    }
    return *this;
}

void Field::MakeInOut() {
    in = {int(round(round(width/3)/2)), int(round(round(height/3)/2))};
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
            if ((chance <= count_wall) && (field[any.y][any.x].GetType() != IN) && (field[any.y][any.x].GetType() != OUT)) //10% chance
                field[any.y][any.x].SetType(NOPASS);
        }
    }
}
int Field::MakeItems() {
    int count = round(item_key * width * height);
   int number = round(item_box * width * height);
    Coordinates treasure;
    treasure = {rand() % width, rand() % height};
    for (int i = 0; i < count; i++){
        while (field[treasure.y][treasure.x].GetType() != PASSABLE || field[treasure.y][treasure.x].GetObject() != NONE)
            treasure = {rand() % width, rand() % height};
        field[treasure.y][treasure.x].SetObject(BOX);
        field[treasure.y][treasure.x].SetKey(true);
    }
    for (int i = 0; i < number - count; i++) {
        treasure = {rand() % width, rand() % height};
        while (field[treasure.y][treasure.x].GetType() != PASSABLE ||
               field[treasure.y][treasure.x].GetObject() != NONE)
            treasure = {rand() % width, rand() % height};
        field[treasure.y][treasure.x].SetKey(false);
        field[treasure.y][treasure.x].SetObject(BOX);
    }
    return count;
}


int Field::GetHeight() {
    return this->height;
}

int Field::GetWidth() {
    return this->width;
}
Cellule** Field::GetField() {
    return this->field;
}
