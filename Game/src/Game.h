//
// Created by Serg on 10.10.2022.
//

#ifndef UNTITLED3_GAME_H
#define UNTITLED3_GAME_H
#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "time.h"
#include "structs.h"
#include "Player.h"
#include "Field.h"
#include "FieldView.h"
#include "GameView.h"
class Game {
public:
    explicit Game();
    void Start(Field& game);
    void Over(bool breakEnd);
    bool GameMove(Coordinates motion);
private:
    Field game;
    Player person;
    GameView game_interface;
    bool game_end;
    time_t start;
    time_t end;
    double timeout;
};

#endif //UNTITLED3_GAME_H
