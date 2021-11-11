#include "Logger.h"

    Logger::Logger() {};
    Logger::Logger(Player& adress) {
        adress.SetObservable(true);
        adress.SetObserver(this);
    }
    void Logger::update(){
        std::cout << "Print!" << std::endl;
    }
    void Logger::update(std::string namefunc, int a){
        std::cout << namefunc << "  " << a << std::endl;
    }
    void Logger::update(std::string namefunc, Coordinates a){
        std::cout << namefunc << "  x = " << a.x << "  y = " << a.y << std::endl;
    }