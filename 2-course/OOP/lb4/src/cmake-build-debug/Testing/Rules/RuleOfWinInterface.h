
#ifndef UNTITLED6_RULEOFWININTERFACE_H
#define UNTITLED6_RULEOFWININTERFACE_H


class RuleOfWinInterface{
public:
    virtual bool KeyNeeded() = 0;
    virtual int MinimumHealthNeeded() = 0;
    virtual int MinimumMoneyNeeded() = 0;
};


#endif //UNTITLED6_RULEOFWININTERFACE_H
