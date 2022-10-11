//
// Created by Serg on 10.10.2022.
//

#ifndef UNTITLED3_GAMEVIEW_H
#define UNTITLED3_GAMEVIEW_H


//
// Created by Любава on 05.12.2021.
//

#ifndef UNTITLED6_GAMEVIEW_H
#define UNTITLED6_GAMEVIEW_H
#include "structs.h"

class GameView {
public:
    explicit GameView();
    void PrintMenu();
    Coordinates GameInput();
    bool Goon();
    void LeaveGame();
    void ReadInstruction();
    void GameOver(double sec);
    void NeedKey();
    void Key(bool key);
private:
    char right;
    char left;
    char up;
    char down;
    bool going;
    char exit;
    char menu;
    char instruction;
    char records;
};


#endif //UNTITLED6_GAMEVIEW_H



#endif //UNTITLED3_GAMEVIEW_H
