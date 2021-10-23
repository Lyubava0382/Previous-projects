#include "Box.h"
    Box::Box(bool filled): full(filled), type(BOX){}

    void Box::interplay(Player& person){
        if (full && person.GetCoins() > 0){
            person.SetKey(true);
            person.SetCoins(-1);
            open = true;
        }
        else {
            std::cout << "Oops! .. Not enough coins." << std::endl;
            std::cout << "Please get the money and come back." << std::endl;
        }
    }

    OBJECT Box::GetObject(){
        return this->type;
    }
    bool Box::GetOpen(){
        return this->open;
    }