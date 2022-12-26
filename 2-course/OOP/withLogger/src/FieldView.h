//
// Created by Любава on 13.11.2021.
//

#ifndef UNTITLED3_FIELDVIEW_H
#define UNTITLED3_FIELDVIEW_H
#include "Field.h"
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


#endif //UNTITLED3_FIELDVIEW_H
