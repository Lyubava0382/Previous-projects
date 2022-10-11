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
class Player {
public:
    explicit Player();
    void SetLocal(int placex, int placey);
    Coordinates GetLocal();
    bool Done() const;
    void SetCountKeys(int count);
    void Key();

private:
    Coordinates location{};
    int keyCount;
    int keys;

};


#endif //UNTITLED3_PLAYER_H
