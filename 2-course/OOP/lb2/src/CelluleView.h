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
