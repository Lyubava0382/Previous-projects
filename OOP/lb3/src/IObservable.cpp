#include "IObservable.h"

void IObservable::SetObservable(bool obs){
        this->observable = obs;
    }

    void IObservable::SetObserver(Logger* obs){
        this->observer = obs;
    }

void IObservable::notify() {
    std::cout << "notify!" << std::endl;
    if (this->observable && this->observer != NULL){
        this->observer->update();
    }
}

void IObservable::notify(std::string namefunc, int a) {
    if (this->observable && this->observer != NULL){
        this->observer->update(namefunc, a);
    }
}

void IObservable::notify(std::string namefunc, Coordinates a) {
    if (this->observable && this->observer != NULL){
        this->observer->update(namefunc, a);
    }
}