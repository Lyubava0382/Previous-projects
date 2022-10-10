//
// Created by Serg on 10.10.2022.
//

#ifndef UNTITLED3_FIELD_H
#define UNTITLED3_FIELD_H


#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Cellule.h"
class Field {
public:
    Field(int w = 10, int h = 10);
    ~Field();

    Field(const Field &other);

    Field& operator = (const Field &other);

    Field(Field&& other);

    Field& operator=(Field&& other);

    void MakeInOut();

    Coordinates GetIn();

    void MakeObjects();

    int MakeItems();

    bool Access(Coordinates presentstate);

    int GetHeight();

    int GetWidth();

    bool WithinField(Coordinates state);

    Cellule** GetField();


private:
    Cellule** field;
    int width;
    int height;
    Coordinates in{};
    Coordinates out{};
    double item_box,item_key,count_wall;
};



#endif //UNTITLED3_FIELD_H
