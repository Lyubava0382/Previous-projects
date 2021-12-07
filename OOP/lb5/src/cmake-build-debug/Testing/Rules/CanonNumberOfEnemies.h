//
// Created by Любава on 26.11.2021.
//

#ifndef UNTITLED6_CANONNUMBEROFENEMIES_H
#define UNTITLED6_CANONNUMBEROFENEMIES_H



#include "NumberOfEnemiesInterface.h"


template <int* monster_array, int size_of_array>
class CanonNumberOfEnemies: NumberOfEnemiesInterface {
public:
    CanonNumberOfEnemies(){}
    int * GetMonsterArray(int size_of_field = 150) final{
        const double proportion_monsters_on_field = 0.01;
        if (monster_array == nullptr){
            int sizeofarray = 3;
            int *array = new int[sizeofarray];
            array[0] = round(size_of_field * proportion_monsters_on_field * 2);
            array[1] = round(size_of_field * proportion_monsters_on_field * 1);
            array[2] = 1;
            return array;
        }
        else return monster_array;
    }


    int GetCount(){
        if (monster_array == nullptr) return 3;
        return size_of_array;
    }
};



#endif //UNTITLED6_CANONNUMBEROFENEMIES_H
