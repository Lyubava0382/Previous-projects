
#include "Cellule.h"

Cellule::Cellule():position({0,0}), type(PASSABLE), occupy(NONE), nextstep(STOP), treasure(false)
{observable = false;
    observer = nullptr;
}

Cellule::Cellule(const Cellule& other) : position(other.position), type(other.type),
                                         occupy(other.occupy), nextstep(other.nextstep), treasure(other.treasure){ // Конструктор копирования
    observable = other.observable;
    observer = other.observer;
}

Cellule& Cellule::operator = (const Cellule& other) { // Оператор присваивания копированием
    if (this != &other){
        position = other.position;
        type = other.type;
        occupy = other.occupy;
        nextstep = other.nextstep;
        treasure = other.treasure;
        observable = other.observable;
        observer = other.observer;
    }
    return* this;
}

Cellule::Cellule(Cellule&& other) { // Конструктор перемещения
    std::swap(this->position, other.position);
    std::swap(this->type, other.type);
    std::swap(this->occupy, other.occupy);
    std::swap(this->nextstep, other.nextstep);
    std::swap(this->treasure, other.treasure);
    std::swap(this->observable, other.observable);
    std::swap(this->observer, other.observer);
}

Cellule& Cellule::operator=(Cellule&& other) { // Оператор присваивания перемещением
    if (this != &other) {
        std::swap(this->position, other.position);
        std::swap(this->type, other.type);
        std::swap(this->occupy, other.occupy);
        std::swap(this->nextstep, other.nextstep);
        std::swap(this->treasure, other.treasure);
        std::swap(this->observable, other.observable);
        std::swap(this->observer, other.observer);
    }
    return* this;
}

TYPE Cellule::GetType() {
    return this->type;
}

void Cellule::SetType(TYPE t) {
    this->type = t;
    notify(*this, __FUNCTION__);
}

void Cellule::SetPoint(int a, int b) {
    this->position.x = a;
    this->position.y = b;
    notify(*this, __FUNCTION__);
}
Coordinates Cellule::GetPoint() {
    return this->position;
}

OBJECT Cellule::GetObject() {
    return this->occupy;
}

void Cellule::SetObject(OBJECT t) {
    this->occupy = t;
    notify(*this, __FUNCTION__);
}
bool Cellule::GetKey() {
    return this->treasure;
}

void Cellule::SetKey(bool rich) {
    this->treasure = rich;
    notify(*this, __FUNCTION__);
}

GO Cellule::GetStep() {
    return this->nextstep;
}

void Cellule::SetStep(GO step) {
    this->nextstep = step;
    notify(*this, __FUNCTION__);
}

