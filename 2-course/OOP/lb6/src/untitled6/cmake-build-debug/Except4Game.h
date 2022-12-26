//
// Created by Любава on 21.12.2021.
//

#ifndef UNTITLED6_EXCEPT4GAME_H
#define UNTITLED6_EXCEPT4GAME_H
#include "./Info.h"

class Except4Game {
public:
    Except4Game(ERROR tp);
    std::string GetMessage();
private:
    ERROR type;
    std::string message;
};


#endif //UNTITLED6_EXCEPT4GAME_H
