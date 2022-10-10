#include "Box.h"
Box::Box(bool filled): full(filled), type(BOX){}

OBJECT Box::GetObject(){
    return this->type;
}
bool Box::GetOpen(){
    return this->open;
}