//
// Created by Любава on 21.12.2021.
//

#include "Except4Game.h"


Except4Game::Except4Game(ERROR tp):type(tp){
    switch (this->type){
        case FILE_ERROR:
            message ="Error: problem with file";
            break;
        case BORDER_ERROR:
            message ="You are out of bounds";
            break;
        default:
            message ="Unrecognized error. Please try again later";
    }
}

std::string Except4Game::GetMessage(){
    return message;
}
