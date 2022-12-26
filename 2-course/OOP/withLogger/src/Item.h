//
// Created by Любава on 12.11.2021.
//

#ifndef UNTITLED3_ITEM_H
#define UNTITLED3_ITEM_H
#include "Interior.h"
#include "IObservable.h"

class Item: Interior, public IObservable{
public:
    OBJECT GetObject();
protected:
    OBJECT type;
};


#endif //UNTITLED3_ITEM_H
