#include "Teleport.h"
    Teleport::Teleport(std::pair <Coordinates, Coordinates> points): firstplace(points.first), secondplace(points.second){
        type = PORTAL;
    }

    void Teleport::interplay(Player& person){
        if (person.GetLocal().x == firstplace.x && person.GetLocal().y == firstplace.y)
            person.SetLocal(secondplace);
        else person.SetLocal(firstplace);
        notify();
    }