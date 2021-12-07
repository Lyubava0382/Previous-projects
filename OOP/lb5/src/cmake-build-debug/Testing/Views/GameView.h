//
// Created by Любава on 05.12.2021.
//

#ifndef UNTITLED6_GAMEVIEW_H
#define UNTITLED6_GAMEVIEW_H
#include "../../Info.h"

class GameView {
public:
    explicit GameView();
    void PrintMenu();
    Coordinates GameInput();
    void ChangeControlKeys();
    bool Goon();
    void LeaveGame();
    void GameOver();
    void ReadInstruction();
private:
    char right;
    char left;
    char up;
    char down;
    bool going;
    const char * exit = "x";
    const char * menu = "m";
    const char * instruction = "?";
    const char * change_keys = "k";
};


#endif //UNTITLED6_GAMEVIEW_H
