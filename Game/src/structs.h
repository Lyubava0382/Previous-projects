//
// Created by Serg on 10.10.2022.
//

#ifndef UNTITLED3_STRUCTS_H
#define UNTITLED3_STRUCTS_H
#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
enum TYPE{PASSABLE, NOPASS, IN, OUT};
enum OBJECT{NONE, BOX};
enum GO{RIGHT, LEFT, UP, DOWN, STOP, START};

struct Coordinates{
    int x;
    int y;
};

#endif //UNTITLED3_STRUCTS_H
