#include "Teleport.h"
    Teleport::Teleport(Coordinates points[2]): firstplace(points[0]), secondplace(points[1]), type(PORTAL){}

    void Teleport::interplay(Player& person){
        if (person.GetLocal().x == firstplace.x && person.GetLocal().y == firstplace.y)
            person.SetLocal(secondplace);
        else person.SetLocal(firstplace);
    }

    OBJECT Teleport::GetObject(){
        return this->type;
    }

