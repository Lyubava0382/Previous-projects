//
// Created by Любава on 26.11.2021.
//

#ifndef UNTITLED6_CANONNUMBEROFENEMIES_H
#define UNTITLED6_CANONNUMBEROFENEMIES_H



#include "NumberOfEnemiesInterface.h"

template <int s, int m, int l>
class CanonNumberOfEnemies: NumberOfEnemiesInterface {
public:
    CanonNumberOfEnemies(int size_of_field = 150){
        double proportion_monsters_on_field = 0.01;
        number_of_s = round(size_of_field * proportion_monsters_on_field * s);
        number_of_m = round(size_of_field * proportion_monsters_on_field * m);
        number_of_l = l;
    }
    int GetScount() final {
        return this->number_of_s;
    }

    int GetMcount() final {
        return this->number_of_m;
    }
    int GetLcount() final {
        return this->number_of_l;
    }
private:
    int number_of_s;
    int number_of_m;
    int number_of_l;
};



#endif //UNTITLED6_CANONNUMBEROFENEMIES_H
