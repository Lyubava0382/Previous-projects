//
// Created by Serg on 10.10.2022.
//
#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Cell.h"
#ifndef UNTITLED3_CELLULE_H
#define UNTITLED3_CELLULE_H



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

private:
    Coordinates position{};
    TYPE type;
    OBJECT occupy;
    bool treasure;
    GO nextstep;
};



#endif //UNTITLED3_CELLULE_H
