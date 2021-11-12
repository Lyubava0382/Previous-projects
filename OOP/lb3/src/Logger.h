//
// Created by Любава on 12.11.2021.
//

#ifndef UNTITLED3_LOGGER_H
#define UNTITLED3_LOGGER_H
#pragma once
#include "Game.h"
#include "Enemy.h"
#include "Heal.h"
#include "Box.h"
#include "Teleport.h"
class IObservable;

class Logger {
public:
    Logger(IObservable& address);
    ~Logger();
    void update(std::string namefunc, Player &person);
    void update(std::string namefunc, Enemy &monster);
    void update(std::string namefunc, Cellule &cell);
    void update(std::string namefunc, Field &fieldgame);
    void update(std::string namefunc, Game &presentgame);
    void update(std::string namefunc, Heal &food);
    void update(std::string namefunc, Box &inbox);
    void update(std::string namefunc, Teleport &teleports);
private:
    friend std::ostream& operator<< (std::ostream &out, const Player &person);
    friend std::ostream& operator<< (std::ostream &out, const Enemy &monster);
    friend std::ostream& operator<< (std::ostream &out, const Cellule &cell);
    friend std::ostream& operator<< (std::ostream &out, const Field &fieldgame);
    friend std::ostream& operator<< (std::ostream &out, const Game &presentgame);
    friend std::ostream& operator<< (std::ostream &out, const Heal &food);
    friend std::ostream& operator<< (std::ostream &out, const Box &inbox);
    friend std::ostream& operator<< (std::ostream &out, const Teleport &teleports);
    std::pair <bool,bool> streams;
    std::ofstream outfile;

    void File_Settings();
};

#endif //UNTITLED3_LOGGER_H
