#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Cell.h"

class Cellule: public Cell {
public:
    Cellule();
    Cellule(const Cellule& other);
    Cellule& operator = (const Cellule& other);
    Cellule(Cellule&& other);
    Cellule& operator=(Cellule&& other);
    TYPE GetType() final;
    void SetType(TYPE t) final;
    void SetPoint(int a, int b) final;
    Coordinates GetPoint() final;
    OBJECT GetObject() final;
    void SetObject(OBJECT t) final;
    bool GetKey() final;
    void SetKey(bool rich) final;
    GO GetStep() final;
    void SetStep(GO step) final;
    
private:
    Coordinates position{};
    TYPE type;
    OBJECT occupy;
    bool treasure;
    GO nextstep;
};
