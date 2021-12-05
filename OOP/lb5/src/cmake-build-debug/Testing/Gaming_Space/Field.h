//
// Created by Любава on 24.11.2021.
//

#ifndef UNTITLED6_FIELD_H
#define UNTITLED6_FIELD_H
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
    void MakeObjects(int chance = 0);
    void MakeItems(int portals_count = 1, int box_count = 3, int heal_count = 3);
    void MakeEnemies(int countS = 3, int countM = 2, int countL = 1);
    bool Access(Coordinates presentstate);
    int GetHeight();
    int GetWidth();
    int GetMonsterCount();
    Cellule** GetField();
    std::pair <Coordinates, Coordinates> GetTeleports();
    Coordinates* GetMonsters();
    void SetMonsters(int k, Coordinates m);
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


#endif //UNTITLED6_FIELD_H
