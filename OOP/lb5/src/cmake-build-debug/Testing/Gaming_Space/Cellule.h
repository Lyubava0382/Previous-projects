//
// Created by Любава on 24.11.2021.
//

#ifndef UNTITLED6_CELLULE_H
#define UNTITLED6_CELLULE_H


#include "../../Empty.h"
#include "../Logging/IObservable.h"
#include "../Static_Items/Item.h"
#include "../Moving_objects/Enemy.h"

class Cellule: public IObservable{
public:
    Cellule();
    Cellule(const Cellule& other);
    Cellule& operator = (const Cellule& other);
    Cellule(Cellule&& other);
    Cellule& operator=(Cellule&& other);
    TYPE GetType();
    void SetType(TYPE t);
    void SetPoint(int a, int b);
    Coordinates GetPoint();
    OBJECT GetObject();
    void SetObject(OBJECT t);
    Interior*& GetObj();
    void SetObj(Interior* Entity);
    ~Cellule();
private:
    Coordinates position{};
    TYPE type;
    OBJECT occupy;
    Interior* object;

};

#endif //UNTITLED6_CELLULE_H
