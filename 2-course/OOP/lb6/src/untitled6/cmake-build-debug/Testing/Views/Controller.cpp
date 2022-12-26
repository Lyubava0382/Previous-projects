//
// Created by Любава on 19.12.2021.
//

#include "Controller.h"

Controller::Controller(){
    command[0] = 'w';
    command[1] = 'a';
    command[2] = 's';
    command[3] = 'd';
    command[4] = 'x';
    command[5] = 'm';
    command[6] = '?';
    command[7] = 'k';
    command[8] = 'v';
    command[9] = 'l';
    going = true;
}

GO Controller::GameInput(){
    char one_command = '0';
    std::cin >> one_command;
    GameView print;
    print = GameView();
    int index = 0;
    if (one_command == command[index++]){
        return UP;
    }
    else if (one_command == command[index++]){
        return LEFT;
    }
    else if (one_command == command[index++]){
        return DOWN;
    }
    else if (one_command == command[index++]){
        return RIGHT;
    }
    else if (one_command == command[index++]){
        print.LeaveGame();
        going = false;
        return STOP;
    }
    else if (one_command == command[index++]){
        print.PrintMenu(command);
        return GameInput();
    }
    else if (one_command == command[index++]){
        print.ReadInstruction();
        return GameInput();
    }
    else if (one_command == command[index++]){
        ChangeControlKeys();
        return GameInput();
    }
    else if (one_command == command[index++]){
        return SAVE;
    }
    else if (one_command == command[index++]){
        return LOAD;
    }
    else return START;
}
void Controller::ChangeControlKeys(){
    GameView print;
    print = GameView();

    print.ChangeUP();
    std::cin >> command[0];

    print.ChangeRIGHT();
    std::cin >> command[3];

    print.ChangeDOWN();
    std::cin >> command[2];

    print.ChangeLEFT();
    std::cin >> command[1];
    print.ChangingEnd();
}

bool Controller::Goon(){
    return this->going;
}
void Controller::Menu(){
    GameView().PrintMenu(command);
}
