//
// Created by Любава on 12.11.2021.
//

#include "Box.h"
    Box::Box(bool filled): full(filled){
        type = BOX;
        observable = false;
        observer = nullptr;
    }

    void Box::interplay(Player& person){
        if (full && person.GetCoins() > 0){
            person.SetKey(true);
            person.SetCoins(-1);
        }
        notify(__FUNCTION__, *this);
    }
    bool Box::GetFull(){
        return this->full;
    }
