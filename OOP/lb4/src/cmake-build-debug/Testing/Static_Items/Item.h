//
// Created by Любава on 24.11.2021.
//

#ifndef UNTITLED6_ITEM_H
#define UNTITLED6_ITEM_H
#include "../../Interior.h"
#include "../Logging/IObservable.h"

class Item: Interior, public IObservable{
public:
    OBJECT GetObject();
protected:
    OBJECT type;
};


#endif //UNTITLED6_ITEM_H
