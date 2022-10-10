//
// Created by Serg on 10.10.2022.
//

#ifndef UNTITLED3_FIELDVIEW_H
#define UNTITLED3_FIELDVIEW_H


#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "CelluleView.h"
#include "Field.h"

class FieldView {
public:
    explicit FieldView(Field& one, Player& character);

    void PrintBorder() const;

    void Print() const;

    virtual ~FieldView();
private:
    Field& GameField;
    Player& hero;
};



#endif //UNTITLED3_FIELDVIEW_H
