
#include "IObservable.h"
#include "Logger.h"
void IObservable::SetObservable(bool obs){
    this->observable = obs;
}

void IObservable::SetObserver(Logger* obs){
    this->observer = obs;
}
void IObservable::notify(std::string namefunc, Player &person) {
    if (this->observable && this->observer != NULL){
        this->observer->update(namefunc, person);
    }
}
void IObservable::notify(std::string namefunc, Enemy &monster) {
    if (this->observable && this->observer != NULL){
        this->observer->update(namefunc, monster);
    }
}
void IObservable::notify(std::string namefunc, Cellule &cell){
    if (this->observable && this->observer != NULL){
        this->observer->update(namefunc, cell);
    }
}

void IObservable::notify(std::string namefunc, Field &fieldgame) {
    if (this->observable && this->observer != NULL) {
        this->observer->update(namefunc, fieldgame);
    }
}
void IObservable::notify(std::string namefunc, Game &presentgame) {
    if (this->observable && this->observer != NULL){
        this->observer->update(namefunc, presentgame);
    }
}
void IObservable::notify(std::string namefunc, Heal &food) {
    if (this->observable && this->observer != NULL){
        this->observer->update(namefunc, food);
    }
}
void IObservable::notify(std::string namefunc, Box &inbox){
    if (this->observable && this->observer != NULL){
        this->observer->update(namefunc, inbox);
    }
}
void IObservable::notify(std::string namefunc, Teleport &teleports){
    if (this->observable && this->observer != NULL){
        this->observer->update(namefunc, teleports);
    }
}