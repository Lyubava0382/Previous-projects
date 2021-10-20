#include "Box.h"
    Box::Box(bool filled): full(filled), type(BOX){}

    void Box::interplay(Player& person){
        if (full && person.GetCoins() > 0){
            person.SetKey(true);
            person.SetCoins(-1);
        }
    }

    OBJECT Box::GetObject(){
        return this->type;
    }

