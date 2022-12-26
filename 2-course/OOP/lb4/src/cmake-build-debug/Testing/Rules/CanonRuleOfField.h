//
// Created by Любава on 26.11.2021.
//

#ifndef UNTITLED6_CANONRULEOFFIELD_H
#define UNTITLED6_CANONRULEOFFIELD_H
#include "RuleOfFieldInterface.h"


template <int h, int w, int chance>
class CanonRuleOfField: RuleOfFieldInterface {
public:
    CanonRuleOfField(){
        height = h;
        width = w;
        advent_of_wall_chance = chance;
    }
    int GetHeight() final {
        return this->height;
    }

    int GetWidth() final {
        return this->width;
    }
    int GetSize() final {
        return this->height*width;
    }
    int GetWallChance() final {
        return this->advent_of_wall_chance;
    }
private:
    int height;
    int width;
    int advent_of_wall_chance;
};


#endif //UNTITLED6_CANONRULEOFFIELD_H
