//
// Created by Любава on 24.11.2021.
//

#ifndef UNTITLED6_ITEM_H
#define UNTITLED6_ITEM_H
#include "../../Empty.h"
#include "../../Interior.h"
#include "../Logging/IObservable.h"
#include "../Views/ItemView.h"

class Item: public Empty{
public:
    OBJECT GetObject();
    Item();
    void interplay(Player& person);
    bool remove();
protected:
    OBJECT type;
    bool removing;
};


#endif //UNTITLED6_ITEM_H
