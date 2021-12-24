
#include "Item.h"
#include "Box.h"
#include "Teleport.h"
#include "Heal.h"
Item::Item(){
    removing = true;
}
OBJECT Item::GetObject() {
    return this->type;
}
void Item::interplay(Player& person){
    if (dynamic_cast<Box*>(this)) {
        dynamic_cast<Box*>(this)->interplay(person);
    }
    else if (dynamic_cast<Heal*>(this)){
        dynamic_cast<Heal*>(this)->interplay(person);
    }
    else if (dynamic_cast<Teleport*>(this)){
        dynamic_cast<Teleport*>(this)->interplay(person);
    }
}
bool Item::remove(){
    return removing;
};