#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Cellule.h"
#include "CelluleView.h"
class Field {
public:
    explicit Field(int w = 10, int h = 10);
    ~Field();
    Field(const Field &other);
    Field& operator = (const Field &other);
    Field(Field&& other);
    Field& operator=(Field&& other);
    void MakeInOut();
    Coordinates GetIn();
    void MakeObjects();
    void PrintBorder() const;
    void Print() const;
    void Start();

private:
    Cellule** field;
    int width;
    int height;
    Coordinates in{};
    Coordinates out{};
};
