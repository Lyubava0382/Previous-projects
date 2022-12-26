//
// Created by Любава on 05.12.2021.
//

#ifndef UNTITLED6_GAMEVIEW_H
#define UNTITLED6_GAMEVIEW_H
#include "../../Info.h"

class GameView {
public:
    //explicit GameView();
    void PrintMenu(char command[]);
    void LeaveGame();
    void GameOver();
    void ReadInstruction();
    void ChangeUP();
    void ChangeDOWN();
    void ChangeRIGHT();
    void ChangeLEFT();
    void ChangingEnd();
    void GameLoading();
    void Save_Load_text();
};


#endif //UNTITLED6_GAMEVIEW_H
