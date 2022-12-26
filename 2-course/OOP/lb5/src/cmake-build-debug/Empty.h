//
// Created by Любава on 04.12.2021.
//

#ifndef UNTITLED6_EMPTY_H
#define UNTITLED6_EMPTY_H
#include "Interior.h"
#include "./Testing/Logging/IObservable.h"

class Empty: public Interior,  public IObservable {
public:
    OBJECT GetObject();
protected:
    OBJECT type;
};


#endif //UNTITLED6_EMPTY_H
