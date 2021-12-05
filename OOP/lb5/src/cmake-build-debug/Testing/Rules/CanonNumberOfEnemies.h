//
// Created by Любава on 26.11.2021.
//

#ifndef UNTITLED6_CANONNUMBEROFENEMIES_H
#define UNTITLED6_CANONNUMBEROFENEMIES_H



#include "NumberOfEnemiesInterface.h"


template <int number_of_s, int number_of_m, int number_of_l>
class CanonNumberOfEnemies: NumberOfEnemiesInterface {
public:
    CanonNumberOfEnemies(int sizeoffield = 150){
        size_of_field = sizeoffield;
        proportion_monsters_on_field = 0.01;
    }
    int GetScount() final {
        return round(size_of_field * proportion_monsters_on_field * number_of_s);
    }

    int GetMcount() final {
        return round(size_of_field * proportion_monsters_on_field * number_of_m);
    }
    int GetLcount() final {
        return number_of_l;
    }
private:
    double proportion_monsters_on_field;
    int size_of_field;
};



#endif //UNTITLED6_CANONNUMBEROFENEMIES_H
