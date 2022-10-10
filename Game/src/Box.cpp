#include "Box.h"
Box::Box(bool filled): full(filled), type(BOX){}

void Box::interplay(Player& person){
    if (full){
        person.Key();
    }
    else {
        std::cout << "Oops! .. It's empty." << std::endl;
    }
}

OBJECT Box::GetObject(){
    return this->type;
}
bool Box::GetOpen(){
    return this->open;
}