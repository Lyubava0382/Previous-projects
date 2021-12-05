//
// Created by Любава on 26.11.2021.
//

#ifndef UNTITLED6_CANONRULEOFWIN_H
#define UNTITLED6_CANONRULEOFWIN_H
#include "RuleOfWinInterface.h"


template <bool key, int health, int moneys>
class CanonRuleOfWin: RuleOfWinInterface {
public:
    CanonRuleOfWin(){ }
    bool Done(Player& person) final{
        ExitDoorPrint door;
        if (person.GetKey() < key) {
            door.KeyPrint();
        } else if (person.GetCoins() < moneys) {
            door.CoinsPrint();
        } else if (person.GetHealth() < health) {
            door.HealthPrint();
        } else {
            door.OpenPrint();
            return true;
        }
        return false;
    }
};


#endif //UNTITLED6_CANONRULEOFWIN_H
