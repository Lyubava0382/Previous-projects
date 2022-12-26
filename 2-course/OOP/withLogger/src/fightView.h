//
// Created by Любава on 12.11.2021.
//

#ifndef UNTITLED3_FIGHTVIEW_H
#define UNTITLED3_FIGHTVIEW_H
#include "Info.h"

class fightView{
public:
    explicit fightView(OBJECT monster_size, int hero_health, int monster_health);
    char GetWound() const;
private:
    char wound;
};


#endif //UNTITLED3_FIGHTVIEW_H
