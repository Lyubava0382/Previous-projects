
#include "Box.h"
Box::Box(bool filled): full(filled){
    type = BOX;
    observable = false;
    observer = nullptr;
    removing = false;
}

void Box::interplay(Player& person){
    if (full && person.GetCoins() > 0){
        person.SetKey(true);
        person.SetCoins(-1);
        removing = true;
    }
    ItemView().BoxPrint(removing,full);
    notify(*this, __FUNCTION__);
}
bool Box::GetFull(){
    return this->full;
}
