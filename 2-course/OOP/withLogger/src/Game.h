//
// Created by Любава on 13.11.2021.
//

#ifndef UNTITLED3_GAME_H
#define UNTITLED3_GAME_H
#include "ExitDoorPrint.h"
#include "FieldView.h"


class Game: public IObservable {
public:
    explicit Game();
    Field * GetField();
    Player * GetPlayer();
private:
    void NextCondition(Cellule& locate);
    void Step(GO side, Coordinates begin, int k);
    void EnemyMove();
    void GameMove();
    void Start();
    Field game;
    Player person;
};

#endif //UNTITLED3_GAME_H
