
#ifndef UNTITLED6_INFO_H
#define UNTITLED6_INFO_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

enum TYPE{PASSABLE, NOPASS, IN, OUT};
enum OBJECT{NONE, FOOD, BOX, PORTAL, SMALLMONSTER, MEDIUMMONSTER, LARGEMONSTER};
enum GO{RIGHT, LEFT, UP, DOWN, STOP, START};

struct Coordinates{
    int x;
    int y;
};


#endif //UNTITLED6_INFO_H
