

#include "Teleport.h"
Teleport::Teleport(std::pair <Coordinates, Coordinates> points): firstplace(points.first), secondplace(points.second){
    type = PORTAL;
    observable = false;
    observer = nullptr;
}

void Teleport::interplay(Player& person) {
    if (person.GetLocal().x == firstplace.x && person.GetLocal().y == firstplace.y)
        person.SetLocal(secondplace);
    else person.SetLocal(firstplace);
    notify(*this, __FUNCTION__);
}
Coordinates Teleport::GetFirstPlace(){
    return firstplace;
}
Coordinates Teleport::GetSecondPlace(){
    return secondplace;
}
