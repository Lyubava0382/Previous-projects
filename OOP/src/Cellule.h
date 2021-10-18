#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Cell.h"

class Cellule: public Cell {
public:
    Cellule();
    TYPE GetType() final;
    void SetType(TYPE t) final;
    void SetPoint(int a, int b) final;
    Coordinates GetPoint() final;
private:
    Coordinates position{};
    TYPE type;
};
