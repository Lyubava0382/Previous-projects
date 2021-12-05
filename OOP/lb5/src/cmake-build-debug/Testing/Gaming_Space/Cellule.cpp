
#include "Cellule.h"

Cellule::Cellule():position({0,0}), type(PASSABLE), occupy(NONE)
{observable = false;
    observer = nullptr;
    object = new Empty;
}

Cellule::Cellule(const Cellule& other) : position(other.position), type(other.type),
                                         occupy(other.occupy){ // Конструктор копирования
    observable = other.observable;
    observer = other.observer;
    object = other.object;
}

Cellule& Cellule::operator = (const Cellule& other) { // Оператор присваивания копированием
    if (this != &other){
        position = other.position;
        type = other.type;
        occupy = other.occupy;
        observable = other.observable;
        observer = other.observer;
       object = other.object;
    }
    return* this;
}

Cellule::Cellule(Cellule&& other) { // Конструктор перемещения
    std::swap(this->position, other.position);
    std::swap(this->type, other.type);
    std::swap(this->occupy, other.occupy);
    std::swap(this->observable, other.observable);
    std::swap(this->observer, other.observer);
    std::swap(this->object, other.object);
}

Cellule& Cellule::operator=(Cellule&& other) { // Оператор присваивания перемещением
    if (this != &other) {
        std::swap(this->position, other.position);
        std::swap(this->type, other.type);
        std::swap(this->occupy, other.occupy);
        std::swap(this->observable, other.observable);
        std::swap(this->observer, other.observer);
        std::swap(this->object, other.object);
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


void Cellule::SetObj(Interior* t){
    this->object = t;
}


Interior *& Cellule::GetObj(){
    return this->object;
}
Cellule::~Cellule(){
};