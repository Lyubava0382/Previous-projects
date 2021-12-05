//
// Created by Любава on 24.11.2021.
//

#ifndef UNTITLED6_FIGHTVIEW_H
#define UNTITLED6_FIGHTVIEW_H



#include "../../Info.h"

class fightView{
public:
    explicit fightView(OBJECT monster_size, int hero_health, int monster_health);
    char GetWound() const;
private:
    char wound;
};


#endif //UNTITLED6_FIGHTVIEW_H
