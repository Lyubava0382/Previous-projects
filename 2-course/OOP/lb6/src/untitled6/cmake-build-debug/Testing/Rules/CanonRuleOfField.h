//
// Created by Любава on 26.11.2021.
//

#ifndef UNTITLED6_CANONRULEOFFIELD_H
#define UNTITLED6_CANONRULEOFFIELD_H
#include "RuleOfFieldInterface.h"


template <int height, int width, int advent_of_wall_chance>
class CanonRuleOfField: RuleOfFieldInterface {
public:
    CanonRuleOfField(){}
    int GetHeight() final {
        return height;
    }

    int GetWidth() final {
        return width;
    }
    int GetSize() final {
        return height*width;
    }
    int GetWallChance() final {
        return advent_of_wall_chance;
    }
};


#endif //UNTITLED6_CANONRULEOFFIELD_H
