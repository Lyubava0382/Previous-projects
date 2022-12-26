//
// Created by Любава on 13.11.2021.
//

#ifndef UNTITLED3_CELLULEVIEW_H
#define UNTITLED3_CELLULEVIEW_H
#include "Cellule.h"
#include "Player.h"
class CelluleView {
public:
    explicit CelluleView(Cellule& one, Player& someone);
    char GetView() const;
private:
    char view;
};


#endif //UNTITLED3_CELLULEVIEW_H
