//
// Created by Любава on 13.11.2021.
//

#ifndef UNTITLED3_FIELD_H
#define UNTITLED3_FIELD_H
#include "Cellule.h"


class Field: public IObservable{
public:
    explicit Field(int w = 10, int h = 10);
    ~Field();
    Field(const Field &other);
    Field& operator = (const Field &other);
    Field(Field&& other);
    Field& operator=(Field&& other);
    void MakeInOut();
    Coordinates GetIn();
    Coordinates GetOut();
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


#endif //UNTITLED3_FIELD_H
