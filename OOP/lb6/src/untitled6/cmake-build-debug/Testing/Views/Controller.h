//
// Created by Любава on 19.12.2021.
//

#ifndef UNTITLED6_CONTROLLER_H
#define UNTITLED6_CONTROLLER_H
#include "../../Info.h"
#include "GameView.h"

class Controller {
public:
    Controller();
    GO GameInput();
    bool Goon();
    void ChangeControlKeys();
    void Menu();
private:
    bool going;
    char command[30];
};


#endif //UNTITLED6_CONTROLLER_H
