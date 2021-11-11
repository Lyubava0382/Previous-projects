#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "Player.h"
#include "Field.h"
#include "Box.h"
#include "Heal.h"
#include "Teleport.h"
#include "Smonster.h"
#include "Mmonster.h"
#include "Lmonster.h"
#include "FieldView.h"
class Game: public IObservable {
public:
    explicit Game();
    void NextCondition(Cellule& locate, Field& game);
    void Step(GO side, Coordinates begin, int k, Field& game);
    void EnemyMove(Field& game);
    void GameMove(Field& game);
    void Start(Field& game);
private:
    Field game;
    Player person;
};