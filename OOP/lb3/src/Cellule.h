//
// Created by Любава on 13.11.2021.
//

#ifndef UNTITLED3_CELLULE_H
#define UNTITLED3_CELLULE_H
#include "IObservable.h"

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


#endif //UNTITLED3_CELLULE_H
