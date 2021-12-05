//
// Created by Ыўсртр on 24.11.2021.
//

#ifndef UNTITLED6_LOGGER_H
#define UNTITLED6_LOGGER_H

/*
#pragma once
#include "Cellule.h"
#include "Field.h"
#include "Game.h"
#include "Enemy.h"
#include "Heal.h"
#include "Box.h"
#include "Teleport.h"
#include "LoggerView.h"
 */
#pragma once
#include "../../Info.h"
class Logger;
class Player;
class Enemy;
class Cellule;
//class Game;
class Field;
class Heal;
class Box;
class Teleport;
class IObservable;

class Logger {
public:
    Logger(IObservable& address);
    ~Logger();

    void update(Box &inbox,std::string namefunc);
    void update(Cellule &cell,std::string namefunc);
    void update(Enemy &monster,std::string namefunc);
    void update(Field &fieldgame,std::string namefunc);
    void update(Heal &food,std::string namefunc);
    void update(Player &person,std::string namefunc);
    void update(Teleport &teleports,std::string namefunc);

    template<class S>
    void update(S &observable_object, std::string namefunc);
private:
    friend std::ostream& operator<< (std::ostream &out, Player &person);
    friend std::ostream& operator<< (std::ostream &out, Enemy &monster);
    friend std::ostream& operator<< (std::ostream &out, Cellule &cell);
    friend std::ostream& operator<< (std::ostream &out, Field &fieldgame);
    friend std::ostream& operator<< (std::ostream &out, Heal &food);
    friend std::ostream& operator<< (std::ostream &out, Box &inbox);
    friend std::ostream& operator<< (std::ostream &out, Teleport &teleports);
    std::pair <bool,bool> streams;
    std::ofstream outfile;
    void File_Settings();
};

template<typename S>
void Logger::update(S &observable_object, std::string namefunc){
    if (streams.first) {
        std::cout << namefunc << ":\n";
        std::cout << observable_object;
    }
    if (streams.second){
        outfile << namefunc << ":\n";
        outfile << observable_object;
    }
}


#endif //UNTITLED6_LOGGER_H
