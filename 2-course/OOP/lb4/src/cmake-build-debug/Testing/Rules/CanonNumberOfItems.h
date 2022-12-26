//
// Created by Любава on 26.11.2021.
//

#ifndef UNTITLED6_CANONNUMBEROFITEMS_H
#define UNTITLED6_CANONNUMBEROFITEMS_H

#include "NumberOfItemsInterface.h"

template <int boxes, int heals, int teleports>
class CanonNumberOfItems : NumberOfItemsInterface{
public:
    CanonNumberOfItems(int size_of_field = 150){
        double proportion_items_on_field = 0.01;
        number_of_boxes = round(size_of_field * boxes * proportion_items_on_field);
        number_of_heals = round(size_of_field * heals * proportion_items_on_field);
        number_of_teleports = teleports;
    }
    int GetBoxCount() {
        return this->number_of_boxes;
    }

    int GetHealCount() {
        return this->number_of_heals;
    }
    int GetPortalCount() {
        return this->number_of_teleports;
    }
private:
    int number_of_boxes;
    int number_of_heals;
    int number_of_teleports;
};
#endif //UNTITLED6_CANONNUMBEROFITEMS_H
