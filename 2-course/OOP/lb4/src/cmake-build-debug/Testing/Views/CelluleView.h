//
// Created by Любава on 24.11.2021.
//

#ifndef UNTITLED6_CELLULEVIEW_H
#define UNTITLED6_CELLULEVIEW_H


#include "../Gaming_Space/Cellule.h"
#include "../Moving_objects/Player.h"
class CelluleView {
public:
    explicit CelluleView(Cellule& one, Player& someone);
    char GetView() const;
private:
    char view;
};



#endif //UNTITLED6_CELLULEVIEW_H
