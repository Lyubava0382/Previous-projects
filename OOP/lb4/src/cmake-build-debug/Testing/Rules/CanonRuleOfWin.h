//
// Created by Любава on 26.11.2021.
//

#ifndef UNTITLED6_CANONRULEOFWIN_H
#define UNTITLED6_CANONRULEOFWIN_H
#include "RuleOfWinInterface.h"


template <bool ky, int hlth, int mns>
class CanonRuleOfWin: RuleOfWinInterface {
public:
    CanonRuleOfWin(){
        key = ky;
        health = hlth;
        moneys = mns;
    }
    bool KeyNeeded() final {
        return this->key;
    }

    int MinimumHealthNeeded() final{
        return this->health;
    }
    int MinimumMoneyNeeded() final{
        return this->moneys;
    }
private:
    bool key;
    int health;
    int moneys;
};


#endif //UNTITLED6_CANONRULEOFWIN_H
