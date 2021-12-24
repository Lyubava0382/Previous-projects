//
// Created by Любава on 24.11.2021.
//

#ifndef UNTITLED6_FIELDVIEW_H
#define UNTITLED6_FIELDVIEW_H


#include "../Gaming_Space/Field.h"
#include "CelluleView.h"

class FieldView {
public:
    explicit FieldView(Field& one, Player& character);
    void Print() const;
    void PrintBorder() const;
private:
    Field& GameField;
    Player& hero;
};



#endif //UNTITLED6_FIELDVIEW_H
