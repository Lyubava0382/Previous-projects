//
// Created by Serg on 10.10.2022.
//

#ifndef UNTITLED3_CELLULEVIEW_H
#define UNTITLED3_CELLULEVIEW_H

#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Cell.h"
#include "Cellule.h"
#include "Player.h"


class CelluleView {
public:
    explicit CelluleView(Cellule& one, Player& someone);
    char GetView() const;
    virtual ~CelluleView();
private:
    char view;
};


#endif //UNTITLED3_CELLULEVIEW_H
