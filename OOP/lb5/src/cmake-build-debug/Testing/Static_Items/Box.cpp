
#include "Box.h"
Box::Box(bool filled): full(filled){
    type = BOX;
    observable = false;
    observer = nullptr;
    removing = false;
}

void Box::interplay(Player& person){
    if (person.GetCoins() > 0) {
        removing = true;
        if (full){
            person.SetKey(true);
            person.SetCoins(-1);
        }
    }

    ItemView().BoxPrint(removing,full);
    notify(*this, __FUNCTION__);
}
bool Box::GetFull(){
    return this->full;
}
