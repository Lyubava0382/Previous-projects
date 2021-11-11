#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "structs.h"
#include "Logger.h"

class IObservable{
public:
    void notify();
    void notify(std::string namefunc, int a);
    void notify(std::string namefunc, Coordinates a);
    void SetObservable(bool obs);
    void SetObserver(Logger* obs);
protected:
    bool observable;
    Logger* observer;
};