//
// Created by Любава on 26.11.2021.
//

#ifndef UNTITLED6_CANONNUMBEROFITEMS_H
#define UNTITLED6_CANONNUMBEROFITEMS_H

#include "NumberOfItemsInterface.h"

template <int number_of_boxes, int number_of_heals, int number_of_teleports>
class CanonNumberOfItems : NumberOfItemsInterface{
public:
    CanonNumberOfItems(int sizeoffield = 150){
        size_of_field = sizeoffield;
        proportion_items_on_field = 0.01;
    }
    int GetBoxCount() {
        return round(size_of_field * number_of_boxes * proportion_items_on_field);
    }

    int GetHealCount() {
        return round(size_of_field * number_of_heals * proportion_items_on_field);
    }
    int GetPortalCount() {
        return number_of_teleports;
    }
private:
    double proportion_items_on_field;
    int size_of_field;
};
#endif //UNTITLED6_CANONNUMBEROFITEMS_H
