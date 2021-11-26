
#ifndef UNTITLED6_IOBSERVABLE_H
#define UNTITLED6_IOBSERVABLE_H

#pragma once
#include "../../Info.h"
#include "Logger.h"
class Logger;
class Player;
class Enemy;
class Cellule;
//class Game;
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
    template<class T>
    void notify(T &observable_object, std::string namefunc);
};

template<typename T>
void IObservable::notify(T &observable_object, std::string namefunc) {
    if (this->observable && this->observer != nullptr){
        this->observer->update(observable_object, namefunc); //Не даёт работать с этим указателем, с полями объекта
    }
}

#endif //UNTITLED6_IOBSERVABLE_H
