#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "structs.h"
#include "Player.h"
#include "Field.h"
#include "Box.h"
#include "Heal.h"
#include "Teleport.h"
#include "Smonster.h"
#include "Mmonster.h"
#include "Lmonster.h"
#include "Game.h"

class Logger{
public:
    Logger();
    Logger(Player& adress);
    void update();
    void update(std::string namefunc, int a);
    void update(std::string namefunc, Coordinates a);
private:
    Player human;
    Smonster npc1;
};