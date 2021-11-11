#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Cellule.h"
class Field: public IObservable {
public:
    Field(int w = 10, int h = 10);
    ~Field();
    
    Field(const Field &other);
    
    Field& operator = (const Field &other);
    
    Field(Field&& other);
    
    Field& operator=(Field&& other);
    
    void MakeInOut();
    
    Coordinates GetIn();
    
    void MakeObjects();
    
    void MakeItems();
    
    void MakeEnemies();
    
    bool Access(Coordinates presentstate);
    
    int GetHeight();

    int GetWidth();
    
    int GetMonsterCount();

    Cellule** GetField();

     std::pair <Coordinates, Coordinates> GetTeleports();

    Coordinates* GetMonsters();

private:
    Cellule** field;
    int width;
    int height;
    Coordinates in{};
    Coordinates out{};
    Coordinates* Monsters;
    std::pair <Coordinates, Coordinates> teleports;
    int monstercount;
};