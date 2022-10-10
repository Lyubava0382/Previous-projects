//
// Created by Serg on 10.10.2022.
//

#ifndef UNTITLED3_PLAYER_H
#define UNTITLED3_PLAYER_H


#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Characters.h"
class Player: Characters{
public:
    explicit Player();
    OBJECT GetObject();
    void SetLocal(int placex, int placey);
    Coordinates GetLocal();
    bool Done() const;
    void SetCountKeys(int count);
    void Key();

private:
    Coordinates location{};
    int keyCount;
    int keys;
    OBJECT type;

};


#endif //UNTITLED3_PLAYER_H
