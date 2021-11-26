//
// Created by Любава on 24.11.2021.
//

#ifndef UNTITLED6_CELLULE_H
#define UNTITLED6_CELLULE_H



#include "../Logging/IObservable.h"

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
    bool GetKey();
    void SetKey(bool rich);
    GO GetStep();
    void SetStep(GO step);
private:
    Coordinates position{};
    TYPE type;
    OBJECT occupy;
    bool treasure;
    GO nextstep;
};

#endif //UNTITLED6_CELLULE_H
