//
// Created by Любава on 12.11.2021.
//

#ifndef UNTITLED3_IOBSERVABLE_H
#define UNTITLED3_IOBSERVABLE_H
#include "Info.h"
class Logger;
class Player;
class Enemy;
class Cellule;
class Game;
class Field;
class Heal;
class Box;
class Teleport;

class IObservable {
public:
    void SetObservable(bool obs);
    void SetObserver(Logger* obs);
protected:
    bool observable;
    Logger* observer;
    void notify(std::string namefunc, Enemy &monster);
    void notify(std::string namefunc, Player &person);
    void notify(std::string namefunc, Cellule &cell);
    void notify(std::string namefunc, Field &fieldgame);
    void notify(std::string namefunc, Game &presentgame);
    void notify(std::string namefunc, Heal &food);
    void notify(std::string namefunc, Box &inbox);
    void notify(std::string namefunc, Teleport &teleports);
};

#endif //UNTITLED3_IOBSERVABLE_H
