#include "Cellule.h"
    Cellule::Cellule():position({0,0}), type(PASSABLE){}

    TYPE Cellule::GetType() {
        return this->type;
    }

    void Cellule::SetType(TYPE t) {
        this->type = t;
    }

    void Cellule::SetPoint(int a, int b) {
        this->position.x = a;
        this->position.y = b;
    }
    Coordinates Cellule::GetPoint() {
        return this->position;
    }